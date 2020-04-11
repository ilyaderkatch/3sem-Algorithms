#include <bits/unique_ptr.h>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ios_base;
using std::map;
using std::pair;
using std::queue;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

struct AhoCorasickNode {
  // Stores ids of strings which are ended at this node.
  vector<size_t> terminal_ids_;
  // Stores tree structure of nodes.
  map<char, AhoCorasickNode> trie_transitions_;
  unordered_map<char, AhoCorasickNode *> automaton_transitions_cache_;
  AhoCorasickNode *suffix_link_ = nullptr;
  AhoCorasickNode *terminal_link_ = nullptr;
};

AhoCorasickNode *GetAutomatonTransition(AhoCorasickNode *node, char ch) {
  auto it_unordered = node->automaton_transitions_cache_.find(ch);

  // automaton had this edge in the cache
  if (it_unordered != node->automaton_transitions_cache_.end()) {
    return it_unordered->second;
  }
  auto it_map = node->trie_transitions_.find(ch);
  // automaton had this edge in the tree
  if (it_map != node->trie_transitions_.end()) {
    node->automaton_transitions_cache_[ch] = &it_map->second;
    return &it_map->second;
  }
  if (node->suffix_link_ == node) {
    return node;
  }
  AhoCorasickNode *p = GetAutomatonTransition(node->suffix_link_, ch);
  node->automaton_transitions_cache_[ch] = p;
  return p;
}

class NodeReference {
 public:
  NodeReference() = default;
  explicit NodeReference(AhoCorasickNode *node) : node_(node) {}

  NodeReference Next(char ch) const;
  template <class Callback>
  void ForEachMatch(Callback cb) const;

 private:
  AhoCorasickNode *node_ = nullptr;
};

NodeReference NodeReference::Next(char c) const {
  return NodeReference(GetAutomatonTransition(node_, c));
}

vector<size_t> FindAllTerminalLinks(AhoCorasickNode *current_node) {
  vector<size_t> ans = current_node->terminal_ids_;
  if (current_node->terminal_link_ != nullptr) {
    vector<size_t> old_terminals_ids =
        FindAllTerminalLinks(current_node->terminal_link_);
    ans.insert(ans.end(), old_terminals_ids.begin(), old_terminals_ids.end());
  }
  return ans;
}

template <class Callback>
void NodeReference::ForEachMatch(Callback cb) const {
  cb(FindAllTerminalLinks(node_));
}

class AhoCorasick {
 public:
  AhoCorasick() = default;
  AhoCorasick(const AhoCorasick &) = delete;
  AhoCorasick &operator=(const AhoCorasick &) = delete;
  AhoCorasick(AhoCorasick &&) = delete;
  AhoCorasick &operator=(AhoCorasick &&) = delete;

  AhoCorasickNode *Root() const { return &root_; }

 private:
  friend class AhoCorasickBuilder;
  mutable AhoCorasickNode root_;
};

class AhoCorasickBuilder {
 public:
  void AddString(string str, size_t id) {
    strings_.push_back(std::move(str));
    ids_.push_back(id);
  }

  std::unique_ptr<AhoCorasick> Build() {
    auto automaton = std::make_unique<AhoCorasick>();
    for (size_t i = 0; i < strings_.size(); ++i) {
      AddString(&automaton->root_, strings_[i], ids_[i]);
    }
    CalculateLinks(&automaton->root_);
    return automaton;
  }

 private:
  static void AddString(AhoCorasickNode *root, const string &string, size_t id);
  static void CalculateLinks(AhoCorasickNode *root);

  std::vector<std::string> strings_;
  std::vector<size_t> ids_;
};

void AhoCorasickBuilder::AddString(AhoCorasickNode *root,
                                   const std::string &string, size_t id) {
  AhoCorasickNode *current_node = root;
  for (size_t i = 0; i < string.size(); ++i) {
    current_node = &current_node->trie_transitions_[string[i]];
  }
  current_node->terminal_ids_.push_back(id);
}

void CalculateLinksFromNode(AhoCorasickNode *current_node,
                            AhoCorasickNode *parent, char ch,
                            AhoCorasickNode *root) {
  current_node->suffix_link_ = GetAutomatonTransition(parent->suffix_link_, ch);
  if (current_node->suffix_link_ == current_node) {
    current_node->suffix_link_ = root;
  }

  if (!current_node->suffix_link_->terminal_ids_.empty()) {
    current_node->terminal_link_ = current_node->suffix_link_;
  } else if (current_node->suffix_link_ != root) {
    current_node->terminal_link_ = current_node->suffix_link_->terminal_link_;
  }
}

void PutChildrenToQueue(AhoCorasickNode *current_node,
                        queue<AhoCorasickNode *> &queue_of_nodes,
                        AhoCorasickNode *root) {
  for (auto &[symbol, child] : current_node->trie_transitions_) {
    CalculateLinksFromNode(&child, current_node, symbol, root);
    queue_of_nodes.push(&child);
  }
}

void AhoCorasickBuilder::CalculateLinks(AhoCorasickNode *root) {
  root->suffix_link_ = root;
  queue<AhoCorasickNode *> queue_of_nodes;
  PutChildrenToQueue(root, queue_of_nodes, root);
  while (!queue_of_nodes.empty()) {
    auto current_node = queue_of_nodes.front();
    queue_of_nodes.pop();
    PutChildrenToQueue(current_node, queue_of_nodes, root);
  }
}

struct Substring {
  string substring_;
  size_t end_index_;
  Substring(string str, size_t end_index)
      : substring_(std::move(str)), end_index_(end_index) {}
};

vector<Substring> Split(const std::string &str, char delimiter) {
  vector<Substring> answer;
  size_t i = 0;
  while (i < str.size() && str[i] == delimiter) {
    ++i;
  }
  size_t first_pos = i;
  for (; i < str.size(); ++i) {
    if (str[i] == delimiter) {
      answer.emplace_back(str.substr(first_pos, i - first_pos), i - 1);
      while (i < str.size() && str[i] == delimiter) {
        ++i;
        first_pos = i;
      }
      --i;
    }
  }
  if (first_pos < str.size()) {
    answer.emplace_back(str.substr(first_pos), str.size() - 1);
  }
  return answer;
}

class WildcardMatcher {
 public:
  WildcardMatcher(const std::string &pattern, char wildcard);

  template <class Callback>
  void Scan(char character, Callback on_match);

 private:
  void UpdateWordOccurrencesCounters();
  void ShiftWordOccurrencesCounters();

  std::deque<size_t> occurences_by_offset_;
  size_t number_of_words_;
  size_t pattern_length_;
  unique_ptr<AhoCorasick> automaton_;
  NodeReference state_;
};

WildcardMatcher::WildcardMatcher(const std::string &pattern, char wildcard) {
  AhoCorasickBuilder builder;
  vector<Substring> strings = Split(pattern, wildcard);
  for (auto &string : strings) {
    builder.AddString(string.substring_, string.end_index_);
  }
  automaton_ = builder.Build();
  state_ = NodeReference(automaton_->Root());
  number_of_words_ = strings.size();
  pattern_length_ = pattern.size();
  occurences_by_offset_.resize(pattern_length_, 0);
}

void WildcardMatcher::UpdateWordOccurrencesCounters() {
  vector<size_t> matched_words;
  state_.ForEachMatch(
      [&matched_words](const vector<size_t> &a) { matched_words = a; });
  for (size_t matched_word : matched_words) {
    occurences_by_offset_[matched_word] += 1;
  }
}

void WildcardMatcher::ShiftWordOccurrencesCounters() {
  occurences_by_offset_.pop_back();
  occurences_by_offset_.push_front(0);
}

template <class Callback>
void WildcardMatcher::Scan(char character, Callback on_match) {
  state_ = state_.Next(character);
  UpdateWordOccurrencesCounters();
  if (occurences_by_offset_[pattern_length_ - 1] == number_of_words_) {
    on_match();
  }
  ShiftWordOccurrencesCounters();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string pattern;
  cin >> pattern;
  WildcardMatcher matcher(pattern, '?');

  string text;
  cin >> text;
  for (size_t i = 0; i < text.size(); ++i) {
    matcher.Scan(text[i], [&]() { cout << i + 1 - pattern.size() << " "; });
  }
  return 0;
}
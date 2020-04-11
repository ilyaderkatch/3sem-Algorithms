#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::ios_base;
using std::string;
using std::vector;

size_t FindNewPrefixFunction(size_t &max_suf, const vector<size_t> &pi,
                             const string &pattern, char letter) {
  while (max_suf > 0 && pattern[max_suf] != letter) {
    max_suf = pi[max_suf - 1];
  }
  if (letter == pattern[max_suf]) {
    ++max_suf;
  }
  return max_suf;
}

vector<size_t> ConvertStringToPrefFunc(const string &s) {
  if (s.empty()) {
    return vector<size_t>();
  }
  vector<size_t> pi(s.size());
  pi[0] = 0;
  for (size_t i = 1; i < s.size(); ++i) {
    size_t max_suf = pi[i - 1];
    pi[i] = FindNewPrefixFunction(max_suf, pi, s, s[i]);
  }
  return pi;
}

bool IsSubstring(const string &pattern, const vector<size_t> &pi, char c,
                 size_t &size_of_max_prefix_suffix) {
  return FindNewPrefixFunction(size_of_max_prefix_suffix, pi, pattern, c) ==
         pattern.size();
}

bool Scan(char &c) { return static_cast<bool>(cin >> c); }

class KMPSearcher {
 public:
  explicit KMPSearcher(const std::string &pattern);

  template <class Callback>
  void Search(Callback on_occurence) const {
    size_t pos = 0;
    size_t size_of_max_prefix_suffix = 0;
    char c;
    while (Scan(c)) {
      if (IsSubstring(pattern_, pi_, c, size_of_max_prefix_suffix)) {
        on_occurence(pos - pattern_.size() + 1);
      }
      ++pos;
    }
  }

 private:
  const string &pattern_;
  vector<size_t> pi_;  // pi_.size() == O(pattern_.size())
};

KMPSearcher::KMPSearcher(const string &pattern)
    : pattern_(pattern), pi_(ConvertStringToPrefFunc(pattern)) {}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string p;
  cin >> p;
  KMPSearcher a(p);
  a.Search([](size_t x) { cout << x << "\n"; });
  return 0;
}
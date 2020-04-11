#include <iostream>
#include <queue>
#include <set>
#include <vector>

const int desk_size = 8;
const int count_points = count_points;

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::pair;
using std::queue;
using std::set;
using std::string;
using std::vector;

struct Point {
  int x_;
  int y_;
  Point(int x, int y) : x_(x), y_(y) {}
  Point() = default;
  friend bool operator==(const Point &p1, const Point &p2) {
    return p1.x_ == p2.x_ && p1.y_ == p2.y_;
  }
  friend bool operator!=(const Point &p1, const Point &p2) {
    return !(p1 == p2);
  }
};

struct State {
  Point black_king_;
  Point white_queen_;
  bool is_white_turn_;
  State(Point black_king, Point white_queen, bool is_white_turn)
      : black_king_(black_king),
        white_queen_(white_queen),
        is_white_turn_(is_white_turn) {}
  friend bool operator<(const State &p1, const State &p2) {
    return p1.Hash() < p2.Hash();
  }
  friend bool operator>(const State &p1, const State &p2) {
    return p1.Hash() > p2.Hash();
  }
  friend bool operator==(const State &p1, const State &p2) {
    return p1.Hash() == p2.Hash();
  }
  int Hash() const;
  State() = default;
  bool IsEndGame();
};

int State::Hash() const {
  if (is_white_turn_) {
    return count_points / 2 +
           (white_queen_.y_ * desk_size + white_queen_.x_) * desk_size *
               desk_size +
           black_king_.y_ * desk_size + black_king_.x_;
  }
  return ((white_queen_.y_ * desk_size + white_queen_.x_) * desk_size *
              desk_size +
          black_king_.y_ * desk_size + black_king_.x_);
}

State FromHashToState(int hash) {
  bool white_turn;
  Point black_king;
  Point white_queen;
  if (hash >= count_points / 2) {
    white_turn = true;
    hash -= count_points / 2;
  } else {
    white_turn = false;
  }
  black_king.x_ = hash % desk_size;
  hash /= desk_size;
  black_king.y_ = hash % desk_size;
  hash /= desk_size;
  white_queen.x_ = hash % desk_size;
  hash /= desk_size;
  white_queen.y_ = hash % desk_size;
  return {black_king, white_queen, white_turn};
}

bool IsBlockedByWhiteKing(Point p) {
  return p.x_ >= 1 && p.x_ <= 3 && p.y_ >= 1 && p.y_ <= 3;
}

bool IsBlockedByBlackKing(Point curr, Point king) {
  return (curr.x_ >= king.x_ - 1) && (curr.x_ <= king.x_ + 1) &&
         (curr.y_ >= king.y_ - 1) && (curr.y_ <= king.y_ + 1);
}

void PosibleNeighPosPart2(State curr, vector<State> &neigh_hash) {
  Point new_point = curr.white_queen_;
  while (new_point.y_ >= 0 && !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    --new_point.y_;
  }
  new_point = curr.white_queen_;
  while (new_point.x_ < desk_size && new_point.y_ < desk_size &&
         !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    ++new_point.x_;
    ++new_point.y_;
  }
  new_point = curr.white_queen_;
  while (new_point.x_ >= 0 && new_point.y_ < desk_size &&
         !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    --new_point.x_;
    ++new_point.y_;
  }
}

void PosibleNeighPosPart3(State curr, vector<State> &neigh_hash) {
  Point new_point = curr.white_queen_;
  while (new_point.x_ < desk_size && new_point.y_ >= 0 &&
         !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    ++new_point.x_;
    --new_point.y_;
  }
  new_point = curr.white_queen_;
  // down-left
  while ((new_point.x_ >= 0 && new_point.y_ >= 0) &&
         !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    --new_point.x_;
    --new_point.y_;
  }
  new_point = curr.white_queen_;
  while ((new_point.y_ < desk_size) &&
         !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    ++new_point.y_;
  }
}

void PosibleNeighPosPart4(State curr, vector<State> &neigh_hash) {
  Point new_point = curr.white_queen_;
  while ((new_point.x_ >= 0) && !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    --new_point.x_;
  }
  new_point = curr.white_queen_;
  while ((new_point.x_ < desk_size) &&
         !(new_point.x_ == 2 && new_point.y_ == 2) &&
         (new_point != curr.black_king_)) {
    if ((new_point != curr.white_queen_) &&
        !IsBlockedByBlackKing(new_point, curr.black_king_)) {
      State new_state = {curr.black_king_, new_point, false};
      neigh_hash.push_back(new_state);
    }
    ++new_point.x_;
  }
  new_point = curr.white_queen_;
}

void PosibleNeighPosPart1(State curr, vector<State> &neigh_hash) {
  if (curr.is_white_turn_) {
    PosibleNeighPosPart2(curr, neigh_hash);
    PosibleNeighPosPart3(curr, neigh_hash);
    PosibleNeighPosPart4(curr, neigh_hash);
  } else {
    for (int i = max(0, curr.black_king_.x_ - 1);
         i < min(desk_size, curr.black_king_.x_ + 2); ++i) {
      for (int j = max(0, curr.black_king_.y_ - 1);
           j < min(desk_size, curr.black_king_.y_ + 2); ++j) {
        if (!IsBlockedByWhiteKing({i, j}) &&
            !(i == curr.black_king_.x_ && j == curr.black_king_.y_) &&
            !(i == curr.white_queen_.x_ && j == curr.white_queen_.y_)) {
          State new_state = {{i, j}, curr.white_queen_, true};
          neigh_hash.push_back(new_state);
        }
      }
    }
  }
}

vector<State> PosibleNeighPos(State curr) {
  vector<State> neigh_hash;
  PosibleNeighPosPart1(curr, neigh_hash);
  PosibleNeighPosPart2(curr, neigh_hash);
  return neigh_hash;
}

bool FirstBoolStatement(Point white_queen, State curr_neigh) {
  if (white_queen.x_ == white_queen.y_ && white_queen.x_ < 2 &&
      curr_neigh.black_king_.x_ > 2) {
    return false;
  }
  return !(white_queen.x_ == white_queen.y_ && white_queen.x_ > 2 &&
           curr_neigh.black_king_.x_ < 2);
}

bool SecondBoolStatement(Point white_queen, State curr_neigh) {
  if (white_queen.x_ + white_queen.y_ == desk_size / 2 && white_queen.x_ < 2 &&
      curr_neigh.black_king_.x_ > 2) {
    return false;
  }
  return !(white_queen.x_ + white_queen.y_ == desk_size / 2 &&
           white_queen.x_ > 2 && curr_neigh.black_king_.x_ < 2);
}

bool ThirdBoolStatement(Point white_queen, State curr_neigh) {
  if (white_queen.x_ == 2 && white_queen.y_ < 2 &&
      curr_neigh.black_king_.y_ > 2) {
    return false;
  }
  return !(white_queen.x_ == 2 && white_queen.y_ > 2 &&
           curr_neigh.black_king_.y_ < 2);
}

bool FourthBoolStatement(Point white_queen, State curr_neigh) {
  if (white_queen.y_ == 2 && white_queen.x_ < 2 &&
      curr_neigh.black_king_.x_ > 2) {
    return false;
  }
  return !(white_queen.y_ == 2 && white_queen.x_ > 2 &&
           curr_neigh.black_king_.x_ < 2);
}

bool State::IsEndGame() {
  if (is_white_turn_) {
    return false;
  }
  vector<State> curr_neigh = PosibleNeighPos(*this);
  for (int i = 0; i < curr_neigh.size(); ++i) {
    if (curr_neigh[i].black_king_.x_ - white_queen_.x_ ==
        curr_neigh[i].black_king_.y_ - white_queen_.y_) {
      if (FirstBoolStatement(white_queen_, curr_neigh[i])) {
        return false;
      }
      continue;
    }
    if (curr_neigh[i].black_king_.x_ - white_queen_.x_ ==
        -curr_neigh[i].black_king_.y_ + white_queen_.y_) {
      if (SecondBoolStatement(white_queen_, curr_neigh[i])) {
        return false;
      }
      continue;
    }
    if (curr_neigh[i].black_king_.x_ == white_queen_.x_) {
      if (ThirdBoolStatement(white_queen_, curr_neigh[i])) {
        return false;
      }
      continue;
    }
    if (curr_neigh[i].black_king_.y_ == white_queen_.y_) {
      if (FourthBoolStatement(white_queen_, curr_neigh[i])) {
        return false;
      }
      continue;
    }
    return false;
  }
  return true;
}

Point ProcessingInput(char letter, char number) {
  return {letter - 'a', number - '1'};
}

struct GameGraph {
  vector<set<State> > list_of_states_;
  queue<pair<State, int> > que_;
  State start_state_;
  explicit GameGraph(State start);
  int FindFastestVictory();
};

GameGraph::GameGraph(State start) {
  vector<bool> is_visited(count_points, false);
  list_of_states_.resize(count_points);
  start_state_ = start;
  is_visited[start.Hash()] = true;
  queue<State> q;
  q.push(start);
  while (!q.empty()) {
    State curr_state = q.front();
    q.pop();
    if (curr_state.IsEndGame()) {
      que_.push({curr_state, 0});
    }
    vector<State> neigh_states = PosibleNeighPos(curr_state);
    for (int i = 0; i < neigh_states.size(); ++i) {
      list_of_states_[neigh_states[i].Hash()].insert(curr_state);
      if (!is_visited[neigh_states[i].Hash()]) {
        is_visited[neigh_states[i].Hash()] = true;
        q.push(neigh_states[i]);
      }
    }
  }
}

int IsAllChildrenVisited(const vector<int> &is_visited, State state) {
  vector<State> neigh = PosibleNeighPos(state);
  int maxi = 0;
  for (int i = 0; i < neigh.size(); ++i) {
    if (is_visited[neigh[i].Hash()] == -1) {
      return -1;
    }
    maxi = max(maxi, is_visited[neigh[i].Hash()]);
  }
  return maxi;
}

int GameGraph::FindFastestVictory() {
  vector<int> is_visited(count_points, -1);
  while (!que_.empty()) {
    auto p = que_.front();
    que_.pop();
    State curr_state = p.first;
    int depth = p.second;
    if (curr_state.is_white_turn_) {
      if (p.first == start_state_) {
        return depth;
      }
      set<State> neigh_states = list_of_states_[curr_state.Hash()];
      for (auto i = neigh_states.begin(); i != neigh_states.end(); ++i) {
        int k = IsAllChildrenVisited(is_visited, *i);
        if (k != -1) {
          is_visited[i->Hash()] = k + 1;
          que_.push({*i, k + 1});
        }
      }
    } else {
      set<State> neigh_states = list_of_states_[curr_state.Hash()];
      for (auto i = neigh_states.begin(); i != neigh_states.end(); ++i) {
        if (is_visited[i->Hash()] == -1) {
          is_visited[i->Hash()] = depth + 1;
          que_.push({*i, depth + 1});
        }
      }
    }
  }
  return -1;
}

int main() {
  string first_s;
  string second_s;
  cin >> first_s >> second_s;
  GameGraph game({ProcessingInput(second_s[0], second_s[1]),
                  ProcessingInput(first_s[0], first_s[1]), true});
  cout << game.FindFastestVictory() << endl;
  return 0;
}


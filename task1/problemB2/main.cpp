#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using std::array;
using std::cin;
using std::cout;
using std::distance;
using std::endl;
using std::find;
using std::ios_base;
using std::string;
using std::vector;

const char min_letter = 'a';
const size_t count_of_letters = 'z' - 'a' + 1;

char FindNotBlocked(const array<bool, count_of_letters> &blocked) {
  auto i = find(blocked.begin(), blocked.end(), false);
  return static_cast<char>(distance(blocked.begin(), i) +
                           static_cast<size_t>(min_letter));
}

string StrFromZ(const vector<size_t> &input_array) {
  if (input_array.empty()) {
    return "";
  }
  string res;
  res.push_back(min_letter);
  size_t right_limit = 0;
  size_t index = 0;
  vector<size_t> blocked(1, 0);
  for (size_t i = 1; i < input_array.size(); ++i) {
    if (right_limit < input_array[i] + i - 1) {
      blocked.resize(1);
      blocked.push_back(input_array[i]);
      right_limit = input_array[i] + i - 1;
      index = 0;
    }
    if (right_limit == input_array[i] + i - 1) {
      blocked.push_back(input_array[i]);
    }

    if (right_limit >= i) {
      res += res[index];
      ++index;
    } else {
      array<bool, count_of_letters> blocked_char{};
      for (size_t j : blocked) {
        blocked_char[static_cast<size_t>(res[j] - min_letter)] = true;
      }
      res += FindNotBlocked(blocked_char);
      right_limit = i;
      index = 0;
      blocked.resize(1);
    }
  }
  return res;
}

void InputVector(vector<size_t> &array) {
  size_t input_integer = 0;
  while (cin >> input_integer) {
    array.push_back(input_integer);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<size_t> a;
  InputVector(a);
  cout << StrFromZ(a) << endl;
  return 0;
}
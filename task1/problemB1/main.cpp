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

string StrFromPre(const vector<size_t> &input_vector) {
  if (input_vector.empty()) {
    return "";
  }
  string res;
  res.push_back(min_letter);
  for (size_t i = 1; i < input_vector.size(); ++i) {
    if (input_vector[i] != 0) {
      res += res[input_vector[i] - 1];
    } else {
      array<bool, count_of_letters> blocked{};
      blocked[0] = true;
      size_t k = input_vector[i - 1];
      while (k > 0) {
        blocked[static_cast<size_t>(res[k] - min_letter)] = true;
        k = input_vector[k - 1];
      }
      res += FindNotBlocked(blocked);
    }
  }
  return res;
}

void InputVector(vector<size_t> &arr) {
  size_t integer = 0;
  while (cin >> integer) {
    arr.push_back(integer);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<size_t> input_data;
  InputVector(input_data);
  cout << StrFromPre(input_data) << endl;
  return 0;
}

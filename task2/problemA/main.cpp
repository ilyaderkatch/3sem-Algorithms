#include <algorithm>
#include <iostream>
#include <vector>

const size_t alphabet_length = 256;

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::vector;

class SufArray {
 private:
  vector<size_t> suff_arr_;
  void FirstStepOfBuilding(const string &input_string, vector<size_t> &classes);
  void OthersStepsOfBuilding(const string &input_string,
                             vector<size_t> &classes);

 public:
  size_t operator[](const size_t index) const { return suff_arr_[index]; }
  size_t Size() const { return suff_arr_.size(); }
  SufArray(const string &input_string);
};

void CalculatePosFromCount(vector<size_t> &count_in_classes) {
  for (size_t i = count_in_classes.size() - 1; i > 0; --i) {
    count_in_classes[i] = count_in_classes[i - 1];
  }
  count_in_classes[0] = 0;
  for (size_t i = 1; i < count_in_classes.size(); ++i) {
    count_in_classes[i] += count_in_classes[i - 1];
  }
}

void SufArray::FirstStepOfBuilding(const string &input_string,
                                   vector<size_t> &classes) {
  vector<size_t> count_in_classes(max(input_string.size(), alphabet_length), 0);
  for (char i : input_string) {
    count_in_classes[static_cast<size_t>(i)] += 1;
  }

  CalculatePosFromCount(count_in_classes);

  for (size_t i = 0; i < input_string.size(); ++i) {
    suff_arr_[count_in_classes[static_cast<size_t>(input_string[i])]++] = i;
  }

  classes[suff_arr_[0]] = 0;
  size_t num_of_class = 0;
  for (size_t i = 1; i < suff_arr_.size(); ++i) {
    if (input_string[suff_arr_[i]] != input_string[suff_arr_[i - 1]]) {
      ++num_of_class;
    }
    classes[suff_arr_[i]] = num_of_class;
  }
}

void SufArray::OthersStepsOfBuilding(const string &input_string,
                                     vector<size_t> &classes) {
  vector<size_t> count_in_classes(max(input_string.size(), alphabet_length), 0);
  size_t num_of_class = 0;
  size_t curr_len = 1;
  while (curr_len < input_string.size()) {
    count_in_classes.clear();
    count_in_classes.assign(max(input_string.size(), alphabet_length), 0);
    vector<size_t> sorted_by_old_classes(input_string.size(), 0);
    for (size_t i = 0; i < sorted_by_old_classes.size(); ++i) {
      sorted_by_old_classes[i] =
          (suff_arr_[i] - curr_len + input_string.size()) % input_string.size();
    }

    for (size_t sorted_by_old_classe : sorted_by_old_classes) {
      ++count_in_classes[classes[sorted_by_old_classe]];
    }
    CalculatePosFromCount(count_in_classes);
    for (size_t i = 0; i < suff_arr_.size(); ++i) {
      suff_arr_[count_in_classes[classes[sorted_by_old_classes[i]]]] =
          sorted_by_old_classes[i];
      ++count_in_classes[classes[sorted_by_old_classes[i]]];
    }

    vector<size_t> new_classes(input_string.size());
    new_classes[suff_arr_[0]] = 0;
    num_of_class = 0;

    for (size_t i = 1; i < new_classes.size(); ++i) {
      if (classes[suff_arr_[i]] != classes[suff_arr_[i - 1]] ||
          classes[(suff_arr_[i] + curr_len) % input_string.size()] !=
              classes[(suff_arr_[i - 1] + curr_len) % input_string.size()]) {
        ++num_of_class;
      }
      new_classes[suff_arr_[i]] = num_of_class;
    }
    classes = new_classes;
    curr_len <<= 1;
  }
}

SufArray::SufArray(const string &input_string) {
  vector<size_t> classes(input_string.size());
  suff_arr_.resize(input_string.size());
  FirstStepOfBuilding(input_string, classes);
  OthersStepsOfBuilding(input_string, classes);
}

vector<size_t> CountMaxLengthOfCommonPrefixes(const SufArray &suff_arr,
                                              const string &str) {
  vector<size_t> ans(str.size());
  size_t pos = 0;
  vector<size_t> anti_suff_arr(suff_arr.Size());
  for (size_t i = 0; i < suff_arr.Size(); ++i) {
    anti_suff_arr[suff_arr[i]] = i;
  }
  for (size_t i = 0; i < str.size(); ++i) {
    if (pos > 0) {
      --pos;
    }
    if (anti_suff_arr[i] != str.size() - 1) {
      while ((pos + i < str.size()) &&
             (pos + suff_arr[anti_suff_arr[i] + 1] < str.size()) &&
             (str[i + pos] == str[suff_arr[anti_suff_arr[i] + 1] + pos])) {
        ++pos;
      }
      ans[anti_suff_arr[i]] = pos;
    }
  }
  return ans;
}

int FindCountOfDifferentSubstrings(const string &input_str) {
  string s = input_str + '$';
  SufArray suff_arr(s);
  vector<size_t> lcp = CountMaxLengthOfCommonPrefixes(suff_arr, s);
  int ans = 0;
  for (size_t i = 1; i < lcp.size(); ++i) {
    ans +=
        static_cast<int>(s.size()) - static_cast<int>(suff_arr[i] + lcp[i]) - 1;
  }
  return ans;
}

int main() {
  string s;
  cin >> s;
  cout << FindCountOfDifferentSubstrings(s) << endl;
  return 0;
}

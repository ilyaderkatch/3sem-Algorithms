#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::vector;

class BigInteger {
 public:
  BigInteger();
  BigInteger(int a);

  bool operator<(BigInteger const &b) const;
  bool operator>(BigInteger const &b) const;
  bool operator==(BigInteger const &b) const;
  bool operator<=(BigInteger const &b) const;
  bool operator>=(BigInteger const &b) const;
  bool operator!=(BigInteger const &b) const;

  BigInteger &operator*=(const BigInteger &b);
  BigInteger &operator+=(const BigInteger &c);
  BigInteger &operator-=(const BigInteger &c);
  BigInteger &operator%=(const BigInteger &b);
  BigInteger &operator/=(const BigInteger &c);

  BigInteger &operator++();
  BigInteger operator++(int);
  BigInteger &operator--();
  BigInteger operator--(int);

  BigInteger operator-() const;

  const std::string toString() const;

  explicit operator bool();

  friend std::istream &operator>>(std::istream &in, BigInteger &n);
  friend std::ostream &operator<<(std::ostream &out, const BigInteger &n);

  friend BigInteger operator*(const BigInteger &b, const BigInteger &a);
  friend BigInteger operator/(const BigInteger &a, const BigInteger &b);
  friend BigInteger operator%(const BigInteger &a, const BigInteger &b);
  friend BigInteger operator+(BigInteger a, const BigInteger &b);
  friend BigInteger operator-(BigInteger a, const BigInteger &c);

 private:
  bool is_nonnegative;
  std::vector<int> num;

  BigInteger(bool sign, vector<int> a)
      : is_nonnegative(sign), num(std::move(a)){};
  static void dif(BigInteger &a, const BigInteger &b);
  static void sum(BigInteger &a, const BigInteger &b);
  static BigInteger mult(const BigInteger &a, const BigInteger &b);
  static void div(BigInteger &a, const BigInteger &b);
  static BigInteger linear_mult(const BigInteger &a, int m);
  BigInteger abs(BigInteger b) {
    b.is_nonnegative = true;
    return b;
  }
  static void pow_10(BigInteger &a, int pow);
  void DeleteZeros();
  bool CompareIfSignsAreTheSame(BigInteger const &n, BigInteger const &m) const;
  friend void PushStrToNum(const string &s, BigInteger &n, int start_ind);
};

BigInteger::operator bool() { return *this != 0; }

void BigInteger::DeleteZeros() {
  while (num.size() > 0 && num[num.size() - 1] == 0) {
    num.pop_back();
  }
  if (num.size() == 0 && !is_nonnegative) {
    is_nonnegative = true;
  }
}

BigInteger::BigInteger() { is_nonnegative = true; }

BigInteger::BigInteger(int a) {
  if (a < 0) {
    is_nonnegative = false;
    a *= -1;
  } else {
    is_nonnegative = true;
  }
  while (a > 0) {
    num.push_back(a % 10);
    a /= 10;
  }
}

bool BigInteger::CompareIfSignsAreTheSame(BigInteger const &n,
                                          BigInteger const &m) const {
  if (m.num.size() > n.num.size()) {
    return false;
  }
  if (m.num.size() < n.num.size()) {
    return true;
  }
  return std::lexicographical_compare(m.num.rbegin(), m.num.rend(),
                                      n.num.rbegin(), n.num.rend());
}

bool BigInteger::operator<(BigInteger const &n) const {
  if (is_nonnegative && !n.is_nonnegative) {
    return false;
  }
  if (!is_nonnegative && n.is_nonnegative) {
    return true;
  }
  if (is_nonnegative && n.is_nonnegative) {
    return CompareIfSignsAreTheSame(n, *this);
  }
  return CompareIfSignsAreTheSame(*this, n);
}

bool BigInteger::operator>(BigInteger const &b) const { return b < *this; }

bool BigInteger::operator==(BigInteger const &b) const {
  return !(*this < b || *this > b);
}

bool BigInteger::operator<=(BigInteger const &b) const { return !(*this > b); }

bool BigInteger::operator>=(BigInteger const &b) const { return !(*this < b); }

bool BigInteger::operator!=(BigInteger const &b) const { return !(*this == b); }

BigInteger BigInteger::operator-() const {
  return {!this->is_nonnegative, this->num};
}

void BigInteger::sum(BigInteger &a, const BigInteger &b) {
  size_t least = min(a.num.size(), b.num.size());
  size_t largest = max(a.num.size(), b.num.size());
  int transfer = 0;
  for (size_t i = 0; i < least; ++i) {
    int cur_sum = a.num[i] + b.num[i] + transfer;
    a.num[i] = cur_sum % 10;
    transfer = cur_sum / 10;
  }

  if (a.num.size() == largest) {
    for (size_t i = least; i < largest; ++i) {
      int cur_sum = a.num[i] + transfer;
      a.num[i] = cur_sum % 10;
      transfer = cur_sum / 10;
    }
  } else {
    for (size_t i = least; i < largest; ++i) {
      a.num.push_back((b.num[i] + transfer) % 10);
      transfer = (b.num[i] + transfer) / 10;
    }
  }

  if (transfer != 0) {
    a.num.push_back(transfer);
  }
}

void PlusDigit(int &cur_dif, int &transfer) {
  if (cur_dif < 0) {
    cur_dif += 10;
    transfer = 1;
  } else {
    transfer = 0;
  }
}

void BigInteger::dif(BigInteger &a, const BigInteger &b) {
  if ((a >= b && a.is_nonnegative) || (a <= b && !a.is_nonnegative)) {
    int transfer = 0;
    int cur_dif = 0;
    for (size_t i = 0; i < b.num.size(); ++i) {
      cur_dif = a.num[i] - transfer - b.num[i];
      a.num[i] = cur_dif;
    }
    for (size_t i = b.num.size(); i < a.num.size(); ++i) {
      cur_dif = a.num[i] - transfer;
      PlusDigit(cur_dif, transfer);
      a.num[i] = cur_dif;
    }
  } else {
    a.is_nonnegative = !a.is_nonnegative;
    int transfer = 0;
    int cur_dif = 0;
    for (size_t i = 0; i < a.num.size(); ++i) {
      cur_dif = b.num[i] - transfer - a.num[i];
      PlusDigit(cur_dif, transfer);
      a.num[i] = cur_dif;
    }
    for (size_t i = a.num.size(); i < b.num.size(); ++i) {
      cur_dif = b.num[i] - transfer;
      PlusDigit(cur_dif, transfer);
      a.num.push_back(cur_dif);
    }
  }
  a.DeleteZeros();
}

BigInteger &BigInteger::operator+=(const BigInteger &b) {
  if ((this->is_nonnegative && !b.is_nonnegative) ||
      (!this->is_nonnegative && b.is_nonnegative)) {
    dif(*this, -b);
    return *this;
  }
  sum(*this, b);
  return *this;
}

BigInteger &BigInteger::operator-=(const BigInteger &b) {
  if ((this->is_nonnegative && !b.is_nonnegative) ||
      (!this->is_nonnegative && b.is_nonnegative)) {
    sum(*this, -b);
    return *this;
  }
  dif(*this, b);
  return *this;
}

BigInteger operator+(BigInteger a, const BigInteger &b) {
  a += b;
  return a;
}

BigInteger operator-(BigInteger a, const BigInteger &b) {
  a -= b;
  return a;
}

const string BigInteger::toString() const {
  if (this->num.size() == 0) {
    return "0";
  }
  string s;
  if (!this->is_nonnegative) {
    s += "-";
  }
  for (size_t i = this->num.size(); i > 0; --i) {
    s += static_cast<char>('0' + this->num[i - 1]);
  }
  return s;
}

std::ostream &operator<<(std::ostream &out, const BigInteger &n) {
  out << n.toString();
  return out;
}

void PushStrToNum(const string &s, BigInteger &n, int start_ind) {
  for (size_t i = s.size() - 1 - start_ind; i > 0; --i) {
    n.num.push_back(s[i] - '0');
  }
}

std::istream &operator>>(std::istream &in, BigInteger &n) {
  string input;
  in >> input;
  n.num.clear();
  if (input.size() == 0) {
    n.is_nonnegative = true;
  } else {
    if (input[0] == '-') {
      n.is_nonnegative = false;
      PushStrToNum(input, n, 0);
    } else {
      n.is_nonnegative = true;
      PushStrToNum(input, n, 1);
    }
  }
  n.DeleteZeros();
  return in;
}

BigInteger &BigInteger::operator++() {
  *this += static_cast<BigInteger>(1);
  return *this;
}

BigInteger BigInteger::operator++(int) {
  BigInteger copy = *this;
  *this += static_cast<BigInteger>(1);
  return copy;
}

BigInteger &BigInteger::operator--() {
  *this -= static_cast<BigInteger>(1);
  return *this;
}

BigInteger BigInteger::operator--(int) {
  BigInteger copy = *this;
  *this -= static_cast<BigInteger>(1);
  return copy;
}

void BigInteger::div(BigInteger &a, const BigInteger &b) {
  BigInteger curr_num;
  for (size_t i = a.num.size(); i > 0; --i) {
    curr_num *= 10;
    curr_num += a.num[i - 1];
    int digit = 1;
    while (curr_num >= b * digit) {
      ++digit;
    }
    a.num[i - 1] = digit - 1;
    curr_num -= (digit - 1) * b;
  }
  a.DeleteZeros();
}

BigInteger BigInteger::mult(const BigInteger &a, const BigInteger &b) {
  if (a.num.size() == 0 || b.num.size() == 0) {
    return BigInteger();
  }
  if (a.num.size() == 1) {
    return linear_mult(b, a.num[0]);
  } else if (b.num.size() == 1) {
    return linear_mult(a, b.num[0]);
  } else {
    size_t m = min(a.num.size(), b.num.size()) / 2;
    BigInteger high_a(true, vector<int>(a.num.begin(), a.num.begin() + m));
    BigInteger high_b(true, vector<int>(b.num.begin(), b.num.begin() + m));
    BigInteger low_a(true, vector<int>(a.num.begin() + m, a.num.end()));
    BigInteger low_b(true, vector<int>(b.num.begin() + m, b.num.end()));
    BigInteger z2 = mult(low_a, low_b);
    BigInteger z1 = mult((low_a + high_a), (low_b + high_b));
    BigInteger z0 = mult(high_a, high_b);
    BigInteger dif_of_parts = z1 - z2 - z0;
    pow_10(z2, m * 2);
    pow_10(dif_of_parts, m);
    return z2 + dif_of_parts + z0;
  }
}

BigInteger BigInteger::linear_mult(const BigInteger &a, int m) {
  BigInteger res;
  int transfer = 0;
  for (size_t i = 0; i < a.num.size(); ++i) {
    transfer = a.num[i] * m + transfer;
    res.num.push_back(transfer % 10);
    transfer /= 10;
  }
  if (transfer != 0) {
    res.num.push_back(transfer);
  }
  return res;
}

void BigInteger::pow_10(BigInteger &a, int pow) {
  a.num.insert(a.num.begin(), pow, 0);
}

BigInteger &BigInteger::operator*=(const BigInteger &b) {
  bool sign = (this->is_nonnegative && b.is_nonnegative) ||
              (!this->is_nonnegative && !b.is_nonnegative);
  *this = abs(*this);
  *this = mult(*this, abs(b));
  this->is_nonnegative = sign;
  return *this;
}

BigInteger &BigInteger::operator/=(const BigInteger &b) {
  bool sign = (this->is_nonnegative && b.is_nonnegative) ||
              (!this->is_nonnegative && !b.is_nonnegative);
  *this = abs(*this);
  div(*this, abs(b));
  this->is_nonnegative = sign;
  return *this;
}

BigInteger &BigInteger::operator%=(const BigInteger &b) {
  *this = *this - *this / b * b;
  return *this;
}

BigInteger operator*(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  res *= b;
  return res;
}

BigInteger operator/(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  res /= b;
  return res;
}

BigInteger operator%(const BigInteger &a, const BigInteger &b) {
  BigInteger res = a;
  res %= b;
  return res;
}


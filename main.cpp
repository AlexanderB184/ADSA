#include <cassert>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

string& reverse(string& A) {
  int n = A.length() - 1;
  for (int i = 0; i < A.length() / 2; i++) {
    std::swap(A[i], A[n - i]);
  }
  return A;
}

void leftpad(string& A, int n) {
  A.resize(A.length() + n);
  for (int i = 0; i < A.length(); i++) {
    A[i + n] = A[i];
  }
  for (int i = 0; i < n; i++) {
    A[i] = '0';
  }
}

void make_same_length(string& A, string& B) {
  if (A.length() < B.length()) {
    leftpad(A, B.length() - A.length());
  } else if (A.length() > B.length()) {
    leftpad(B, A.length() - B.length());
  }
}

string& strip_trailing_zeros(string& A) {
  int i = A.length();
  while (--i >= 0 && A[i] == '0') {
    A.pop_back();
  }
  return A;
}

string school_addition(const string& lhs, const string& rhs, int base) {
  string res;
  int carry = 0;
  int i = 0;
  int n = std::max(lhs.length(), rhs.length());
  while (i < n) {
    int a = 0, b = 0;
    if (i < lhs.length()) a = lhs[i] - '0';
    if (i < rhs.length()) b = rhs[i] - '0';
    int x = a + b + carry;
    carry = (x / base);
    res.push_back((x % base) + '0');
    i++;
  }
  res.push_back(carry + '0');
  strip_trailing_zeros(res);
  return res;
}

string school_subtraction(const string& lhs, const string& rhs, int base) {
  string res;
  int borrow = 0;
  int i = 0;
  int n = std::max(lhs.length(), rhs.length());
  while (i < n) {
    int a = 0, b = 0;
    if (i < lhs.length()) a = lhs[i] - '0';
    if (i < rhs.length()) b = rhs[i] - '0';
    int x = a - b - borrow;
    if (x < 0) {
      x += base;
      borrow = 1;
    } else {
      borrow = 0;
    }
    res.push_back((x % base) + '0');
    i++;
  }
  res.push_back(borrow + '0');
  strip_trailing_zeros(res);
  return res;
}

string school_multiplication(const string& lhs, const string& rhs, int base) {
  assert(rhs.length() < 2);
  if (rhs.length() == 0) {
    return "";
  }
  string res;
  res.reserve(lhs.length() + 1);
  char carry = '0';
  int m = (rhs[0] - '0');
  int i = 0;
  while (i < lhs.length()) {
    int x = (lhs[i] - '0') * m + (carry - '0');
    carry = (x / base) + '0';
    res.push_back((x % base) + '0');
    i++;
  }
  res.push_back(carry);
  strip_trailing_zeros(res);
  return res;
}

string karatsuba_multiplication(const string& lhs, const string& rhs,
                                int base) {
  if (lhs.length() < 2) {
    return school_multiplication(rhs, lhs, base);
  } else if (rhs.length() < 2) {
    return school_multiplication(lhs, rhs, base);
  }
  int m = std::max(lhs.length(), rhs.length());
  int m2 = m - m / 2;
  string low1 = lhs.substr(0, m2);
  string high1 = lhs.substr(m2);
  string low2 = rhs.substr(0, m2);
  string high2 = rhs.substr(m2);
  string z0 = karatsuba_multiplication(low1, low2, base);
  string z1 =
      karatsuba_multiplication(school_addition(low1, high1, base),
                               school_addition(low2, high2, base), base);
  string z2 = karatsuba_multiplication(high1, high2, base);
  string z3 = school_addition(z2, z0, base);
  string z4, z5;
  if (stoi(z3) > stoi(z1)) {
    cout << "a" << endl;
    z4 = school_subtraction(z3, z1, base);
    leftpad(z4, m2);
    leftpad(z2, m2 * 2);
    z5 = school_subtraction(z2, z4, base);
    return school_addition(z5, z0, base);
  } else {
    cout << "b" << endl;
    z4 = school_subtraction(z1, z3, base);
    leftpad(z4, m2);
    leftpad(z2, m2 * 2);
    z5 = school_addition(z2, z4, base);
    return school_addition(z5, z0, base);
  }
}

int main(int argc, char const* argv[]) {
  string a = "999";
  string b = "1000";
  string base = "10";
  string res = school_subtraction(reverse(a), reverse(b), stoi(base));
  cout << reverse(res) << endl;
  return 0;
}

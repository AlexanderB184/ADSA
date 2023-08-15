#include <cassert>
#include <iostream>
#include <string>

using std::string;

string reverse(string A) {
  size_t n = A.length() - 1;
  size_t m = A.length() / 2;
  for (size_t i = 0; i < m; i++) {
    std::swap(A[i], A[n - i]);
  }
  return A;
}

void leftpad(string& A, size_t n) {
  A.resize(A.length() + n);
  for (long i = A.length() - 1; i >= 0; i--) {
    A[i + n] = A[i];
  }
  for (size_t i = 0; i < n; i++) {
    A[i] = '0';
  }
}

string& strip_trailing_zeros(string& A) {
  size_t i = A.length();
  while (--i > 0 && A[i] == '0') {
    A.pop_back();
  }
  return A;
}

string school_addition(const string& lhs, const string& rhs, int base) {
  string res;
  int carry = 0;
  size_t i = 0;
  size_t n = std::max(lhs.length(), rhs.length());
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
  size_t i = 0;
  size_t n = std::max(lhs.length(), rhs.length());
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
    return "0";
  }
  string res;
  res.reserve(lhs.length() + 1);
  char carry = '0';
  int m = (rhs[0] - '0');
  size_t i = 0;
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
  size_t m = std::max(lhs.length(), rhs.length());
  size_t m2 = m - m / 2;
  string low1 = lhs.substr(0, m2);
  string high1 = lhs.substr(m2);
  string low2 = rhs.substr(0, m2);
  string high2 = rhs.substr(m2);
  string z0 = karatsuba_multiplication(low1, low2, base);
  string z1 =
      karatsuba_multiplication(school_addition(low1, high1, base),
                               school_addition(low2, high2, base), base);
  string z2 = karatsuba_multiplication(high1, high2, base);
  string z4 = school_subtraction(school_subtraction(z1, z2, base), z0, base);
  leftpad(z4, m2);
  leftpad(z2, m2 * 2);
  return school_addition(z0, school_addition(z2, z4, base), base);
}

string add(const string& A, const string& B, const string& base) {
  return reverse(school_addition(reverse(A), reverse(B), stoi(base)));
}

string mult(const string& A, const string& B, const string& base) {
  return reverse(karatsuba_multiplication(reverse(A), reverse(B), stoi(base)));
}

int main(int argc, char const* argv[]) {
  assert(argc == 4);
  std::cout << add(argv[1], argv[2], argv[3]) << " "
            << mult(argv[1], argv[2], argv[3]) << " 0" << std::endl;
  return 0;
}

//
// Created by marsofandrew on 16.09.18.
//
#include "supportive_functions.hpp"
#include <exception>
#include <stdexcept>

std::vector<double> solveMatrixSweepMethod(const unsigned long n, std::vector<double> a,
                                            std::vector<double> c,
                                            std::vector<double> b,
                                            std::vector<double> f)
{
  if ((a.size() != n) || (b.size() != n) || (c.size() != n) || (f.size() != n)) {
    throw std::invalid_argument("one of your vector have invalid size");
  }
  if (c[0] == 0) {
    throw std::invalid_argument("c[0] = 0");
  }
  double m = 1;
  for (int i = 1; i < n; i++) {
    m = a[i] / c[i];
    c[i] = c[i] - m * b[i - 1];
    f[i] = f[i] - m * f[i - 1];
  }
  std::vector<double> solution(n);
  solution[n - 1] = f[n - 1] / c[n - 1];
  for (int j = n - 2; j >= 0; --j) {
    solution[j] = (f[j] - b[j] * solution[j + 1]) / c[j];
  }
  return solution;
}

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
  std::vector<double> alpha(n);
  std::vector<double> beta(n);
  alpha[0] = -b[0]/c[0];
  beta[0] = f[0]/c[0];
  for (int i = 1; i<n ; i++){
    alpha[i] =-b[i-1]/(a[i-1]*alpha[i-1]+c[i-1]);
    beta[i]=(f[i-1]-a[i-1]*beta[i-1])/(a[i-1]*alpha[i-1]+c[i-1]);
  }
  std::vector<double> solution(n);
  solution[n-1] = (f[n-1]-a[n-1]*beta[n-1])/(a[n-1]*alpha[n-1]+c[n-1]);
  for (int i = n-2; i>=0; --i){
    solution[i] = alpha[i+1]*solution[i+1] + beta[i+1];
  }

  return solution;
}

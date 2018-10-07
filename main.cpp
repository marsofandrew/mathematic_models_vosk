#include <iostream>
#include <vector>
#include "Equation.hpp"

double f(double r)
{
  return 1;
}

double k(double r)
{
  return 1;
}

double q(double r)
{
  return 1;
}

double u(double r)
{
  return 1;
}

std::vector<double> countQ(std::size_t n, double rMin, double rMax)
{
  std::vector<double> retVector(n);
  const double h = (rMax - rMin) / n;
  for (std::size_t i = 0; i <= n; ++i) {
    retVector[i] = (u(rMin + i * h));
  }
  return retVector;
}

void printInfo(const std::vector<double> &solvedVector, const std::vector<double> &correctVector, std::size_t n)
{
  std::cout << "\n------------------- N = " << n << "-------------------\n";
  for (int i = 0; i < solvedVector.size(); ++i) {
    std::cout << "i = " << i <<" correct = "<<correctVector[i]<< " difference = " << correctVector[i] - solvedVector[i] << "\n";
  }
  std::cout << "---------------------------------------------------------\n";
}

int main()
{
  const double capa = 1;
  const double mu = 1;
  const double rMin = 0;
  const double rMax = 1;
  for (std::size_t n = 4; n <= 64; n *= 2) {
    Equation equation = {&k, &q, &f, capa, mu, n, rMin, rMax};
    printInfo(equation.solve(), countQ(n, rMin, rMax), n);
  }

  return 0;
}


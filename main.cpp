#include <iostream>
#include "Equation.hpp"
#include "Test.hpp"

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

int main()
{
  Test test1(&u, &k, &q, &f, 1, 1, 1, 0, 2);
  test1.test(4,1024);
  test1.printResults();

  return 0;
}


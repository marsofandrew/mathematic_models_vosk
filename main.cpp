#include <iostream>
#include "Equation.hpp"
#include "Test.hpp"

int main()
{
  const std::size_t minPart = 4;
  const std::size_t maxPart = 1024;

  Test::funct funct = [](double r) { return 1; };

  Test test1("first", funct, funct, funct, funct, 1, 1, 1, 2, 20);
  test1.test(minPart, maxPart);
  test1.printResults();

  Test::funct funct2 = [](double r) { return 5 * r; };

  Test test2("lineat P_1(r)", funct2, funct, funct,
             [](double r) { return -5 / r + 5 * r; }, 1, 0, 55, 0, 10);
  test2.test(minPart, maxPart);
  test2.printResults();

  Test test3("both linear", funct2, funct2, funct, [](double r) { return 5 * r - 50; }, 1, 0, 300, 0, 10);
  test3.test(minPart, maxPart);
  test3.printResults();

  return 0;
}


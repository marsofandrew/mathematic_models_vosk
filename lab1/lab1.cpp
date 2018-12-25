//
// Created by marsofandrew on 23.12.18.
//

#include "../impl.hpp"
#include <iostream>
#include "Equation.hpp"
#include "Test.hpp"
void lab1(){
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

  Test::funct funct3 = [](double r) { return 5 * r * r; };
  Test test4("third test", funct3, funct3, funct, [](double r) { return -195 * r * r; }, 2, 5, 51000, 1, 10);
  test4.test(8, maxPart*4);
  test4.printResults();
}

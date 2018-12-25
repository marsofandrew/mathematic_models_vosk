//
// Created by marsofandrew on 23.12.18.
//
#include <iostream>
#include "../impl.hpp"

#include "Test2.hpp"

void lab2()
{
  Equations::function funConst = [](double r, double t) { return 1; };
  Equations::function funF = [](double r, double t) { return r - 1 / r; };
  Equations::function funRT = [](double r, double t) { return r * t; };

  Equations::function funLiner = [](double r, double t) { return r; };
  Equations::function funPolinom = [](double r, double t) { return r * r; };
  Equations::functionFt funt1 = [](double t) { return 1; };
  Equations::functionFt funtr = [](double r) { return r; };
  Equations::functionFt funConst3t = [](double t) { return 3; };

  const double T_MIN = 0;
  const double T_MAX = 1;
  const double R_MIN = 1;
  const double R_MAX = 2;
  Test2 test1("const", T_MIN, T_MAX, R_MIN, R_MAX, funConst, funConst, funConst, funt1, funt1, 1, funt1, funConst);
  test1.test();
  test1.printResults(&std::cout);

  Test2 test2("k linear", T_MIN, T_MAX, R_MIN, R_MAX, funLiner, funConst, funConst, funt1, funt1, 1, funt1, funConst);
  test2.test();
  test2.printResults(&std::cout);

  Test2 test3("u linear", T_MIN, T_MAX, R_MIN, R_MAX, funConst, funConst, funF, funt1, funConst3t, 1, funtr, funLiner);
  test3.test();
  test3.printResults(&std::cout);

  Test2 test4("u&k linear", T_MIN, T_MAX, R_MIN, R_MAX, funLiner, funConst,
              [](const double r, const double t) { return r - 2; },
              funt1, [](const double t) { return 4; }, 1, funtr, funLiner);
  test4.test();
  test4.printResults(&std::cout);

  Test2 test5("u&k polinominal", T_MIN, T_MAX, R_MIN, R_MAX, funPolinom, funConst,
              [](const double r, const double t) { return -7 * r * r; },
              funt1, [](const double t) { return 20; }, 1, [](const double r) { return r * r; }, funPolinom);
  test5.test();
  test5.printResults(&std::cout);

  Test2 test6("u(r,t)", T_MIN, T_MAX, R_MIN, R_MAX, funConst, funConst,
              [](const double r, const double t) { return r + r * t - t / r; },
              [](const double t) { return t; }, [](const double t) { return 3 * t; }, 1,
              [](const double r) { return 0; }, funRT);
  test4.test();
  test4.printResults(&std::cout);

}

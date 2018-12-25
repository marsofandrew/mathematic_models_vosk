//
// Created by marsofandrew on 23.12.18.
//
#include <iostream>
#include "../impl.hpp"

#include "Test2.hpp"



void lab2()
{
  Equations::function funConst = [](double r, double t) { return 1; };
  Equations::function funF = [](double r, double t) { return r-1/r; };

  Equations::function funLiner = [](double r, double t) { return r; };
  Equations::functionFt funt1 = [](double t) { return 1; };
  Equations::functionFt funtr = [](double r) { return r; };
  Equations::functionFt funConst4t = [](double t) { return 4; };

  const double T_MIN = 0;
  const double T_MAX = 1;
  const double R_MIN = 0;
  const double R_MAX = 1;
  Test2 test1("const", T_MIN, T_MAX, R_MIN, R_MAX, funConst, funConst, funConst, funt1, funt1, 1, funt1, funConst);
  //test1.test();
  //test1.printResults(&std::cout);

  Test2 test2("k linear", T_MIN, T_MAX, R_MIN, R_MAX, funLiner, funConst, funConst, funt1, funt1, 1, funt1, funConst);
  //test2.test();
  //test2.printResults(&std::cout);

  Test2 test3("u linear", T_MIN, T_MAX, R_MIN+1, R_MAX+1, funConst, funConst, funConst, funt1, funConst4t, 1, funtr, funLiner);
  test3.test();
  test3.printResults(&std::cout);
}

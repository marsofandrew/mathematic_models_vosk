//
// Created by marsofandrew on 16.09.18.
//
#define BOOST_TEST_MODULE main_module

#include <boost/test/included/unit_test.hpp>
#include "supportive_functions.hpp"
#include <vector>
#include <exception>
#include <cstdio>

BOOST_AUTO_TEST_SUITE(check_solveMatrixSweepMethod)

  BOOST_AUTO_TEST_CASE(invalid_length_a)
  {
    unsigned long n = 4;
    std::vector<double> a(3);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> f(n);
    BOOST_CHECK_THROW(solveMatrixSweepMethod(n, a, c, b, f), std::exception);
  }

  BOOST_AUTO_TEST_CASE(invalid_length_b)
  {
    unsigned long n = 4;
    std::vector<double> a(n);
    std::vector<double> b(3);
    std::vector<double> c(n);
    std::vector<double> f(n);
    BOOST_CHECK_THROW(solveMatrixSweepMethod(n, a, c, b, f), std::exception);
  }

  BOOST_AUTO_TEST_CASE(invalid_length_c)
  {
    unsigned long n = 4;
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(3);
    std::vector<double> f(n);
    BOOST_CHECK_THROW(solveMatrixSweepMethod(n, a, c, b, f), std::exception);
  }

  BOOST_AUTO_TEST_CASE(invalid_length_f)
  {
    unsigned long n = 4;
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c(n);
    std::vector<double> f(3);
    BOOST_CHECK_THROW(solveMatrixSweepMethod(n, a, c, b, f), std::exception);
  }

  BOOST_AUTO_TEST_CASE(invalid_value_of_c_0)
  {
    unsigned long n = 4;
    std::vector<double> a(n);
    std::vector<double> b(n);
    std::vector<double> c = {0, 1, 1, 1};
    std::vector<double> f(n);
    BOOST_CHECK_THROW(solveMatrixSweepMethod(n, a, c, b, f), std::exception);
  }

  BOOST_AUTO_TEST_CASE(solveMatrix)
  {
    unsigned long n = 4;
    std::vector<double> a = {0, 1, 2, 3};
    std::vector<double> c = {2, 3, 6, 4};
    std::vector<double> b = {1, 115, 3, 0};
    std::vector<double> f = {3, 5, 10, 7};

    std::vector<double> solution = solveMatrixSweepMethod(n, a, c, b, f);

    BOOST_CHECK_EQUAL(solution.size(), n);
    BOOST_CHECK_CLOSE(c[0] * solution[0] + b[0] * solution[1], f[0], 10e-14);
    std::cout << f[0] - (c[0] * solution[0] + b[0] * solution[1]) << "\n";
    for (int i = 1; i < n - 1; ++i) {
      BOOST_CHECK_CLOSE(a[i] * solution[i - 1] + c[i] * solution[i] + b[i] * solution[i + 1], f[i], 10e-14);
      std::cout << f[i] - (a[i] * solution[i - 1] + c[i] * solution[i] + b[i] * solution[i + 1]) << "\n";
    }
    BOOST_CHECK_CLOSE(c[3] * solution[3] + a[3] * solution[2], f[3], 10e-14);
    std::cout << f[3] - (c[3] * solution[3] + a[3] * solution[2]) << "\n";
  }

BOOST_AUTO_TEST_SUITE_END()
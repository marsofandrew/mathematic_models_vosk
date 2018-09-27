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
    std::vector<double> a = {0, 1, 3, 2};
    std::vector<double> c = {2, 5, 5, 3};
    std::vector<double> b = {1, 3, 2, 0};
    std::vector<double> f = {4, 9, 10, 6};

    std::vector<double> expectedSolution = {8.0/9, 45.0 / 46, 4.0 / 5, 22.0 / 15};
    std::vector<double> solution = solveMatrixSweepMethod(n, a, c, b, f);

    BOOST_CHECK_EQUAL(solution.size(), n);
    for (int i = 0; i < solution.size(); ++i) {
      BOOST_CHECK_CLOSE(solution[i], expectedSolution[i], 10e-3);
    }
  }

BOOST_AUTO_TEST_SUITE_END()
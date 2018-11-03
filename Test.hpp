//
// Created by marsofandrew on 03.11.18.
//

#ifndef MATHEMATIC_MODELS_VOSK_TEST_HPP
#define MATHEMATIC_MODELS_VOSK_TEST_HPP

#include <sstream>
#include "Equation.hpp"

class Test
{
public:
  Test(const Equation::funct &u, const Equation::funct &k, const Equation::funct &q, const Equation::funct &f,
       const double capa, const double nu1, const double nu2, const double rMin, const double rMax);

  void test(const std::size_t minPart, const std::size_t maxPart);

  void printResults();

private:
  const Equation::funct u_;
  const Equation::funct k_;
  const Equation::funct q_;
  const Equation::funct f_;
  const double capa_;
  const double nu1_;
  const double nu2_;
  const double rMin_;
  const double rMax_;
  std::stringstream tmpOutput_;

  void printToTmpOutput(const std::vector<double> &solvedVector, const std::vector<double> &correctVector, std::size_t );
  std::vector<double> countCorrectSolution(std::size_t n, double rMin, double rMax);
};

#endif //MATHEMATIC_MODELS_VOSK_TEST_HPP

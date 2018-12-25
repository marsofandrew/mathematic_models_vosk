//
// Created by marsofandrew on 03.11.18.
//

#include <algorithm>
#include <iostream>
#include "Test.hpp"
#include "Equation.hpp"


Test::Test(const std::string &name, const Equation::funct &u, const Equation::funct &k,
           const Equation::funct &q, const Equation::funct &f, const double capa,
           const double nu1, const double nu2, const double rMin, const double rMax) :
  name_(name),
  u_(u),
  k_(k),
  q_(q),
  f_(f),
  capa_(capa),
  nu1_(nu1),
  nu2_(nu2),
  rMin_(rMin),
  rMax_(rMax),
  tmpOutput_(""),
  prevDiff_(-1.0) {}

void Test::test(const std::size_t minPart, const std::size_t maxPart)
{
  for (std::size_t n = minPart; n <= maxPart; n *= 2) {
    Equation equation(k_, q_, f_, capa_, nu1_, nu2_, n, rMin_, rMax_);
    printToTmpOutput(equation.solve(), countCorrectSolution(n, rMin_, rMax_), n);
  }
}

void Test::printToTmpOutput(const std::vector<double> &solvedVector,
                            const std::vector<double> &correctVector, std::size_t n)
{
  std::vector<double> difference(n+1);
  tmpOutput_ << "\n------------------- N = " << n << "-------------------\n";
  for (int i = 0; i < solvedVector.size(); ++i) {
    difference[i] = correctVector[i] - solvedVector[i];
  }
  double currentDiff = std::abs(
    *std::max_element(difference.begin(), difference.end(), [](const double &a, const double &b)
    {
      return std::abs(a) < std::abs(b);
    }));
  tmpOutput_ << "max diff = "
             << currentDiff << "\n";
  if (prevDiff_ != -1) {
    tmpOutput_ << "diff prev/current = " << prevDiff_/currentDiff << "\n";
  }
  tmpOutput_ << "---------------------------------------------------------\n";
  prevDiff_ = currentDiff;
}

void Test::printResults()
{
  std::cout << "\n----------" << name_ << "---------------------------\n";
  std::cout << tmpOutput_.rdbuf();
}



std::vector<double> Test::countCorrectSolution(std::size_t n, double rMin, double rMax)
{
  std::vector<double> retVector(n+1);
  const double h = (rMax - rMin) / n;
  for (std::size_t i = 0; i <= n; ++i) {
    retVector[i] = (u_(rMin + i * h));
  }
  return retVector;
}


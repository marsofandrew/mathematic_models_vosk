//
// Created by marsofandrew on 27.09.18.
//

#ifndef MATHEMATIC_MODELS_VOSK_EQUATION_HPP
#define MATHEMATIC_MODELS_VOSK_EQUATION_HPP

#include <functional>
#include <vector>

class Equation
{
public:
  using funct=std::function<double (double)>;
  Equation(const funct &k,
           const funct &q,
           const funct &f,
           const double capa,
           const double nu1,
           const double nu2_,
           const std::size_t N,
           const double rMin,
           const double rMax);
  std::vector<double> solve() const;

private:
  const Equation::funct k_;
  const Equation::funct q_;
  const Equation::funct f_;
  const double capa_;
  const double nu1_;
  const double nu2_;
  const std::size_t N_;
  const double rMin_;
  const double rMax_;
  double h_;
  std::vector<double> rHalfMinus_;
  std::vector<double> rHalfPlus_;
  std::vector<double> r_;
  std::vector<double> rightSide_;
  std::vector<double> a_;
  std::vector<double> b_;
  std::vector<double> c_;
  void init();
  void countCofficients();
};

#endif //MATHEMATIC_MODELS_VOSK_EQUATION_HPP

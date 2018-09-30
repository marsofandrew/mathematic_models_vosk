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
  Equation(funct k, funct q, funct f, double capa, double mu1, double mu2, std::size_t N, double Rmin, double Rright);
  std::vector<double> solve();

private:
  Equation::funct k_;
  Equation::funct q_;
  Equation::funct f_;
  const double capa_;
  const double mu1_;
  const double mu2_;
  const std::size_t N_;
  const double Rmin_;
  const double Rright_;
  double h_;
  std::vector<double> rHalfMinus_;
  std::vector<double> rHalfPlus_;
  std::vector<double> r_;
  std::vector<double> v_;

  void init();
  void countF();

};

#endif //MATHEMATIC_MODELS_VOSK_EQUATION_HPP

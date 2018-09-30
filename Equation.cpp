//
// Created by marsofandrew on 27.09.18.
//

#include "Equation.hpp"
#include "supportive_functions.hpp"

Equation::Equation(funct k, funct q, funct f,
                   double capa, double mu1, double mu2, std::size_t N, double Rmin, double Rright) :
  k_(k),
  q_(q),
  f_(f),
  capa_(capa),
  mu1_(mu1),
  mu2_(mu2),
  N_(N),
  Rmin_(Rmin),
  Rright_(Rright),
  h_((Rright_ - Rmin_) / N_),
  rHalfMinus_(N_),
  rHalfPlus_(N_),
  r_(N_),
  rightSide_(N_),
  a_(N_),
  b_(N_),
  c_(N_)
{
  init();
}

std::vector<double> Equation::solve()
{
  return solveMatrixSweepMethod(a_, c_, b_, f_);
}

void Equation::init()
{
  for (int i = 0; i < N_; ++i) {
    r_.emplace_back(Rmin_ + i * h_);
  }
  for (int i = 1; i < N_; ++i) {
    rHalfMinus_.emplace_back(r_[i - 1] + h_ / 2);
  }
  for (int j = 0; j < N_ - 1; ++j) {
    rHalfPlus_.emplace_back(r_[j] + h_ / 2);
  }
  rightSide_[N_-1] = h_/2 * r_[N_-1] * f_(r_[N_-1]);
  for (int i = 1; i < N_-1; i++){
	double r_i = r_[i];
	rightSide_[i] = h * r_i * f_(r_i);
  }
  rightSide_[0] = mu1_; //TODO: check it  
}

void Equation::countCofficients()
{
  a_[0] = 0;
}





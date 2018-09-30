//
// Created by marsofandrew on 27.09.18.
//

#include "Equation.hpp"

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
  r_(N_)
{
  init();
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
}



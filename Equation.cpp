//
// Created by marsofandrew on 27.09.18.
//

#include "Equation.hpp"

#include <utility>
#include "supportive_functions.hpp"

Equation::Equation(funct k, funct q, funct f,
                   double capa, double mu1, std::size_t N, double Rmin, double Rright) :
  k_(std::move(k)),
  q_(std::move(q)),
  f_(std::move(f)),
  capa_(capa),
  mu1_(mu1),
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
  countCofficients();
}

std::vector<double> Equation::solve() const
{
  return solveMatrixSweepMethod(a_, c_, b_, rightSide_);
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

  rightSide_[N_ - 1] = h_ / 2 * r_[N_ - 1] * f_(r_[N_ - 1]); //TODO: check it
  for (int i = 1; i < N_ - 1; i++) {
    double r_i = r_[i];
    rightSide_[i] = h_ * r_i * f_(r_i);
  }
  rightSide_[0] = mu1_; //TODO: check it  
}

void Equation::countCofficients()
{
  a_[0] = 0;
  b_[0] = 0;
  for (int i = 0; i < N_ - 1; i++) {
    double r_hm = rHalfMinus_[i];
    double r_hp = rHalfPlus_[i];
    a_[i] = -r_hm * k_(r_hm) / h_;
    b_[i] = -r_hp * k_(r_hp) / h_;
    c_[i] = (r_hp * k_(r_hp) + r_hm * k_(r_hm)) / h_ + h_ * q_(r_[i]) * r_[i];
  }

  std::size_t i = N_ - 1;
  double r_hm = rHalfMinus_[i];
  double r_hp = rHalfPlus_[i];
  b_[i] = 0;
  a_[i] = -r_hm * k_(r_hm) / h_;
  c_[i] = r_[i] * capa_ + (r_hp * k_(r_hp)) / h_ + h_ / 2 * r_[i] * q_(r_[i]);

}





//
// Created by marsofandrew on 23.12.18.
//

#ifndef MATHEMATIC_MODELS_VOSK_EQUATION2_HPP
#define MATHEMATIC_MODELS_VOSK_EQUATION2_HPP

#include <cstddef>
#include <functional>
#include "Matrix.hpp"
#include "../supportive_functions.hpp"

enum SolveMethod
{
  EXPLICIT,
  IMPLICIT
};

namespace Equations
{
  using function=std::function<double(double r, double t)>;
  using functionFt=std::function<double(double t)>;
}

template<std::size_t Nr, std::size_t Nt>
class Equation
{
public:

  Equation<Nr, Nt>(const double Tmin, const double Tmax, const double Rmin,
                   const double Rmax, const Equations::function &k, const Equations::function &q,
                   const Equations::function &f, const Equations::functionFt &nu1,
                   const Equations::functionFt &nu2, const double capa, const Equations::functionFt &mu);

  Matrix<double, Nr + 1, Nt + 1> solve(const SolveMethod solveMethod);

private:
  const double tMin_;
  const double tMax_;
  const double rMin_;
  const double rMax_;
  const Equations::function k_;
  const Equations::function q_;
  const Equations::function f_;
  const Equations::functionFt nu1_;
  const Equations::functionFt nu2_;
  const double capa_;
  const Equations::functionFt mu_;

  double tau_;
  double h_;

  std::vector<double> rHalfMinus_;
  std::vector<double> rHalfPlus_;
  std::vector<double> r_;

  void init();

  Vector<double, Nr + 1> countF(const double t);

  Matrix<double, Nr + 1, Nr + 1> countC(const double t);

  Vector<double, Nr + 1>
  countBySweepMethod(Matrix<double, Nr + 1, Nr + 1> &c, Vector<double, Nr + 1> &f);

  void insertSolveColumn(const std::size_t columnIndex, Vector<double, Nr + 1> &column,
                         Matrix<double, Nr + 1, Nt + 1> &matrix);

};

#endif //MATHEMATIC_MODELS_VOSK_EQUATION2_HPP

template<std::size_t Nr, std::size_t Nt>
Equation<Nr, Nt>::Equation(const double Tmin, const double Tmax, const double Rmin,
                           const double Rmax, const Equations::function &k, const Equations::function &q,
                           const Equations::function &f, const Equations::functionFt &nu1,
                           const Equations::functionFt &nu2,
                           const double capa, const Equations::functionFt &mu) :
  tMin_(Tmin),
  tMax_(Tmax),
  rMin_(Rmin),
  rMax_(Rmax),
  k_(k),
  q_(q),
  f_(f),
  nu1_(nu1),
  nu2_(nu2),
  capa_(capa),
  mu_(mu),
  tau_((tMax_ - tMin_) / Nt),
  h_((rMax_ - rMin_) / Nr),
  rHalfMinus_(Nr + 1),
  rHalfPlus_(Nr + 1),
  r_(Nr + 1)
{

  init();
}

template<std::size_t Nr, std::size_t Nt>
Matrix<double, Nr + 1, Nt + 1> Equation<Nr, Nt>::solve(const SolveMethod solveMethod)
{
  Matrix<double, Nr + 1, Nr + 1> E = Matrix<double, Nr + 1, Nr + 1>::E();
  Matrix<double, Nr + 1, Nt + 1> matrix = {};
  Vector<double, Nr + 1> prevColumn = {};

  for (int i = 0; i < prevColumn.getAmountOfRows(); ++i) {
    prevColumn.getMatrix()[i][0] = mu_(r_[i]);
  }

  insertSolveColumn(0, prevColumn, matrix);
  for (std::size_t j = 1; j < matrix.getAmountOfColumns(); ++j) {
    const double tPrev = tMin_ + tau_ * (j - 1);
    const double t = tMin_ + tau_ * (j);
    Vector<double, Nr + 1> current = {};

    if (solveMethod == EXPLICIT) {

      current = prevColumn + (countC(tPrev) * prevColumn + countF(tPrev)) * tau_;
    }

    if (solveMethod == IMPLICIT) {
      Matrix<double, Nr + 1, Nr + 1> C = E * (1 / tau_) - countC(t);
      Vector<double, Nr + 1> f = countF(t) + prevColumn * (1 / tau_);
      current = countBySweepMethod(C, f);
    }

    insertSolveColumn(j, current, matrix);
    prevColumn = current;
  }
  return matrix;
}

template<std::size_t Nr, std::size_t Nt>
void Equation<Nr, Nt>::init()
{
  for (int i = 0; i < Nr + 1; ++i) {
    r_[i] = (rMin_ + i * h_);
  }

  for (int i = 1; i < Nr + 1; ++i) {
    rHalfMinus_[i] = (r_[i - 1] + h_ / 2);
  }
  for (int j = 0; j < Nr + 1 - 1; ++j) {
    rHalfPlus_[j] = (r_[j] + h_ / 2);
  }
}

template<std::size_t Nr, std::size_t Nt>
Vector<double, Nr + 1> Equation<Nr, Nt>::countF(const double t)
{
  Vector<double, Nr + 1> tmp = {};
  tmp.getMatrix()[0][0] = nu1_(t);
  for (int i = 1; i < tmp.getAmountOfRows() - 1; ++i) {
    tmp.getMatrix()[i][0] = f_(r_[i], t);
  }
  const std::size_t N = Nr;
  tmp.getMatrix()[N][0] = f_(r_[N], t) + 2 * (nu2_(t) / h_);
  return tmp;
}

template<std::size_t Nr, std::size_t Nt>
Matrix<double, Nr + 1, Nr + 1> Equation<Nr, Nt>::countC(const double t)
{
  Matrix<double, Nr + 1, Nr + 1> tmp = {};
  tmp.getMatrix()[0][0] = -1;

  double r = 0;
  double rHm = 0;
  double rHp = 0;
  for (int i = 1; i < tmp.getAmountOfRows() - 1; ++i) {
    r = r_[i];
    rHm = rHalfMinus_[i];
    rHp = rHalfPlus_[i];

    tmp.getMatrix()[i][i - 1] = (rHm * k_(rHm, t)) / (h_ * h_ * r);
    tmp.getMatrix()[i][i + 1] = (rHp * k_(rHp, t)) / (h_ * h_ * r);
    tmp.getMatrix()[i][i] = -((rHp * k_(rHp, t) + rHm * k_(rHm, t)) / h_ + h_ * q_(r, t) * r) / (h_ * r);
  }

  const std::size_t N = tmp.getAmountOfRows() - 1;
  r = r_[N];
  rHm = rHalfMinus_[N];
  tmp.getMatrix()[N][N - 1] = (rHm * k_(rHm, t) * 2) / (h_ * h_ * r);
  tmp.getMatrix()[N][N] = -(r * capa_ + rHm * k_(rHm, t) / h_ + h_ / 2 * r * q_(r, t)) * 2 / (h_ * r);
  return tmp;
}

template<std::size_t Nr, std::size_t Nt>
void Equation<Nr, Nt>::insertSolveColumn(const std::size_t columnIndex, Vector<double, Nr + 1> &column,
                                         Matrix<double, Nr + 1, Nt + 1> &matrix)
{
  for (int i = 0; i < matrix.getAmountOfRows(); ++i) {
    matrix.getMatrix()[i][columnIndex] = column.getMatrix()[i][0];
  }
}

template<std::size_t Nr, std::size_t Nt>
Vector<double, Nr + 1>
Equation<Nr, Nt>::countBySweepMethod(Matrix<double, Nr + 1, Nr + 1> &c, Vector<double, Nr + 1> &f)
{
  std::vector<double> right = {};
  for (int i = 0; i < f.getAmountOfRows(); ++i) {
    right.push_back(f.getMatrix()[i][0]);
  }
  std::vector<double> a(Nr + 1);
  std::vector<double> b(Nr + 1);
  std::vector<double> midle(Nr + 1);
  a[0] = 0;
  b[0] = c.getMatrix()[0][1];
  midle[0] = c.getMatrix()[0][0];
  for (int j = 1; j < Nr; ++j) {
    a[j] = c.getMatrix()[j][j - 1];
    b[j] = c.getMatrix()[j][j + 1];
    midle[j] = c.getMatrix()[j][j];
  }
  const std::size_t N = Nr;
  a[N] = c.getMatrix()[N][N - 1];
  midle[N] = c.getMatrix()[N][N];
  b[N] = 0;
  std::vector<double> tmp = solveMatrixSweepMethod(a, midle, b, right);
  Vector<double, Nr + 1> vector = {};
  for (int k = 0; k < vector.getAmountOfRows(); ++k) {
    vector.getMatrix()[k][0] = tmp[k];
  }

  return vector;
}



//
// Created by marsofandrew on 24.12.18.
//

#ifndef MATHEMATIC_MODELS_VOSK_TEST2_HPP
#define MATHEMATIC_MODELS_VOSK_TEST2_HPP

#include "Equation.hpp"
#include "Matrix.hpp"
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>

namespace detail1
{
  constexpr std::size_t NT_SIZE = 7;
  constexpr std::size_t NR_SIZE = 7;
  constexpr std::size_t NT[NT_SIZE] = {4, 8, 16, 32, 64, 128, 256};
  constexpr std::size_t NR[NR_SIZE] = {4, 8, 16, 32, 64, 128, 256};

  constexpr std::size_t cexpr(const std::size_t x) { return x; }
}

class Test2
{
public:
  Test2(const std::string name, const double Tmin, const double Tmax, const double Rmin,
        const double Rmax, const Equations::function &k, const Equations::function &q,
        const Equations::function &f, const Equations::functionFt &nu1,
        const Equations::functionFt &nu2, const double capa, const Equations::functionFt &mu,
        const Equations::function &u);

  void test();

  void printResults(std::ostream *ostream);

private:
  const std::string name_;
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
  const Equations::function u_;

  std::stringstream buffer_;

  template<std::size_t Nr, std::size_t Nt>
  Matrix<double, Nr + 1, Nt + 1> countU();

  template<std::size_t Nr, std::size_t Nt>
  void iteration();

  template<std::size_t Nr, std::size_t Nt>
  void print(const SolveMethod method, Matrix<double, Nr, Nt> &matrix);
};

#endif //MATHEMATIC_MODELS_VOSK_TEST2_HPP

Test2::Test2(const std::string name, const double Tmin, const double Tmax, const double Rmin, const double Rmax,
             const Equations::function &k,
             const Equations::function &q, const Equations::function &f, const Equations::functionFt &nu1,
             const Equations::functionFt &nu2, const double capa, const Equations::functionFt &mu,
             const Equations::function &u) :
  name_(name),
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
  u_(u),
  buffer_() {}

void Test2::test()
{

  iteration<2, 2>();
  /*iteration<32, 2>();
  iteration<128, 2>();
  iteration<256, 2>();

  iteration<4, 4>();
  iteration<32, 4>();
  iteration<64, 4>();
  iteration<128, 4>();

  iteration<8, 8>();
  iteration<64, 8>();
  iteration<128, 8>();
  iteration<256, 8>();

  iteration<16, 16>();
  iteration<64, 16>();
  iteration<128, 16>();
  iteration<256, 16>();

  iteration<32, 32>();
  iteration<64, 32>();
  iteration<128, 32>();
  iteration<256, 32>();

  iteration<32, 64>();
  iteration<64, 64>();
  iteration<128, 64>();
  iteration<256, 64>();

  iteration<32, 128>();
  iteration<64, 128>();
  iteration<128, 128>();
  iteration<256, 128>();

  iteration<32, 256>();
  iteration<64, 256>();
  iteration<128, 256>();
  iteration<256, 256>();
*/
}

void Test2::printResults(std::ostream *ostream)
{
  (*ostream) << "---------" << name_ << "----------\n";
  (*ostream) << buffer_.rdbuf();
}

template<std::size_t Nr, std::size_t Nt>
Matrix<double, Nr + 1, Nt + 1> Test2::countU()
{
  const double tau = (tMax_ - tMin_) / Nt;
  const double h = (rMax_ - rMin_) / Nr;

  Matrix<double, Nr + 1, Nt + 1> matrix = {};
  for (int i = 0; i < matrix.getAmountOfRows(); ++i) {
    double r = rMin_ + i * h;
    for (int j = 0; j < matrix.getAmountOfColumns(); ++j) {
      double t = tMin_ + j * tau;
      matrix.getMatrix()[i][j] = u_(r, t);
    }
  }
  return matrix;
}

template<std::size_t Nr, std::size_t Nt>
void Test2::iteration()
{
  Equation<Nr, Nt> equation(tMin_, tMax_, rMin_, rMax_, k_, q_, f_, nu1_, nu2_, capa_, mu_);
  Matrix<double, Nr + 1, Nt + 1> vExp = equation.solve(SolveMethod::EXPLICIT);
  Matrix<double, Nr + 1, Nt + 1> vImp = equation.solve(SolveMethod::IMPLICIT);
  Matrix<double, Nr + 1, Nt + 1> correct = countU<Nr, Nt>();

  vExp -= correct;
  vImp -= correct;
  buffer_ << "Nt = " << Nt << " Nr = " << Nr << "\n";
  print(SolveMethod::EXPLICIT, vExp);
  print(SolveMethod::IMPLICIT, vImp);
  buffer_ << "\n\n";
}

template<std::size_t Nr, std::size_t Nt>
void Test2::print(const SolveMethod method, Matrix<double, Nr, Nt> &matrix)
{
  std::vector<double> maxElements;
  std::transform(matrix.getMatrix().begin(), matrix.getMatrix().end(), std::back_inserter(maxElements),
                 [](std::vector<double> vector)
                 {
                   return std::abs(*std::max_element(vector.begin(), vector.end(), [](const double a, const double b)
                   {
                     return std::abs(a) < std::abs(b);
                   }));
                 });
  double max = *std::max_element(maxElements.begin(), maxElements.end());

  if (method == EXPLICIT) {
    buffer_ << "EXPLICIT: max error =  " << max << "\n";
  }
  if (method == IMPLICIT) {
    buffer_ << "IMPLICIT: max error =  " << max << "\n";
  }
}





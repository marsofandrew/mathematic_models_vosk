//
// Created by marsofandrew on 16.09.18.
//

#ifndef MATHEMATIC_MODELS_VOSK_SUPPORTIVE_FUNCTIONS_HPP
#define MATHEMATIC_MODELS_VOSK_SUPPORTIVE_FUNCTIONS_HPP

#include <vector>
#include <functional>

/**
 * solve Matrix by using sweep method
 * @param n amount of matrix rows
 * @param a lower diagonal [1;n-1]
 * @param c diagonal [0; n-1]
 * @param b upper diagonal [0; n-2]
 * @param f the right side of equation
 * @return std::vector<double> x - solution of equation
 */
std::vector<double> solveMatrixSweepMethod(const unsigned long n,  std::vector<double> a,
                        std::vector<double> c,
                        std::vector<double> b,
                        std::vector<double> f);

#endif //MATHEMATIC_MODELS_VOSK_SUPPORTIVE_FUNCTIONS_HPP

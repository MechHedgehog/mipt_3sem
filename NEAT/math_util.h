#include <cmath>
#include <vector>
#include <algorithm>

#ifndef NEAT_MATH_UTIL_H
#define NEAT_MATH_UTIL_H

double mean(std::vector <double> v);
double median(std::vector <double> v);
double median2(std::vector <double> v);
double variance(std::vector<double> v);
double stdev(std::vector<double> v);
std::vector<double> softmax(std::vector<double> v);

#endif//NEAT_MATH_UTIL_H

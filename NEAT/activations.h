#include <cmath>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>
#include "func.h"

#ifndef NEAT_ACTIVATIONS_H
#define NEAT_ACTIVATIONS_H

class sigmoid_activation : public func
{
public:
    double operator() (double z);
};

class tanh_activation : public func
{
public:
    double operator() (double z);
};

class sin_activation : public func
{
public:
    double operator() (double z);
};

class gauss_activation : public func
{
public:
    double operator() (double z);
};

class relu_activation : public func
{
public:
    double operator() (double z);
};

class elu_activation : public func
{
public:
    double operator() (double z);
};

class lelu_activation : public func
{
public:
    double operator() (double z);
};

class selu_activation : public func
{
public:
    double operator() (double z);
};

class softplus_activation : public func
{
public:
    double operator() (double z);
};

class identity_activation : public func
{
public:
    double operator() (double z);
};

class clamped_activation : public func
{
public:
    double operator() (double z);
};

class inv_activation : public func
{
public:
    double operator() (double z);
};

class log_activation : public func
{
public:
    double operator() (double z);
};

class exp_activation : public func
{
public:
    double operator() (double z);
};

class abs_activation : public func
{
public:
    double operator() (double z);
};

class hat_activation : public func
{
public:
    double operator() (double z);
};

class square_activation : public func
{
public:
    double operator() (double z);
};

class cube_activation : public func
{
public:
    double operator() (double z);
};

class ActivationFunctionSet
{
private:
    std::map <std::string, func> m;
public:
    ActivationFunctionSet();
    func get(std::string name);
    bool is_valid(std::string name);
};


#endif//NEAT_ACTIVATIONS_H

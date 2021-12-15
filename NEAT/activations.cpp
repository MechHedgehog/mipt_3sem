#include "activations.h"
#include "func.h"
#include <cmath>
#include <map>
#include <string>
#include <algorithm>
#include <iostream>

double sigmoid_activation::operator() (double z)
{
    z = std::max(-60.0, std::min(60.0, 5.0 * z));
    return 1 / (1 + exp(-z));
}

double tanh_activation:: operator() (double z)
{
    z = std::max(-60.0, std::min(60.0, 2.5 * z));
    return tanh(z);
}

double sin_activation:: operator() (double z)
{
    z = std::max(-60.0, std::min(60.0, 5.0 * z));
    return sin(z);
}

double gauss_activation:: operator() (double z)
{
    z = std::max(-3.4, std::min(3.4, z));
    return exp(-5 * z * z);
}

double relu_activation:: operator() (double z)
{
    return (z > 0 ? z : 0);
}

double elu_activation:: operator() (double z)
{
    return (z > 0 ? z : exp(z) - 1);
}

double lelu_activation:: operator() (double z)
{
    double leaky = 0.005;
    return (z > 0 ? z : leaky * z);
}

double selu_activation:: operator() (double z)
{
    double lam = 1.0507009873554804934193349852946;
    double alpha = 1.6732632423543772848170429916717;
    return (z > 0 ? lam * z : lam * alpha * (exp(z) - 1));
}

double softplus_activation:: operator() (double z)
{
    z = std::max(-60.0, std::min(60.0, 5.0 * z));
    return 0.2 + log(1 + exp(z));
}

double identity_activation:: operator() (double z)
{
    return z;
}

double clamped_activation:: operator() (double z)
{
    return std::max(-1.0, std::min(1.0, z));
}

double inv_activation:: operator() (double z)
{
    try
    {
        if(z == 0) throw 0;
        z = 1 / z;
        return z;
    }
    catch (int a)
    {
        return 0.0;
    }
}

double log_activation:: operator() (double z)
{
    z = std::max(1e-7, z);
    return log(z);
}

double exp_activation:: operator() (double z)
{
    z = std::max(-60.0, std::min(60.0, z));
    return exp(z);
}

double abs_activation:: operator() (double z)
{
    return std::abs(z);
}

double hat_activation:: operator() (double z)
{
    return std::max(0.0, 1 - std::abs(z));
}

double square_activation:: operator() (double z)
{
    return z * z;
}

double cube_activation:: operator() (double z)
{
    return z * z * z;
}


ActivationFunctionSet::ActivationFunctionSet()
{
    m.insert(std::make_pair("cube", cube_activation()));
    m.insert(std::make_pair("square", square_activation()));
    m.insert(std::make_pair("hat", hat_activation()));
    m.insert(std::make_pair("abs", abs_activation()));
    m.insert(std::make_pair("exp", exp_activation()));
    m.insert(std::make_pair("log", log_activation()));
    m.insert(std::make_pair("inv", inv_activation()));
    m.insert(std::make_pair("clamped_", clamped_activation()));
    m.insert(std::make_pair("identity", identity_activation()));
    m.insert(std::make_pair("softplus", softplus_activation()));
    m.insert(std::make_pair("selu", selu_activation()));
    m.insert(std::make_pair("lelu", lelu_activation()));
    m.insert(std::make_pair("elu", elu_activation()));
    m.insert(std::make_pair("relu", relu_activation()));
    m.insert(std::make_pair("gauss", gauss_activation()));
    m.insert(std::make_pair("sin", sin_activation()));
    m.insert(std::make_pair("tanh", tanh_activation()));
    m.insert(std::make_pair("sigmoid", sigmoid_activation()));
}

func ActivationFunctionSet::get(std::string name)
{
    try
    {
        if (m.count(name)) return m[name];
        throw(0);
    }
    catch (int a)
    {
        std::cerr << "NO such activation function";
        return m["identity"];
    }
}

bool ActivationFunctionSet:: is_valid(std::string name)
{
    return m.count(name);
}
#include "attributes.h"
#include <random>
#include <string>
#include <iostream>

double FloatAttributes::clamp(double value)
{
    return(std::max(std::min(value, max_value), min_value));
}
double FloatAttributes::init_value ()
{
    try
    {
        if (init_type == "gaussian" || init_type == "normal")
        {
            std::random_device rd{};
            std::mt19937 gen{rd()};
            std::normal_distribution<double> d{init_mean, init_stdev};
            return clamp(d(gen));
        }
        if (init_type == "uniform")
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<double> d(
                    std::max(min_value, init_mean - 2 * init_stdev),
                    std::min(max_value, init_mean + 2 * init_stdev));
            return d(gen);
        }
        throw 0;
    }
    catch (int a)
    {
        std::cerr << "unknown init type";
        return 0;
    }
}
double FloatAttributes::mutate_value(double value)
{
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> d(0,1);
    double r = d(gen);
    if(r < mutate_rate)
    {
        std::normal_distribution<double> dg{0, mutate_power};
        return (clamp(value + dg(gen)));
    }
    if(r < replace_rate + mutate_rate)
    {
        return init_value();
    }
    return value;
}


bool BoolAttribute:: mutate_value(bool value)
{
    if(value)
        mutate_rate += rate_to_false_add;
    else
        mutate_rate += rate_to_true_add;
    if(mutate_rate > 0)
    {
        std::random_device rd{};
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> d(0,1);
        double r = d(gen);
        if(r < mutate_rate)
            return (d(gen) < 0.5);
    }
    return value;
}

std::string StringAttribute:: mutate_value(std::string value)
{
    if(mutate_rate > 0)
    {
        std::random_device rd{};
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> d(0,1);
        double r = d(gen);
        if(r < mutate_rate)
        {
            std::uniform_int_distribution<int> di(0,options.size() - 1);
            return options[di(gen)];
        }
    }
    return value;
}

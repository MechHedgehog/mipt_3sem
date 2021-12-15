#include <random>
#include <string>
#include <iostream>

#ifndef NEAT_ATTRIBUTES_H
#define NEAT_ATTRIBUTES_H


class FloatAttributes
{
private:
    std::string name;
    double  init_mean;
    double init_stdev;
    std::string init_type = "gaussian";
    double replace_rate;
    double mutate_rate;
    double mutate_power;
    double max_value;
    double min_value;

public:
    double clamp(double value);
    double init_value ();
    double mutate_value(double value);
};

class BoolAttribute
{
private:
    double mutate_rate;
    double rate_to_true_add;
    double rate_to_false_add;

public:
    bool mutate_value(bool value);
};

class StringAttribute
{
private:
    std::string def;
    std::vector<std::string> options;
    double mutate_rate;

public:
    std::string mutate_value(std::string value);
};



#endif//NEAT_ATTRIBUTES_H

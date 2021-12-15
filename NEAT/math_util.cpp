#include <cmath>
#include <vector>
#include <algorithm>

double mean(std::vector <double> v)
{
    double sum_buf = 0;
    for(auto it = v.begin(); it != v.end(); it++)
        sum_buf += *it;
    return sum_buf / v.size();
}

double median(std::vector <double> v)
{
    std::sort(v.begin(), v.end());
    return v[v.size() / 2];
}

double median2(std::vector <double> v)
{
    if(v.size() <= 2) return mean(v);
    std::sort(v.begin(), v.end());
    if(v.size() % 2) return v[v.size() / 2];
    return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2;
}

double variance(std::vector<double> v)
{
    double m = mean(v);
    double sum_buf = 0;
    for(auto it = v.begin(); it != v.end(); it++)
        sum_buf += ((*it) - m) * ((*it) - m);
    return sum_buf / v.size();
}

double stdev(std::vector<double> v)
{
    return sqrt(variance(v));
}

std::vector<double> softmax(std::vector<double> v)
{
    std::vector<double> smax(v.size());
    double sum_buf = 0;
    for(int i = 0; i < smax.size(); i++)
    {
        smax[i] = exp(v[i]);
        sum_buf += smax[i];
    }
    for(int i = 0; i < smax.size(); i++)
        v[i] /= sum_buf;
    return smax;
}







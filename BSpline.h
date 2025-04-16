#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::cerr;


inline vector<double> knots_initialization(double lower, double upper, int degree, int num_control_points)
{
    int num_knots = num_control_points + degree + 1;
    vector<double> knots(num_knots);
    for(int i = 0; i < degree; ++i)
    {
        knots[i] = lower;
        knots[num_knots - 1 - i] = upper;
    }
    for(int i = 0; i < num_control_points - 1; ++i)
    {
        knots[degree + i] = lower + (upper - lower) * i / (num_control_points - 2);
    }
    return knots;
}



// B样条基函数计算（保持之前实现）
// 递归实现
inline double bspline_basis(int i, int p, double x, const std::vector<double>& knots) 
{
    if (p == 0) 
    {
        return (knots[i] <= x && x < knots[i+1]) ? 1.0 : 0.0;
    } 
    else 
    {
        double term1 = 0.0, term2 = 0.0;
        double denom = knots[i+p] - knots[i];
        if (denom != 0.0) 
        {
            double alpha = (x - knots[i]) / denom;
            term1 = alpha * bspline_basis(i, p-1, x, knots);
        }
        denom = knots[i+p+1] - knots[i+1];
        if (denom != 0.0) 
        {
            double beta = (knots[i+p+1] - x) / denom;
            term2 = beta * bspline_basis(i+1, p-1, x, knots);
        }
        return term1 + term2;
    }
}

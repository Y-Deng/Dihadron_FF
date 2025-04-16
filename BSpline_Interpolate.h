#pragma once

#include "BSpline.h"
#include "Tools.h"

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


inline vector<double> BSpline_coefficients(int degree, double lower, double upper, const vector<double>& sample_x, const vector<double>& sample_f)
{
    const int num_ctrl_points = sample_x.size();
    vector<double> knots = knots_initialization(lower, upper, degree, num_ctrl_points);

    // f_i = sum_j c_j * B_j(x_i)
    // b_i = sum_j A_ij * x_j
    // where b_i = f_i, A_ij = B_j(x_i), x_j = c_j
    vector< vector< double > > Bjxi(num_ctrl_points, vector<double>(num_ctrl_points));
    for (int i=0; i<num_ctrl_points; ++i) 
    {
        for(int j = 0; j < num_ctrl_points; ++j)
        {
            double basis = bspline_basis(j, degree, sample_x[i], knots);
            Bjxi[i][j] = basis;
        }
    }
    vector<double> coefficients = solve_linear_system(Bjxi, sample_f);
    
    return coefficients;
}

#pragma once

#include <iostream>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_interp.h>
#include "cmath"
#include "vector"
#include "string"
#include "fstream"
#include "sstream"
#include "array"


using std::vector;
using std::string;
using std::ifstream;
using std::stringstream;
using std::array;


class Spline_Interpolate_1D
{
    public:
        Spline_Interpolate_1D(const vector<double> &x_grid, const vector<double> &data)
            : n_points(x_grid.size()), x_lower_limit(x_grid.front()), x_upper_limit(x_grid.back())
        {
            if(data.size() != n_points)
            {
                throw std::invalid_argument("data size does not match x_grid size");
            }
            if (n_points < 4) {
                throw std::invalid_argument("x_grid must have at least four points");
            }

            acc = gsl_interp_accel_alloc();
            spline = gsl_spline_alloc(gsl_interp_cspline, n_points);
            gsl_spline_init(spline, x_grid.data(), data.data(), n_points);
        }

        ~Spline_Interpolate_1D()
        {
            gsl_spline_free(spline);
            gsl_interp_accel_free(acc);
        }

        double operator()(double x) const
        {
            if (x < x_lower_limit || x > x_upper_limit)
            {
                throw std::out_of_range("x is out of range of x_grid");
            }
            return gsl_spline_eval(spline, x, acc);
        }

    private:
        const int n_points;
        const double x_lower_limit;
        const double x_upper_limit;
        gsl_interp_accel* acc;
        gsl_spline* spline;
};

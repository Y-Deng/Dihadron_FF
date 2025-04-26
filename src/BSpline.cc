#include <Eigen/Dense>
#include <Eigen/Sparse>

#include "../include/BSpline.h"
#include "test_BSpline_interpolate.h"

#include <iostream>

using namespace Eigen;

using namespace std;

VectorXd knots_initialization(const double &lower, const double &upper, const int &degree,
                              const int &num_control_points)
{
    VectorXd knots(num_control_points + degree + 1);
    knots.segment(0, degree) = VectorXd::Constant(degree, lower);
    knots.segment(degree, num_control_points - degree + 1) =
        VectorXd::LinSpaced(num_control_points - degree + 1, lower, upper);
    knots.segment(num_control_points + 1, degree) = VectorXd::Constant(degree, upper);

    return knots;
}

double Bspline_basis(const int &i, const int &degree, const double &x, const VectorXd &knots)
{
    if (degree == 0)
    {
        return (knots(i) <= x && x < knots(i + 1)) ? 1.0 : 0.0;
    }
    else
    {
        double term1 = 0.0, term2 = 0.0;

        double denom = knots(i + degree) - knots(i);
        if (denom != 0.0)
        {
            double alpha = (x - knots(i)) / denom;
            term1 = alpha * Bspline_basis(i, degree - 1, x, knots);
        }
        denom = knots(i + degree + 1) - knots(i + 1);
        if (denom != 0.0)
        {
            double beta = (knots(i + degree + 1) - x) / denom;
            term2 = beta * Bspline_basis(i + 1, degree - 1, x, knots);
        }
        return term1 + term2;
    }
}
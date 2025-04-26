#pragma once
#include <Eigen/Dense>
#include <Eigen/Sparse>

Eigen::VectorXd knots_initialization(const double &lower, const double &upper, const int &degree,
                                     const int &num_control_points);

double Bspline_basis(const int &i, const int &p, const double &x, const Eigen::VectorXd &knots);
#pragma once

#include "BSpline.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/src/Core/Matrix.h>
#include <iostream>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

using Eigen::VectorXd;

vector<int> activeBasisFunctions(double x, const VectorXd &knots, int degree);

class BSplineInterpolate_1D
{
  public:
    BSplineInterpolate_1D();
    BSplineInterpolate_1D(const int &degree, const double &lower, const double &upper, const vector<double> &sample_x,
                          const vector<double> &sample_f);

    BSplineInterpolate_1D(const int &degree, const int &num_ctrl_points, const vector<double> &knots,
                          const vector<double> &coefficients);

    double operator()(const double &x) const;

    int save(const string &filename) const;
    int load(const string &filename);

    vector<double> get_coefficients() const;
    vector<double> get_knots() const;
    int get_degree() const;
    int get_num_ctrl_points() const;
    static VectorXd Calculate_Control_Points(const int &degree, const VectorXd &knots, const vector<double> &sample_x,
                                             const vector<double> &sample_f);

  private:
    int degree_;
    int num_ctrl_points_;
    VectorXd knots_;
    VectorXd coefficients_;
};

/*
The quadratic interpolate program
*/

class BSplineInterpolate_2D
{
  public:
    BSplineInterpolate_2D();

    BSplineInterpolate_2D(const int &x_degree, const int &y_degree, const double &x_lower, const double &x_upper,
                          const double &y_lower, const double &y_upper, const vector<double> &sample_x,
                          const vector<double> &sample_y, const vector<vector<double>> &sample_f);

    BSplineInterpolate_2D(const int &x_degree, const int &y_degree, const int &num_x_ctrl_points,
                          const int &num_y_ctrl_points, const vector<double> &x_knots, const vector<double> &y_knots,
                          const vector<vector<double>> &coefficients);

    int load(const string &filename);
    int save(const string &filename) const;

    double operator()(const double &x, const double &y) const;

    vector<vector<double>> get_coefficients() const;
    vector<double> get_x_knots() const;
    vector<double> get_y_knots() const;
    int get_num_x_ctrl_points() const;
    int get_num_y_ctrl_points() const;
    int get_x_degree() const;
    int get_y_degree() const;

    static vector<VectorXd> Calculate_Control_Points(const int &x_degree, const int &y_degree, const VectorXd &x_knots,
                                                     const VectorXd &y_knots, const vector<double> &sample_x,
                                                     const vector<double> &sample_y,
                                                     const vector<vector<double>> &sample_f);

  private:
    int x_degree_;
    int y_degree_;
    int num_x_ctrl_points_;
    int num_y_ctrl_points_;
    VectorXd x_knots_;
    VectorXd y_knots_;

    vector<VectorXd> coefficients_;
};

/*
The cubic interpolation
*/
class BSplineInterpolate_3D
{
  public:
    BSplineInterpolate_3D();
    BSplineInterpolate_3D(const int &x_degree, const int &y_degree, const int &z_degree, const double &x_lower,
                          const double &x_upper, const double &y_lower, const double &y_upper, const double &z_lower,
                          const double &z_upper, const vector<double> &sample_x, const vector<double> &sample_y,
                          const vector<double> &sample_z, const vector<vector<vector<double>>> &sample_f);

    double operator()(const double &x, const double &y, const double &z) const;

    int save(const string &filename) const;
    int load(const string &filename);

    vector<vector<vector<double>>> get_coefficients() const;
    vector<double> get_x_knots() const;
    vector<double> get_y_knots() const;
    vector<double> get_z_knots() const;
    int get_num_x_ctrl_points() const;
    int get_num_y_ctrl_points() const;
    int get_num_z_ctrl_points() const;
    int get_x_degree() const;
    int get_y_degree() const;
    int get_z_degree() const;

    static vector<vector<VectorXd>> Calculate_Control_Points(
        const int &x_degree, const int &y_degree, const int &z_degree, const VectorXd &x_knots, const VectorXd &y_knots,
        const VectorXd &z_knots, const vector<double> &sample_x, const vector<double> &sample_y,
        const vector<double> &sample_z, const vector<vector<vector<double>>> &sample_f);

  private:
    int x_degree_;
    int y_degree_;
    int z_degree_;
    int num_x_ctrl_points_;
    int num_y_ctrl_points_;
    int num_z_ctrl_points_;
    VectorXd x_knots_;
    VectorXd y_knots_;
    VectorXd z_knots_;
    vector<vector<VectorXd>> coefficients_;
};
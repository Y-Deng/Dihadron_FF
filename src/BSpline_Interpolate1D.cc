#include "../include/BSpline_Interpolate.h"
#include "BSpline.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <Eigen/src/Core/Matrix.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

using SpMat = SparseMatrix<double>;
using Elem = Triplet<double>;

VectorXd BSplineInterpolate_1D::Calculate_Control_Points(const int &degree, const VectorXd &knots,
                                                         const vector<double> &sample_x, const vector<double> &sample_f)
{
    const int num_ctrl_points = sample_x.size();

    Map<const VectorXd> Eigen_x(sample_x.data(), sample_x.size());
    Map<const VectorXd> Eigen_f(sample_f.data(), sample_f.size());

    vector<Elem> elem_list;
    for (int i = 0; i < num_ctrl_points; ++i)
    {
        vector<int> index_active_BSpline = activeBasisFunctions(Eigen_x(i), knots, degree);
        for (auto j : index_active_BSpline)
        {
            double basis = Bspline_basis(j, degree, Eigen_x(i), knots);
            elem_list.emplace_back(i, j, basis);
        }
    }

    SpMat A(num_ctrl_points, num_ctrl_points);
    A.setFromTriplets(elem_list.begin(), elem_list.end());
    VectorXd coefficients;
    SparseLU<SpMat> solver;
    solver.compute(A);
    coefficients = solver.solve(Eigen_f);

    if (solver.info() != Success)
        cerr << "求解失败！" << endl;

    return coefficients;
}
BSplineInterpolate_1D::BSplineInterpolate_1D(){};

BSplineInterpolate_1D::BSplineInterpolate_1D(const int &degree, const double &lower, const double &upper,
                                             const vector<double> &sample_x, const vector<double> &sample_f)
{
    degree_ = degree;
    num_ctrl_points_ = sample_x.size();

    knots_ = knots_initialization(lower, upper, degree, num_ctrl_points_);
    coefficients_ = Calculate_Control_Points(degree, knots_, sample_x, sample_f);
}

double BSplineInterpolate_1D::operator()(const double &x) const
{
    double sum = 0.0;
    vector<int> no_zere_index = activeBasisFunctions(x, knots_, degree_);

    for (auto j : no_zere_index)
    {
        double basis = Bspline_basis(j, degree_, x, knots_);
        sum += coefficients_[j] * basis;
    }
    return sum;
}

vector<double> BSplineInterpolate_1D::get_coefficients() const
{
    return vector<double>(coefficients_.data(), coefficients_.data() + coefficients_.size());
}

vector<double> BSplineInterpolate_1D::get_knots() const
{
    return vector<double>(knots_.data(), knots_.data() + knots_.size());
}

int BSplineInterpolate_1D::get_degree() const
{
    return degree_;
}

int BSplineInterpolate_1D::get_num_ctrl_points() const
{
    return num_ctrl_points_;
}

int BSplineInterpolate_1D::save(const string &filename) const
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error: Interpolation 1D output file cannot open! \nfile name: " << filename << endl;
        throw "Error: Interpolation 1D output file cannot open! \nfile name:" + filename;
    }

    outfile << "degree: " << degree_ << endl;
    outfile << "num_ctrl_points: " << num_ctrl_points_ << endl;

    outfile << "knots: ";
    for (int i = 0; i < num_ctrl_points_ - 1; ++i)
        outfile << knots_(i) << ", ";
    outfile << knots_(num_ctrl_points_ - 1) << endl;

    outfile << "coefficients: ";
    for (int i = 0; i < num_ctrl_points_ - 1; ++i)
        outfile << coefficients_(i) << ", ";
    outfile << coefficients_(num_ctrl_points_ - 1) << endl;

    outfile.close();

    return 0;
}

BSplineInterpolate_1D::BSplineInterpolate_1D(const int &degree, const int &num_ctrl_points, const vector<double> &knots,
                                             const vector<double> &coefficients)
{
    degree_ = degree;
    num_ctrl_points_ = num_ctrl_points;
    knots_ = VectorXd::Map(knots.data(), knots.size()).eval();
    coefficients_ = VectorXd::Map(coefficients.data(), coefficients.size()).eval();
}

int BSplineInterpolate_1D::load(const string &filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error: Interpolation 1D input file cannot open! \nfile name: " << filename << endl;
        throw "Error: Interpolation 1D input file cannot open! \nfile name:" + filename;
    }
    string line;
    getline(infile, line);
    degree_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    num_ctrl_points_ = stoi(line.substr(line.find(":") + 1));
    knots_ = VectorXd::Zero(num_ctrl_points_);
    coefficients_ = VectorXd::Zero(num_ctrl_points_);

    getline(infile, line);
    stringstream ss(line.substr(line.find(":") + 1));

    for (int i = 0; i < num_ctrl_points_; ++i)
    {
        ss >> knots_(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    getline(infile, line);
    stringstream ss2(line.substr(line.find(":") + 1));
    for (int i = 0; i < num_ctrl_points_; ++i)
    {
        ss2 >> coefficients_(i);
        if (ss2.peek() == ',')
            ss2.ignore();
    }

    infile.close();

    return 0;
}
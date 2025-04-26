#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/src/Core/Map.h>
#include <Eigen/src/Core/Matrix.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>

#include "../include/BSpline_Interpolate.h"
#include "../include/Tools.h"
#include "BSpline.h"

using namespace std;
using namespace Eigen;

using SpMat = SparseMatrix<double>;
using Elem = Triplet<double>;

vector<VectorXd> BSplineInterpolate_2D::Calculate_Control_Points(const int &x_degree, const int &y_degree,
                                                                 const VectorXd &x_knots, const VectorXd &y_knots,
                                                                 const vector<double> &sample_x,
                                                                 const vector<double> &sample_y,
                                                                 const vector<vector<double>> &sample_f)
{
    size_t n_x = sample_x.size();
    size_t n_y = sample_y.size();
    VectorXd EV_y = Map<const VectorXd>(sample_y.data(), sample_y.size());
    VectorXd EV_x = Map<const VectorXd>(sample_x.data(), sample_x.size());

    vector<VectorXd> Coefficients;

    vector<vector<double>> Mbi(n_y);
    for (size_t b = 0; b < n_y; ++b)
    {
        VectorXd Fb(n_x);
        vector<Elem> elem_list;
        for (size_t a = 0; a < n_x; ++a)
        {
            Fb(a) = sample_f[a][b];
            vector<int> index_active_BSpline = activeBasisFunctions(EV_x(a), x_knots, x_degree);

            for (auto i : index_active_BSpline)
            {
                double basis = Bspline_basis(i, x_degree, EV_x(a), x_knots);
                elem_list.emplace_back(a, i, basis);
            }
        }

        SpMat A(n_x, n_x);
        A.setFromTriplets(elem_list.begin(), elem_list.end());

        SparseLU<SpMat> solver;
        solver.compute(A);
        VectorXd Mi = solver.solve(Fb);
        Mbi[b] = vector<double>(Mi.data(), Mi.data() + Mi.size());
    }

    for (size_t i = 0; i < n_x; ++i)
    {
        VectorXd Mi(n_y);
        vector<Elem> elem_list;
        for (size_t b = 0; b < n_y; ++b)
        {
            Mi(b) = Mbi[b][i];
            vector<int> index_active_BSpline = activeBasisFunctions(EV_y(b), y_knots, y_degree);
            for (int j : index_active_BSpline)
            {
                double basis = Bspline_basis(j, y_degree, EV_y(b), y_knots);
                elem_list.emplace_back(b, j, basis);
            }
        }
        SpMat A(n_x, n_x);
        A.setFromTriplets(elem_list.begin(), elem_list.end());
        SparseLU<SpMat> solver;
        solver.compute(A);
        Coefficients.emplace_back(solver.solve(Mi));
    }

    return Coefficients;
}

BSplineInterpolate_2D::BSplineInterpolate_2D(const int &x_degree, const int &y_degree, const double &x_lower,
                                             const double &x_upper, const double &y_lower, const double &y_upper,
                                             const vector<double> &sample_x, const vector<double> &sample_y,
                                             const vector<vector<double>> &sample_f)

{
    x_degree_ = x_degree;
    y_degree_ = y_degree;
    num_x_ctrl_points_ = sample_x.size();
    num_y_ctrl_points_ = sample_y.size();
    x_knots_ = knots_initialization(x_lower, x_upper, x_degree, num_x_ctrl_points_);
    y_knots_ = knots_initialization(y_lower, y_upper, y_degree, num_y_ctrl_points_);
    coefficients_ = Calculate_Control_Points(x_degree, y_degree, x_knots_, y_knots_, sample_x, sample_y, sample_f);
}

BSplineInterpolate_2D::BSplineInterpolate_2D()
{
}
BSplineInterpolate_2D::BSplineInterpolate_2D(const int &x_degree, const int &y_degree, const int &num_x_ctrl_points,
                                             const int &num_y_ctrl_points, const vector<double> &x_knots,
                                             const vector<double> &y_knots, const vector<vector<double>> &coefficients)

{
    x_degree_ = x_degree;
    y_degree_ = y_degree;
    num_x_ctrl_points_ = num_x_ctrl_points;
    num_y_ctrl_points_ = num_y_ctrl_points;
    x_knots_ = VectorXd::Map(x_knots.data(), x_knots.size()).eval();
    y_knots_ = VectorXd::Map(y_knots.data(), y_knots.size()).eval();
    for (size_t i = 0; i < coefficients.size(); ++i)
    {
        coefficients_.emplace_back(VectorXd::Map(coefficients[i].data(), coefficients[i].size()).eval());
    }
}

int BSplineInterpolate_2D::load(const string &filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error: Interpolation 2D input file cannot open! \nfile name: " << filename << endl;
        throw "Error: Interpolation 2D input file cannot open! \nfile name:" + filename;
    }

    string line;

    getline(infile, line);
    x_degree_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    y_degree_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    num_x_ctrl_points_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    num_y_ctrl_points_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    stringstream ss(line.substr(line.find(":") + 1));
    vector<double> xk(num_x_ctrl_points_);
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        ss >> xk[i];
        if (ss.peek() == ',')
            ss.ignore();
    }
    x_knots_ = VectorXd::Map(xk.data(), xk.size());

    getline(infile, line);
    stringstream ss2(line.substr(line.find(":") + 1));
    vector<double> yk(num_y_ctrl_points_);
    for (int j = 0; j < num_y_ctrl_points_; ++j)
    {
        ss2 >> yk[j];
        if (ss2.peek() == ',')
            ss2.ignore();
    }
    y_knots_ = VectorXd::Map(yk.data(), yk.size());

    getline(infile, line);
    coefficients_.resize(num_x_ctrl_points_);
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        vector<double> temp(num_y_ctrl_points_);
        getline(infile, line);
        stringstream ss3(line);
        for (int j = 0; j < num_y_ctrl_points_; ++j)
        {
            ss3 >> temp[j];
            if (ss3.peek() == ',')
                ss3.ignore();
        }
        coefficients_[i] = VectorXd::Map(temp.data(), temp.size());
    }
    infile.close();

    return 1;
}

double BSplineInterpolate_2D::operator()(const double &x, const double &y) const
{
    vector<int> x_index = activeBasisFunctions(x, x_knots_, x_degree_);
    vector<int> y_index = activeBasisFunctions(y, y_knots_, y_degree_);

    double sum = 0.0;

    for (int i : x_index)
    {
        for (int j : y_index)
        {
            double basis_x = Bspline_basis(i, x_degree_, x, x_knots_);
            double basis_y = Bspline_basis(j, y_degree_, y, y_knots_);
            sum += coefficients_[i][j] * basis_x * basis_y;
        }
    }
    return sum;
}

vector<vector<double>> BSplineInterpolate_2D::get_coefficients() const
{
    vector<vector<double>> result(num_x_ctrl_points_);
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        result[i] = vector<double>(coefficients_[i].data(), coefficients_[i].data() + coefficients_[i].size());
    }
    return result;
}

vector<double> BSplineInterpolate_2D::get_x_knots() const
{
    return vector<double>(x_knots_.data(), x_knots_.data() + x_knots_.size());
}

vector<double> BSplineInterpolate_2D::get_y_knots() const
{
    return vector<double>(y_knots_.data(), y_knots_.data() + y_knots_.size());
}

int BSplineInterpolate_2D::get_num_x_ctrl_points() const
{
    return num_x_ctrl_points_;
}

int BSplineInterpolate_2D::get_num_y_ctrl_points() const
{
    return num_y_ctrl_points_;
}

int BSplineInterpolate_2D::get_x_degree() const
{
    return x_degree_;
}

int BSplineInterpolate_2D::get_y_degree() const
{
    return y_degree_;
}

int BSplineInterpolate_2D::save(const string &filename) const
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error: Interpolation 2D output file cannot open! \nfile name: " << filename << endl;
        throw "Error: Interpolation 2D output file cannot open! \nfile name:" + filename;
        return -1;
    }
    outfile << "x_degree: " << x_degree_ << endl;
    outfile << "y_degree: " << y_degree_ << endl;
    outfile << "num_x_ctrl_points: " << num_x_ctrl_points_ << endl;
    outfile << "num_y_ctrl_points: " << num_y_ctrl_points_ << endl;

    outfile << "x_knots: ";
    for (int i = 0; i < num_x_ctrl_points_ - 1; i++)
        outfile << x_knots_(i) << ", ";
    outfile << x_knots_(num_x_ctrl_points_ - 1) << endl;

    outfile << "y_knots: ";
    for (int i = 0; i < num_y_ctrl_points_ - 1; ++i)
        outfile << y_knots_(i) << ", ";
    outfile << y_knots_(num_y_ctrl_points_ - 1) << endl;

    outfile << "coefficients: " << endl;
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        for (int j = 0; j < num_y_ctrl_points_ - 1; ++j)
            outfile << coefficients_[i](j) << ", ";
        outfile << coefficients_[i](num_y_ctrl_points_ - 1) << endl;
    }

    outfile.close();

    return 0;
}
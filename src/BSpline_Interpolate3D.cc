
#include "../include/BSpline_Interpolate.h"
#include "BSpline.h"
#include "test_BSpline_interpolate.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>

#include <Eigen/src/Core/Map.h>
#include <Eigen/src/Core/Matrix.h>
#include <Eigen/src/SparseLU/SparseLU.h>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

using SpMat = SparseMatrix<double>;
using Elem = Triplet<double>;

vector<vector<VectorXd>> BSplineInterpolate_3D::Calculate_Control_Points(
    const int &x_degree, const int &y_degree, const int &z_degree, const VectorXd &x_knots, const VectorXd &y_knots,
    const VectorXd &z_knots, const vector<double> &sample_x, const vector<double> &sample_y,
    const vector<double> &sample_z, const vector<vector<vector<double>>> &sample_f)
{
    int n_x = sample_x.size();
    int n_y = sample_y.size();
    int n_z = sample_z.size();

    vector<vector<VectorXd>> Coefficients(n_x, vector<VectorXd>(n_y));

    VectorXd Eigen_x = VectorXd::Map(sample_x.data(), sample_x.size()).eval();
    VectorXd Eigen_y = VectorXd::Map(sample_y.data(), sample_y.size()).eval();
    VectorXd Eigen_z = VectorXd::Map(sample_z.data(), sample_z.size()).eval();

    vector<vector<vector<double>>> Nicj(n_x, vector<vector<double>>(n_z));
    vector<vector<vector<double>>> Mcbi(n_z, vector<vector<double>>(n_y));
    for (int c = 0; c < n_z; ++c)
    {
        for (int b = 0; b < n_y; ++b)
        {
            VectorXd Fbc_a(n_x);
            vector<Elem> elem_list;
            for (int a = 0; a < n_x; ++a)
            {
                Fbc_a(a) = sample_f[a][b][c];
                vector<int> index_active_BSpline = activeBasisFunctions(Eigen_x(a), x_knots, x_degree);
                for (int i : index_active_BSpline)
                {
                    double basis = Bspline_basis(i, x_degree, Eigen_x(a), x_knots);
                    elem_list.emplace_back(a, i, basis);
                }
            }
            SpMat A(n_x, n_x);
            A.setFromTriplets(elem_list.begin(), elem_list.end());
            SparseLU<SpMat> solver;
            solver.compute(A);
            VectorXd Mi = solver.solve(Fbc_a);
            Mcbi[c][b] = vector<double>(Mi.data(), Mi.data() + Mi.size());
        }
    }

    for (int i = 0; i < n_x; i++)
    {
        for (int c = 0; c < n_z; ++c)
        {
            VectorXd Mic_b(n_y);
            vector<Elem> elem_list;
            for (int b = 0; b < n_y; ++b)
            {
                Mic_b(b) = Mcbi[c][b][i];
                vector<int> index_active_BSpline = activeBasisFunctions(Eigen_y(b), y_knots, y_degree);
                for (int j : index_active_BSpline)
                {
                    double basis = Bspline_basis(j, y_degree, Eigen_y(b), y_knots);
                    elem_list.emplace_back(b, j, basis);
                }
            }
            SpMat A(n_y, n_y);
            A.setFromTriplets(elem_list.begin(), elem_list.end());
            SparseLU<SpMat> solver;
            solver.compute(A);
            VectorXd Nj = solver.solve(Mic_b);
            Nicj[i][c] = vector<double>(Nj.data(), Nj.data() + Nj.size());
        }
    }

    for (int i = 0; i < n_x; ++i)
    {
        for (int j = 0; j < n_y; ++j)
        {
            VectorXd Nij_c(n_z);
            vector<Elem> elem_list;
            for (int c = 0; c < n_z; ++c)
            {
                Nij_c(c) = Nicj[i][c][j];
                vector<int> index_active_BSpline = activeBasisFunctions(Eigen_z(c), z_knots, z_degree);
                for (int k : index_active_BSpline)
                {
                    double basis = Bspline_basis(k, z_degree, Eigen_z(c), z_knots);
                    elem_list.emplace_back(c, k, basis);
                }
            }
            SpMat A(n_z, n_z);
            A.setFromTriplets(elem_list.begin(), elem_list.end());
            SparseLU<SpMat> solver;
            solver.compute(A);
            VectorXd Ck = solver.solve(Nij_c);
            Coefficients[i][j] = Ck;
        }
    }
    return Coefficients;
}
/*
    后续添加任意维度自动求解程序。
*/

BSplineInterpolate_3D::BSplineInterpolate_3D()
{
}

BSplineInterpolate_3D::BSplineInterpolate_3D(const int &x_degree, const int &y_degree, const int &z_degree,
                                             const double &x_lower, const double &x_upper, const double &y_lower,
                                             const double &y_upper, const double &z_lower, const double &z_upper,
                                             const vector<double> &sample_x, const vector<double> &sample_y,
                                             const vector<double> &sample_z,
                                             const vector<vector<vector<double>>> &sample_f)

{
    x_degree_ = x_degree;
    y_degree_ = y_degree;
    z_degree_ = z_degree;
    num_x_ctrl_points_ = sample_x.size();
    num_y_ctrl_points_ = sample_y.size();
    num_z_ctrl_points_ = sample_z.size();
    x_knots_ = knots_initialization(x_lower, x_upper, x_degree, num_x_ctrl_points_);
    y_knots_ = knots_initialization(y_lower, y_upper, y_degree, num_y_ctrl_points_);
    z_knots_ = knots_initialization(z_lower, z_upper, z_degree, num_z_ctrl_points_);

    cout << "x_degree: " << x_degree_ << endl;
    cout << "y_degree: " << y_degree_ << endl;
    cout << "z_degree: " << z_degree_ << endl;
    cout << "num_x_ctrl_points: " << num_x_ctrl_points_ << " " << sample_x.size() << endl;
    cout << "num_y_ctrl_points: " << num_y_ctrl_points_ << " " << sample_y.size() << endl;
    cout << "num_z_ctrl_points: " << num_z_ctrl_points_ << " " << sample_z.size() << endl;
    cout << "shape of sample_f: " << sample_f.size() << " " << sample_f[0].size() << " " << sample_f[0][0].size()
         << endl;

    coefficients_ = Calculate_Control_Points(x_degree, y_degree, z_degree, x_knots_, y_knots_, z_knots_, sample_x,
                                             sample_y, sample_z, sample_f);
}

double BSplineInterpolate_3D::operator()(const double &x, const double &y, const double &z) const
{
    vector<int> x_index = activeBasisFunctions(x, x_knots_, x_degree_);
    vector<int> y_index = activeBasisFunctions(y, y_knots_, y_degree_);
    vector<int> z_index = activeBasisFunctions(z, z_knots_, z_degree_);

    double sum = 0.0;
    for (int i : x_index)
    {
        for (int j : y_index)
        {
            for (int k : z_index)
            {
                double basis_x = Bspline_basis(i, x_degree_, x, x_knots_);
                double basis_y = Bspline_basis(j, y_degree_, y, y_knots_);
                double basis_z = Bspline_basis(k, z_degree_, z, z_knots_);
                sum += coefficients_[i][j][k] * basis_x * basis_y * basis_z;
            }
        }
    }
    return sum;
}

int BSplineInterpolate_3D::save(const string &filename) const
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error: Interpolation 3D output file cannot open! \nfile name: " << filename << endl;
        throw "Error: Interpolation 3D output file cannot open! \nfile name:" + filename;
        return -1;
    }
    outfile << "x_degree: " << x_degree_ << endl;
    outfile << "y_degree: " << y_degree_ << endl;
    outfile << "z_degree: " << z_degree_ << endl;
    outfile << "num_x_ctrl_points: " << num_x_ctrl_points_ << endl;
    outfile << "num_y_ctrl_points: " << num_y_ctrl_points_ << endl;
    outfile << "num_z_ctrl_points: " << num_z_ctrl_points_ << endl;

    outfile << "x_knots: ";
    for (int i = 0; i < num_x_ctrl_points_ - 1; ++i)
        outfile << x_knots_(i) << ", ";
    outfile << x_knots_(num_x_ctrl_points_ - 1) << endl;

    outfile << "y_knots: ";
    for (int j = 0; j < num_y_ctrl_points_ - 1; ++j)
        outfile << y_knots_(j) << ", ";
    outfile << y_knots_(num_y_ctrl_points_ - 1) << endl;

    outfile << "z_knots: ";
    for (int k = 0; k < num_z_ctrl_points_ - 1; k++)
        outfile << z_knots_(k) << ", ";
    outfile << z_knots_(num_z_ctrl_points_ - 1) << endl;

    outfile << "coefficients: " << endl;
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        for (int j = 0; j < num_y_ctrl_points_; ++j)
        {
            for (int k = 0; k < num_z_ctrl_points_ - 1; ++k)
                outfile << coefficients_[i][j](k) << ", ";
            outfile << coefficients_[i][j](num_z_ctrl_points_ - 1) << endl;
        }
    }

    outfile.close();
    return 0;
}

int BSplineInterpolate_3D::load(const string &filename)
{
    ifstream infile(filename);
    if (!infile.is_open())
    {
        cerr << "Error: Interpolation 3D input file cannot open! \nfile name: " << filename << endl;
        throw "Error: Interpolation 3D input file cannot open! \nfile name:" + filename;
        return -1;
    }

    string line;

    getline(infile, line);
    x_degree_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    y_degree_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    z_degree_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    num_x_ctrl_points_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    num_y_ctrl_points_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    num_z_ctrl_points_ = stoi(line.substr(line.find(":") + 1));

    getline(infile, line);
    stringstream ss(line.substr(line.find(":") + 1));
    vector<double> xk(num_x_ctrl_points_);
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        ss >> xk[i];
        if (ss.peek() == ',')
            ss.ignore();
    }
    x_knots_ = VectorXd::Map(xk.data(), xk.size()).eval();

    getline(infile, line);
    stringstream ss2(line.substr(line.find(":") + 1));
    vector<double> yk(num_y_ctrl_points_);
    for (int j = 0; j < num_y_ctrl_points_; ++j)
    {
        ss2 >> yk[j];
        if (ss2.peek() == ',')
            ss2.ignore();
    }
    y_knots_ = VectorXd::Map(yk.data(), yk.size()).eval();

    getline(infile, line);
    stringstream ss3(line.substr(line.find(":") + 1));
    vector<double> zk(num_z_ctrl_points_);
    for (int k = 0; k < num_z_ctrl_points_; ++k)
    {
        ss3 >> zk[k];
        if (ss3.peek() == ',')
            ss3.ignore();
    }
    z_knots_ = VectorXd::Map(zk.data(), zk.size()).eval();

    coefficients_ = vector<vector<VectorXd>>(num_x_ctrl_points_, vector<VectorXd>(num_y_ctrl_points_));
    getline(infile, line);
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        for (int j = 0; j < num_y_ctrl_points_; ++j)
        {
            vector<double> temp(num_z_ctrl_points_);
            getline(infile, line);
            stringstream ss4(line);
            for (int k = 0; k < num_z_ctrl_points_; ++k)
            {
                ss4 >> temp[k];
                if (ss4.peek() == ',')
                    ss4.ignore();
            }
            coefficients_[i][j] = VectorXd::Map(temp.data(), temp.size()).eval();
        }
    }

    infile.close();

    return 0;
}

vector<vector<vector<double>>> BSplineInterpolate_3D::get_coefficients() const
{
    vector<vector<vector<double>>> result(num_x_ctrl_points_, vector<vector<double>>(num_y_ctrl_points_));
    for (int i = 0; i < num_x_ctrl_points_; ++i)
    {
        for (int j = 0; j < num_y_ctrl_points_; ++j)
        {
            result[i][j] =
                vector<double>(coefficients_[i][j].data(), coefficients_[i][j].data() + coefficients_[i][j].size());
        }
    }

    return result;
}

vector<double> BSplineInterpolate_3D::get_x_knots() const
{
    return vector<double>(x_knots_.data(), x_knots_.data() + x_knots_.size());
}

vector<double> BSplineInterpolate_3D::get_y_knots() const
{
    return vector<double>(y_knots_.data(), y_knots_.data() + y_knots_.size());
}

vector<double> BSplineInterpolate_3D::get_z_knots() const
{
    return vector<double>(y_knots_.data(), y_knots_.data() + z_knots_.size());
}

int BSplineInterpolate_3D::get_num_x_ctrl_points() const
{
    return num_x_ctrl_points_;
}

int BSplineInterpolate_3D::get_num_y_ctrl_points() const
{
    return num_y_ctrl_points_;
}
int BSplineInterpolate_3D::get_num_z_ctrl_points() const
{
    return num_z_ctrl_points_;
}

int BSplineInterpolate_3D::get_x_degree() const
{
    return x_degree_;
}

int BSplineInterpolate_3D::get_y_degree() const
{
    return y_degree_;
}

int BSplineInterpolate_3D::get_z_degree() const
{
    return z_degree_;
}
#pragma once

#include "BSpline_Interpolate.h"

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


class BSplineInterpolate_3D
{
    public:
        BSplineInterpolate_3D(){};
        BSplineInterpolate_3D(
            int x_degree, int y_degree, int z_degree,
            double x_lower, double x_upper, double y_lower, double y_upper, double z_lower, double z_upper,
            const vector<double>& sample_x, const vector<double>& sample_y, const vector<double>& sample_z,
            const vector<vector<vector<double> > >& sample_f
        )
            : x_degree_(x_degree), y_degree_(y_degree), z_degree_(z_degree), 
              num_x_ctrl_points_(sample_x.size()), num_y_ctrl_points_(sample_y.size()), num_z_ctrl_points_(sample_z.size()),
              x_knots_( knots_initialization(x_lower, x_upper, x_degree, sample_x.size()) ),
              y_knots_( knots_initialization(y_lower, y_upper, y_degree, sample_y.size()) ),
              z_knots_( knots_initialization(z_lower, z_upper, z_degree, sample_z.size()) )
        {
            int n_x = num_x_ctrl_points_;
            int n_y = num_y_ctrl_points_;
            int n_z = num_z_ctrl_points_;

            vector< vector< vector< double > > > N_abk(n_x, vector< vector<double> >(n_y,vector<double>(n_z) ) );
            coefficients_.resize(n_x);
            for(int ia = 0; ia < n_x; ++ia)
            {
                coefficients_[ia].resize(n_y);
                for(int ib = 0; ib < n_y; ++ib)
                {
                    coefficients_[ia][ib].resize(n_z);
                    N_abk[ia][ib] = BSpline_coefficients(z_degree, z_lower, z_upper, sample_z, sample_f[ia][ib]);
                }
            }

            vector< vector< vector< double > > > L_akj(n_x, vector< vector<double> >(n_z, vector<double>(n_y) ) );
            
            for(int ia = 0; ia < n_x; ++ia)
            {
                for(int k = 0; k < n_z; ++k)
                {
                    vector<double> temp(n_y);
                    for(int ib = 0; ib < n_y; ++ib)
                    {
                        temp[ib] = N_abk[ia][ib][k];
                    }

                    L_akj[ia][k] = BSpline_coefficients(y_degree, y_lower, y_upper, sample_y, temp);
                }
            }

            for(int k = 0; k < n_z; ++k)
            {
                for(int j = 0; j < n_y; ++j)    
                {
                    vector<double> temp(n_x);
                    for(int ia = 0; ia < n_x; ++ia)
                    {
                        temp[ia] = L_akj[ia][k][j];
                    }
                    vector<double> temp_coefficients = BSpline_coefficients(x_degree, x_lower, x_upper, sample_x, temp);
                    for(int ia = 0; ia < n_x; ++ia)
                    {
                        coefficients_[ia][j][k] = temp_coefficients[ia];
                    }
                }
            }
        }

        double operator()(double x, double y, double z) const
        {
            double sum = 0.0;
            for(int i = 0; i < num_x_ctrl_points_; ++i)
            {
                for(int j = 0; j < num_y_ctrl_points_; ++j)
                {
                    for(int k = 0; k < num_z_ctrl_points_; ++k)
                    {
                        double basis_x = bspline_basis(i, x_degree_, x, x_knots_);
                        double basis_y = bspline_basis(j, y_degree_, y, y_knots_);
                        double basis_z = bspline_basis(k, z_degree_, z, z_knots_);
                        sum += coefficients_[i][j][k] * basis_x * basis_y * basis_z;
                    }
                }
            }
            return sum;
        }


        int save(string filename) const
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
            for(int i = 0; i < x_knots_.size(); ++i)
            {
                outfile << x_knots_[i] << " ";
            }
            outfile << endl;

            outfile << "y_knots: ";
            for(int i = 0; i < y_knots_.size(); ++i)
            {
                outfile << y_knots_[i] << " ";
            }
            outfile << endl;

            outfile << "z_knots: ";
            for(int i = 0; i < z_knots_.size(); ++i)
            {
                outfile << z_knots_[i] << " ";
            }
            outfile << endl;

            outfile << "coefficients: " << endl;
            for(int i = 0; i < num_x_ctrl_points_; ++i)
            {
                for(int j = 0; j < num_y_ctrl_points_; ++j)
                {
                    for(int k = 0; k < num_z_ctrl_points_; ++k)
                    {
                        outfile << coefficients_[i][j][k] << " ";
                    }
                    outfile << endl;
                }
            }

            outfile.close();
            return 0;
        }

        int load(string filename)
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
            int x_degree = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int y_degree = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int z_degree = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int num_x_ctrl_points = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int num_y_ctrl_points = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int num_z_ctrl_points = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            vector<double> x_knots;
            stringstream ss(line.substr(line.find(":") + 1));
            double temp;
            while (ss >> temp)
            {
                x_knots.push_back(temp);
                if (ss.peek() == ',')
                    ss.ignore();
            } 
            
            getline(infile, line);
            vector<double> y_knots;
            stringstream ss2(line.substr(line.find(":") + 1));
            while (ss2 >> temp)
            {
                y_knots.push_back(temp);
                if (ss2.peek() == ',')
                    ss2.ignore();
            }
            
            getline(infile, line);
            vector<double> z_knots;
            stringstream ss3(line.substr(line.find(":") + 1));
            while (ss3 >> temp)
            {
                z_knots.push_back(temp);
                if (ss3.peek() == ',')
                    ss3.ignore();
            }

            getline(infile, line);
            vector< vector< vector< double > > > coefficients(num_x_ctrl_points, vector< vector<double> >(num_y_ctrl_points, vector<double>(num_z_ctrl_points) ) );
            for(int i = 0; i < num_x_ctrl_points; ++i)
            {
                for(int j = 0; j < num_y_ctrl_points; ++j)
                {
                    getline(infile, line);
                    stringstream ss4(line);
                    for(int k = 0; k < num_z_ctrl_points; ++k)
                    {
                        double temp;
                        ss4 >> temp;
                        coefficients[i][j][k] = temp;
                    }
                }
            }
            
            infile.close();
            x_degree_ = x_degree;
            y_degree_ = y_degree;
            z_degree_ = z_degree;
            num_x_ctrl_points_ = num_x_ctrl_points;
            num_y_ctrl_points_ = num_y_ctrl_points;
            num_z_ctrl_points_ = num_z_ctrl_points;
            x_knots_ = x_knots;
            y_knots_ = y_knots;
            z_knots_ = z_knots;
            coefficients_ = coefficients;
            return 0;
        }
        
        vector< vector< vector< double > > > get_coefficients() const
        {
            return coefficients_;
        }

        vector<double> get_x_knots() const
        {
            return x_knots_;
        }

        vector<double> get_y_knots() const
        {
            return y_knots_;
        }

        vector<double> get_z_knots() const
        {
            return z_knots_;
        }

        int get_num_x_ctrl_points() const
        {
            return num_x_ctrl_points_;
        }

        int get_num_y_ctrl_points() const
        {
            return num_y_ctrl_points_;
        }
        int get_num_z_ctrl_points() const
        {
            return num_z_ctrl_points_;
        }

        int get_x_degree() const
        {
            return x_degree_;
        }

        int get_y_degree() const
        {
            return y_degree_;
        }

        int get_z_degree() const
        {
            return z_degree_;
        }


    private:
        int x_degree_;
        int y_degree_;
        int z_degree_;
        int num_x_ctrl_points_;
        int num_y_ctrl_points_;
        int num_z_ctrl_points_;
        vector<double> x_knots_;
        vector<double> y_knots_;
        vector<double> z_knots_;
        vector< vector< vector < double > > > coefficients_;
};
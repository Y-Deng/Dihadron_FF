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


class BSplineInterpolate_2D
{
    public:
        BSplineInterpolate_2D(){};

        BSplineInterpolate_2D(
            int x_degree, int y_degree, 
            double x_lower, double x_upper, double y_lower, double y_upper, 
            const vector<double>& sample_x, const vector<double>& sample_y,
            const vector<vector<double> >& sample_f
        )
            : x_degree_(x_degree), y_degree_(y_degree), num_x_ctrl_points_(sample_x.size()), num_y_ctrl_points_(sample_y.size()),
              x_knots_( knots_initialization(x_lower, x_upper, x_degree, sample_x.size()) ),
              y_knots_( knots_initialization(y_lower, y_upper, y_degree, sample_y.size()) )
        {
            int n_x = num_x_ctrl_points_;
            int n_y = num_y_ctrl_points_;

            #if 0
            cout << "sample x:" << endl;
            print_vector(sample_x);
            cout << "sample y:" << endl;
            print_vector(sample_y);
            cout << "sample f:" << endl;
            print_matrix(sample_f);            
            #endif

            vector< vector<double> >  Temp_A( n_x );
            for (int i=0; i<num_x_ctrl_points_; ++i) 
            {
                vector<double> temp = BSpline_coefficients(y_degree, y_lower, y_upper, sample_y, sample_f[i]);
                Temp_A[i] = temp;
            }

            coefficients_.resize(num_x_ctrl_points_, vector<double>(num_y_ctrl_points_));
            for(int j = 0; j < num_y_ctrl_points_; ++j)
            {
                vector<double> Temp_b(n_x);
                for( int i = 0; i < num_x_ctrl_points_; ++i)
                {
                    Temp_b[i] = Temp_A[i][j];
                }
                vector<double> Temp_C = BSpline_coefficients(x_degree, x_lower, x_upper, sample_x, Temp_b);
                for(int i = 0; i < num_x_ctrl_points_; ++i)
                {
                    coefficients_[i][j] = Temp_C[i];
                }
            }
        }

        BSplineInterpolate_2D(
            int x_degree, int y_degree, int num_x_ctrl_points, int num_y_ctrl_points,
            vector<double> x_knots, vector<double> y_knots,
            vector<vector<double> > coefficients
        ) 
            : x_degree_(x_degree), y_degree_(y_degree), num_x_ctrl_points_(num_x_ctrl_points), num_y_ctrl_points_(num_y_ctrl_points),
              x_knots_(x_knots), y_knots_(y_knots), coefficients_(coefficients)
        {

        }

        BSplineInterpolate_2D(string filename)
        {
            ifstream infile(filename);
            if (!infile.is_open())
            {
                cerr << "Error: Interpolation 2D input file cannot open! \nfile name: " << filename << endl;
                throw "Error: Interpolation 2D input file cannot open! \nfile name:" + filename;
            }
            
            string line;
            
            getline(infile, line);
            int x_degree = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int y_degree = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int num_x_ctrl_points = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int num_y_ctrl_points = stoi(line.substr(line.find(":") + 1));
            
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
            vector<vector<double> > coefficients(num_x_ctrl_points, vector<double>(num_y_ctrl_points));
            for(int i = 0; i < num_x_ctrl_points; ++i)
            {
                getline(infile, line);
                stringstream ss3(line);
                for(int j = 0; j < num_y_ctrl_points; ++j)
                {
                    double temp;
                    ss3 >> temp;
                    coefficients[i][j] = temp;
                }
            }
            
            infile.close();

            x_degree_ = x_degree;
            y_degree_ = y_degree;
            num_x_ctrl_points_ = num_x_ctrl_points;
            num_y_ctrl_points_ = num_y_ctrl_points;
            x_knots_ = x_knots;
            y_knots_ = y_knots;
            coefficients_ = coefficients;
        }

        
        double operator()(double x, double y) const
        {
            double sum = 0.0;
            for(int i = 0; i < num_x_ctrl_points_; ++i)
            {
                for(int j = 0; j < num_y_ctrl_points_; ++j)
                {
                    double basis_x = bspline_basis(i, x_degree_, x, x_knots_);
                    double basis_y = bspline_basis(j, y_degree_, y, y_knots_);
                    sum += coefficients_[i][j] * basis_x * basis_y;
                }
            }
            return sum;
        }

        vector<vector< double > > get_coefficients() const
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

        int get_num_x_ctrl_points() const
        {
            return num_x_ctrl_points_;
        }

        int get_num_y_ctrl_points() const
        {
            return num_y_ctrl_points_;
        }

        int get_x_degree() const
        {
            return x_degree_;
        }

        int get_y_degree() const
        {
            return y_degree_;
        }

        int save(string filename) const
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

            outfile << "coefficients: " << endl;
            for(int i = 0; i < num_x_ctrl_points_; ++i)
            {
                for(int j = 0; j < num_y_ctrl_points_; ++j)
                {
                    outfile << coefficients_[i][j] << " ";
                }
                outfile << endl;
            }

            outfile.close();
            return 0;
        }

    private:
        int x_degree_;
        int y_degree_;
        int num_x_ctrl_points_;
        int num_y_ctrl_points_;
        vector<double> x_knots_;
        vector<double> y_knots_;
        
        vector<vector<double> > coefficients_;
};
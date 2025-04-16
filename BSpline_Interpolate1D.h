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


class BSplineInterpolate_1D
{
    public:
        BSplineInterpolate_1D(int degree, double lower, double upper, const vector<double>& sample_x, const vector<double>& sample_f)
            : degree_(degree), num_ctrl_points_(sample_x.size()), knots_( knots_initialization(lower, upper, degree, sample_x.size()) )
        {
            coefficients_ = BSpline_coefficients(degree, lower, upper, sample_x, sample_f);
        }
        
        double operator()(double x) const
        {
            double sum = 0.0;
            for (int j=0; j<num_ctrl_points_; ++j) {
                sum += coefficients_[j] * bspline_basis(j, degree_, x, knots_);
            } 
            return sum;
        }

        vector<double> get_coefficients() const
        {
            return coefficients_;
        }
        vector<double> get_knots() const
        {
            return knots_;
        }
        int get_degree() const
        {
            return degree_;
        }
        int get_num_ctrl_points() const
        {
            return num_ctrl_points_;
        }

        int save(string filename) const
        {
            ofstream outfile(filename);
            if(!outfile.is_open())
            {
                cerr << "Error: Interpolation 1D output file cannot open! \nfile name: " << filename << endl;
                throw "Error: Interpolation 1D output file cannot open! \nfile name:" + filename;
                return -1;
            }

            outfile << "degree: " << degree_ << endl;
            outfile << "num_ctrl_points: " << num_ctrl_points_ << endl;
            
            outfile << "knots: ";
            for(auto knot : knots_)
            {
                outfile << knot << " ";
            }
            outfile << endl;

            outfile << "coefficients: ";
            for(auto coeff : coefficients_)
            {
                outfile << coeff << " ";
            }
            outfile.close();
            
            return 0;
        }
        BSplineInterpolate_1D(int degree, int num_ctrl_points, vector<double> knots, vector<double> coefficients)
            : degree_(degree), num_ctrl_points_(num_ctrl_points), knots_(knots), coefficients_(coefficients)
        {
        }

        BSplineInterpolate_1D(string filename)
        {
            ifstream infile(filename);
            if (!infile.is_open())
            {
                cerr << "Error: Interpolation 1D input file cannot open! \nfile name: " << filename << endl;
                throw "Error: Interpolation 1D input file cannot open! \nfile name:" + filename;
            }
            string line;
            getline(infile, line);
            int degree = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            int num_ctrl_points = stoi(line.substr(line.find(":") + 1));
            
            getline(infile, line);
            vector<double> knots;
            stringstream ss(line.substr(line.find(":") + 1));
            double temp;
            while (ss >> temp)
            {
                knots.push_back(temp);
                if (ss.peek() == ',')
                    ss.ignore();
            }
            
            getline(infile, line);
            vector<double> coefficients;
            stringstream ss2(line.substr(line.find(":") + 1));
            while (ss2 >> temp)
            {
                coefficients.push_back(temp);
                if (ss2.peek() == ',')
                    ss2.ignore();
            }

            infile.close();
            
            degree_ = degree;
            num_ctrl_points_ = num_ctrl_points;
            knots_ = knots;
            coefficients_ = coefficients;
        }

    private:
        int degree_;
        int num_ctrl_points_;
        vector<double> knots_;
        vector<double> coefficients_;
};


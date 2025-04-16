#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "string"
#include "BSpline_Interpolate1D.h"
#include "BSpline_Interpolate2D.h"
#include "BSpline_Interpolate3D.h"

#include "ROOT/TCanvas.h"
#include "ROOT/TGraph.h"
#include "ROOT/TGraph2D.h"

#include "chrono"

using std::vector;
using std::cout;
using std::endl;

using std::string;
using std::stringstream;
using std::to_string;
using std::ifstream;
using std::ofstream;

inline int test_1D_BSpline_interpolate()
{
    const int degree = 3;       // 三次样条
    const double lower = 0.0;
    const double upper = 1.0;
    const int N = 30;
    const std::vector<double> sample_x = [&](){
        vector<double> temp;
        for(int i = 0; i < N; i++)
        {
            double x = lower + 0.01  + (upper - lower) * i / (N);
            temp.push_back(x);
        }
        return temp;
    }();
    const std::vector<double> sample_f = [&](){ 
        vector<double> temp;
        for(int i = 0; i < N; i++)
        {
            double x = sample_x[i];
            temp.push_back(sin(x));
        }
        return temp;
    }();

    BSplineInterpolate_1D interpolator(degree, lower, upper, sample_x, sample_f);

    // 验证插值结果
    
    TGraph *gr_original = new TGraph(sample_x.size(), &sample_x[0], &sample_f[0]);
    gr_original->SetMarkerStyle(8);
    gr_original->SetMarkerSize(1.0);

    
    vector<double> test_x;
    vector<double> test_f;
    for (double x = lower; x <= upper; x += 0.01) {
        test_x.push_back(x);
        test_f.push_back(interpolator(x));
    }

    TGraph *gr_interpolated = new TGraph(test_x.size(), &test_x[0], &test_f[0]);

    TCanvas *c1 = new TCanvas("c1", "c1");
    
    gr_interpolated->Draw("APL same");
    gr_original->Draw("P same");
    c1->Draw();
    c1->SaveAs("test_1D_BSpline_interpolate.png");

    // Save the interpolated coefficients to a file
    interpolator.save("./coefficients1D.txt");

    // Read the interpolated coefficients from a file
    BSplineInterpolate_1D interpolator2("./coefficients1D.txt");
    interpolator2.save("./coefficients1D_check.txt");

    return 0;    
}

inline int test_2D_BSpline_interpolate()
{
    const int x_degree = 3;       // 三次样条
    const int y_degree = 3;       // 三次样条

    const double lower = 0.0;
    const double upper = 1.0;

    int N = 30;

    const std::vector<double> sample_x = [&](){
        vector<double> temp;
        for(int i = 0; i < N; i++)
        {
            double x = lower + 0.01 + (upper - lower) * i / (N);
            temp.push_back(x);
        }
        return temp;
    }();
    const std::vector<double> sample_y = [&](){
        vector<double> temp;
        for(int i = 0; i < N; i++)
        {
            double y = lower + 0.01 + (upper - lower) * i / (N);
            temp.push_back(y);
        }
        return temp;
    }();
    const vector< vector< double > > sample_f = [&](){
        vector< vector< double > > f(sample_x.size(), vector<double>(sample_y.size()));
        for (size_t i=0; i<sample_x.size(); ++i) {
            for (size_t j=0; j<sample_y.size(); ++j) {
                f[i][j] = sin(sample_x[i]*sample_y[j]);
            }
        }
        return f;
    }();

    BSplineInterpolate_2D interpolator(x_degree, y_degree, lower, upper, lower, upper, sample_x, sample_y, sample_f);

    // 验证插值结果
    TGraph2D *gr_original = new TGraph2D();
    int point = 0;
    for(int i = 0; i < sample_x.size(); i++)
    {
        for(int j = 0; j < sample_y.size(); j++)
        {
            gr_original->SetPoint(point++, sample_x[i], sample_y[j], sample_f[i][j]);
        }
    }

    const vector<double> test_x = [&](){
        vector<double> temp;
        for(double x = lower; x <= upper; x += 0.01)
        {
            temp.push_back(x);
        }
        return temp;
    }();
    const vector<double> test_y = [&](){
        vector<double> temp;
        for(double y = lower; y <= upper; y += 0.01)
        {
            temp.push_back(y);
        }
        return temp;
    }();
    const vector<vector<double> > test_f = [&](){
        vector<vector<double> > temp(test_x.size(), vector<double>(test_y.size()));
        for(size_t i = 0; i < test_x.size(); i++)
        {
            for(size_t j = 0; j < test_y.size(); j++)
            {
                temp[i][j] = interpolator(test_x[i], test_y[j]);
            }
        }
        return temp;
    }();
    TGraph2D *gr_interpolated = new TGraph2D();
    point = 0;
    for(int i = 0; i < test_x.size(); i++)
    {
        for(int j = 0; j < test_y.size(); j++)
        {
            gr_interpolated->SetPoint(point++, test_x[i], test_y[j], test_f[i][j]);
        }
    }

    TCanvas *c1 = new TCanvas("c1", "c1");
    c1->Divide(1,2);
    c1->cd(1);
    gr_original->Draw("surf1");
    c1->cd(2);
    gr_interpolated->Draw("surf1");
    c1->Draw();
    c1->SaveAs("test_2D_BSpline_interpolate.png");

    // Save the interpolated coefficients to a file
    interpolator.save("./coefficients2D.txt");
    
    // Read the interpolated coefficients from a file
    BSplineInterpolate_2D interpolator2("./coefficients2D.txt");

    vector<vector<double> > coef = interpolator2.get_coefficients();
    interpolator2.save("./coefficients2D_check.txt");
    
    return 0;    
}


int test_3D_BSpline_interpolate()
{
    const int x_degree = 3;       // 三次样条
    const int y_degree = 3;       // 三次样条
    const int z_degree = 3;       // 三次样条

    const double lower = 0.0;
    const double upper = 1.0; 

    int N = 40;
    const std::vector<double> sample_x = linspace(lower+1.e-4, upper-1.e-4, N);
    const std::vector<double> sample_y = linspace(lower+1.e-4, upper-1.e-4, N);
    const std::vector<double> sample_z = linspace(lower+1.e-4, upper-1.e-4, N);

    const vector< vector < vector< double > > > sample_f = [&](){
        vector< vector < vector< double > > > f(sample_x.size(), vector< vector<double> >(sample_y.size(), vector<double>(sample_z.size())));
        for (size_t i=0; i<sample_x.size(); ++i) {
            for (size_t j=0; j<sample_y.size(); ++j) {
                for (size_t k=0; k<sample_z.size(); ++k) {
                    f[i][j][k] = sin(sample_x[i]*sample_y[j]*sample_z[k]);
                }
            }
        }
        return f;
    }();

    auto start = std::chrono::high_resolution_clock::now(); 
    BSplineInterpolate_3D interpolator(x_degree, y_degree, z_degree, 
        lower, upper, lower, upper, lower, upper, 
        sample_x, sample_y, sample_z, sample_f);
    auto end = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Time used for 3D BSpline interpolation: " << duration << " microseconds" << endl;

    vector<double> test_z = linspace(lower+1.e-4, upper-1.e-4, 200);
    
    vector<int> indexs = {1, 5, 11, 16};
    
    int index = 1;
    for(int i :indexs)
    {
        for(int j : indexs)
        {

            vector<double> test_f = [&](){
                vector<double> temp(test_z.size());
                for(int k = 0; k < test_z.size(); k++)
                {
                    temp[k] = interpolator(sample_x[i], sample_y[j], test_z[k]);
                }
                return temp;
            }();
            
            TGraph *gr_original = new TGraph(sample_z.size(), &sample_z[0], &sample_f[i][j][0]);
            gr_original->SetMarkerStyle(10);
            gr_original->SetMarkerSize(1.);
            
            TGraph *gr_interpolated = new TGraph(test_z.size(), &test_z[0], &test_f[0]);
            
            TCanvas *c1 = new TCanvas(std::to_string(index).c_str(), "c1", 600, 600);
            c1->cd();
            gr_interpolated->Draw("APL");
            gr_original->Draw("P same");
            
            c1->SaveAs((to_string(index) + ".pdf").c_str());
            index++;
            
        }
    }


    interpolator.save("./coefficients3D.txt");
    BSplineInterpolate_3D interpolator2;
    interpolator2.load("./coefficients3D.txt");
    vector<vector<vector<double> > > coef = interpolator2.get_coefficients();
    interpolator2.save("./coefficients3D_check.txt");

    return 0;
}
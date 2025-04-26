#include "BSpline_Interpolate.h"
#include "DiFF_TMD.h"
#include "Tools.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void output_TMD_DiFF()
{
    const int zh_degree = 2;
    const int Mh_degree = 2;
    const int mu2_degree = 2;

    const double zh_min = 0.02;
    const double zh_max = 1.0;
    const double Mh_min = 0.2;
    const double Mh_max = 2.0;
    const double mu2_min = 1.1;
    const double mu2_max = 1.e4;

    vector<int> flavors = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};

    int num_zhs = 100;
    int num_Mhs = 50;
    int num_mu2s = 100;

    const vector<double> zh_grid = linspace(zh_min + 1.e-3, zh_max - 1.e-3, num_zhs);
    const vector<double> Mh_grid = linspace(Mh_min + 1.e-3, Mh_max - 1.e-3, num_Mhs);
    const vector<double> log10_mu2_gird = linspace(log10(mu2_min) + 1.e-3, log10(mu2_max) - 1.e-3, num_mu2s);
    map<string, map<int, vector<vector<vector<double>>>>> result =
        output_evolved_DiFF(zh_grid, Mh_grid, log10_mu2_gird, flavors);

    vector<string> keys = {"pm", "pp"};
    for (string key : keys)
    {
        for (int id : flavors)
        {
            vector<vector<vector<double>>> TMD_DiFF = result[key][id];

            cout << "TMD_DiFF:" << key << "_" << id << ".dat" << endl;
            for (int i = 0; i < num_Mhs; i++)
            {
                for (int j = 0; j < num_zhs; j++)
                {
                    for (int k = 0; k < num_mu2s; k++)
                    {
                        cout << TMD_DiFF[i][j][k] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }

            BSplineInterpolate_3D interpolator(Mh_degree, zh_degree, mu2_degree, Mh_min, Mh_max, zh_min, zh_max,
                                               log10(mu2_min), log10(mu2_max), Mh_grid, zh_grid, log10_mu2_gird,
                                               TMD_DiFF);
            string filename = "./TMD_DiFF_" + key + "_" + to_string(id) + ".dat";
            interpolator.save(filename);
        }
    }
}

int main()
{

    output_TMD_DiFF();

    return 0;
}
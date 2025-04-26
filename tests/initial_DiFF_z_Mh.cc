#include "BSpline_Interpolate.h"
#include "DiFF_TMD.h"
#include "Tools.h"
#include "functional"
#include <cmath>
#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "map"
using namespace std;

double mu_value = 0.1;
double sigma_value = 1.;

vector<double> mu_vec = {};
vector<double> sigma_vec = {};

const map<int, BSplineInterpolate_2D> initial_pm_DiFF_z1_z2 = []() {
    map<int, BSplineInterpolate_2D> result;
    for (int id : {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5})
    {
        string filename =
            "/root/DengYongjie/BsplineInterpolation/output_files/DiFF_z1_z2/initial_DiFF_z1_z2/pm_DiFF_z1_z2_" +
            to_string(id) + ".txt";
        BSplineInterpolate_2D interpolator;
        interpolator.load(filename);
        result[id] = interpolator;
    }
    return result;
}();

const map<int, BSplineInterpolate_2D> initial_pp_DiFF_z1_z2 = []() {
    map<int, BSplineInterpolate_2D> result;
    for (int id : {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5})
    {
        string filename =
            "/root/DengYongjie/BsplineInterpolation/output_files/DiFF_z1_z2/initial_DiFF_z1_z2/pp_DiFF_z1_z2_" +
            to_string(id) + ".txt";
        BSplineInterpolate_2D interpolator;
        interpolator.load(filename);
        result[id] = interpolator;
    }
    return result;
}();

function<double(double)> test_pm_RT_distribution = [](double RT) {
    double mu = mu_value;
    double sigma = sigma_value;
    double result = 1. / (sqrt(2. * M_PI) * sigma) * exp(-pow(RT - mu, 2) / (2. * sigma * sigma));
    return result;
};

function<double(double)> test_pp_RT_distribution = [](double RT) {
    double mu = mu_value;
    double sigma = sigma_value;
    double result = 1. / (sqrt(2. * M_PI) * sigma) * exp(-pow(RT - mu, 2) / (2. * sigma * sigma));
    return result;
};

const function<double(int, double, double)> pm_coll = [](int id, double z1, double z2) {
    return initial_pm_DiFF_z1_z2.at(id)(z1, z2);
};

const function<double(int, double, double)> pp_coll = [](int id, double z1, double z2) {
    return initial_pp_DiFF_z1_z2.at(id)(z1, z2);
};

void output_DiFF_zh_Mh(int mu_index, int sigma_index)
{
    int zh_degree = 2;
    int Mh_degree = 2;
    int zh_num_ctrl = 100;
    int Mh_num_ctrl = 100;
    double zh_lower = 0.02;
    double zh_upper = 1.;
    double Mh_lower = 0.2;
    double Mh_upper = 2.;

    vector<double> zh_grid = linspace<double>(zh_lower + 1.e-3, zh_upper - 1.e-3, zh_num_ctrl);
    vector<double> Mh_grid = linspace<double>(Mh_lower + 1.e-3, Mh_upper - 1.e-3, Mh_num_ctrl);

    vector<int> flavors = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    for (auto id : flavors)
    {
        cout << "flavor: " << id << endl;
        vector<vector<double>> pm_DiFF_zh_Mh(zh_grid.size(), vector<double>(Mh_grid.size()));
        vector<vector<double>> pp_DiFF_zh_Mh(zh_grid.size(), vector<double>(Mh_grid.size()));
        for (size_t i = 0; i < zh_grid.size(); i++)
        {
            for (size_t j = 0; j < zh_grid.size(); j++)
            {
                pm_DiFF_zh_Mh[i][j] =
                    TMD_DiFFs_pm_initial(zh_grid[i], Mh_grid[j], id, pm_coll, test_pm_RT_distribution);
                pp_DiFF_zh_Mh[i][j] =
                    TMD_DiFFs_pp_initial(zh_grid[i], Mh_grid[j], id, pp_coll, test_pp_RT_distribution);
            }
        }

        BSplineInterpolate_2D interpolator_pm(zh_degree, Mh_degree, zh_lower, zh_upper, Mh_lower, Mh_upper, zh_grid,
                                              Mh_grid, pm_DiFF_zh_Mh);
        BSplineInterpolate_2D interpolator_pp(zh_degree, Mh_degree, zh_lower, zh_upper, Mh_lower, Mh_upper, zh_grid,
                                              Mh_grid, pp_DiFF_zh_Mh);

        string pm_filename = "pm_DiFF_zh_Mh_" + to_string(id) + ".txt";
        string pp_filename = "pp_DiFF_zh_Mh_" + to_string(id) + ".txt";
        interpolator_pm.save(pm_filename);
        interpolator_pp.save(pp_filename);
    }
}

int main()
{
    for (size_t i_mu = 0; i_mu < mu_vec.size(); ++i_mu)
    {
        for (size_t i_sigma = 0; i_sigma < sigma_vec.size(); ++i_sigma)
        {
            mu_value = mu_vec[i_mu];
            sigma_value = sigma_vec[i_sigma];
            output_DiFF_zh_Mh(i_mu, i_sigma);
        }
    }

    return 0;
}

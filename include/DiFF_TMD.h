#pragma once

#include "Field-FeynmanModel.h"
#include "QCDNUM_Evolution.h"
#include "Tools.h"

#include "cmath"
#include "functional"
#include "map"
#include <cstddef>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::function;
using std::map;
using std::sqrt;
using std::string;
using std::vector;

double Mh;

const double r20 = 111.96;
const double alpha_s0 = 0.17;
const double Q20 = 1.;
const double q2thre[3] = {1.6, 17., 1000000.};
const int is_initialized = QCDevol_init(r20, alpha_s0, Q20, q2thre);

const function<double(double)> pm_RT_distribution = [](double RT) {
    double mu = 0.15;
    double sigma = 1.;
    double result = 1. / (sqrt(2. * M_PI) * sigma) * exp(-pow(RT - mu, 2) / (2. * sigma * sigma));
    return result;
};
const function<double(double)> pp_RT_distribution = [](double RT) {
    double mu = 0.15;
    double sigma = 1.;
    double result = 1. / (sqrt(2. * M_PI) * sigma) * exp(-pow(RT - mu, 2) / (2. * sigma * sigma));
    return result;
};

inline double zDiFFs_pm_QCDNUM_initial_FF(int *ipdf, double *zh)
{
    int id;
    if (*ipdf == 0)
        id = 0;
    else if (*ipdf == 1)
        id = 1;
    else if (*ipdf == 2)
        id = 2;
    else if (*ipdf == 3)
        id = 3;
    else if (*ipdf == 4)
        id = -1;
    else if (*ipdf == 5)
        id = -2;
    else if (*ipdf == 6)
        id = -3;
    else
        return 0.;

    double z_value = zh[0];
    double result = z_value * TMD_DiFFs_pm_initial(z_value, Mh, id, pm_RT_distribution);
    return result;
}

inline double zDiFFs_pp_QCDNUM_initial_FF(int *ipdf, double *zh)
{
    int id;
    if (*ipdf == 0)
        id = 0;
    else if (*ipdf == 1)
        id = 1;
    else if (*ipdf == 2)
        id = 2;
    else if (*ipdf == 3)
        id = 3;
    else if (*ipdf == 4)
        id = -1;
    else if (*ipdf == 5)
        id = -2;
    else if (*ipdf == 6)
        id = -3;
    else
        return 0.;

    double z_value = *zh;

    double result = z_value * TMD_DiFFs_pp_initial(z_value, Mh, id, pp_RT_distribution);
    return result;
}

inline void Evolution_DiFF()
{
    double eps;
    int iq20 = QCDNUM::iqfrmq(Q20);
    QCDNUM::evolfg(3, zDiFFs_pm_QCDNUM_initial_FF, Flavor_mixing_matrix, iq20, eps);
    QCDNUM::pdfcpy(3, 5);

    QCDNUM::evolfg(3, zDiFFs_pp_QCDNUM_initial_FF, Flavor_mixing_matrix, iq20, eps);
    QCDNUM::pdfcpy(3, 6);
}

inline double DiFFs_pm_QCDNUM_evolved_FF(int id, double zh, double mu2)
{
    double result = QCDNUM::fvalxq(5, id, zh, mu2, 1);
    return result / zh;
}

inline double DiFFs_pp_QCDNUM_evolved_FF(int id, double zh, double mu2)
{
    double result = QCDNUM::fvalxq(6, id, zh, mu2, 1);
    return result / zh;
}

inline int test_QCDNUM_evolved_DiFF_TMD(double zh, double Mh_value, double mu2, int id)
{
    Mh = Mh_value;
    Evolution_DiFF();
    double result_pm = DiFFs_pm_QCDNUM_evolved_FF(id, zh, mu2);
    double result_pp = DiFFs_pp_QCDNUM_evolved_FF(id, zh, mu2);
    cout << "DiFFs_pm_QCDNUM_evolved_FF(" << id << ", " << zh << ", " << mu2 << ") = " << result_pm << endl;
    cout << "DiFFs_pp_QCDNUM_evolved_FF(" << id << ", " << zh << ", " << mu2 << ") = " << result_pp << endl;

    return 0;
}

inline map<int, map<int, vector<vector<double>>>> output_QCDNUM_evolved_DiFF_TMD(double Mh_value)
{
    Mh = Mh_value;
    Evolution_DiFF();

    vector<double> zh = linspace(0.01, 0.99, 100);
    vector<double> log10_mu2 = linspace<double>(1., 6, 100);
    vector<double> mu2 = [&]() {
        vector<double> temp;
        for (int i = 0; i < log10_mu2.size(); i++)
        {
            double mu2 = pow(10, log10_mu2[i]);
            temp.push_back(mu2);
        }
        return temp;
    }();

    map<int, map<int, vector<vector<double>>>> result;

    for (int id : {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5})
    {
        vector<vector<double>> pm_result(zh.size(), vector<double>(mu2.size()));
        vector<vector<double>> pp_result(zh.size(), vector<double>(mu2.size()));

        for (size_t i = 0; i < zh.size(); i++)
        {
            for (size_t j = 0; j < mu2.size(); j++)
            {
                pm_result[i][j] = DiFFs_pm_QCDNUM_evolved_FF(id, zh[i], mu2[j]);
                pp_result[i][j] = DiFFs_pp_QCDNUM_evolved_FF(id, zh[i], mu2[j]);
            }
        }

        result[1][id] = pm_result;
        result[2][id] = pp_result;
    }
    return result;
}

inline map<string, map<int, vector<vector<vector<double>>>>> output_evolved_DiFF(const vector<double> &zh,
                                                                                 const vector<double> &M_h,
                                                                                 const vector<double> &log10_mu2,
                                                                                 const vector<int> &ids)
{
    map<string, map<int, vector<vector<vector<double>>>>> result;
    for (int id : ids)
    {
        result["pm"][id] = vector<vector<vector<double>>>(
            M_h.size(), vector<vector<double>>(zh.size(), vector<double>(log10_mu2.size())));
        result["pp"][id] = vector<vector<vector<double>>>(
            M_h.size(), vector<vector<double>>(zh.size(), vector<double>(log10_mu2.size())));
    }

    for (int i = 0; i < M_h.size(); i++)
    {
        Mh = M_h[i];
        Evolution_DiFF();
        for (int j = 0; j < ids.size(); j++)
        {
            for (int k = 0; k < zh.size(); k++)
            {
                for (int l = 0; l < log10_mu2.size(); l++)
                {
                    double mu2 = pow(10, log10_mu2[l]);
                    result["pm"][ids[j]][i][k][l] = DiFFs_pm_QCDNUM_evolved_FF(ids[j], zh[k], mu2);
                    result["pp"][ids[j]][i][k][l] = DiFFs_pp_QCDNUM_evolved_FF(ids[j], zh[k], mu2);
                }
            }
        }
    }
    return result;
}

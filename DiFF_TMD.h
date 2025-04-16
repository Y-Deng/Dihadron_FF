#pragma once

#include "./Field-FeynmanModel_TMD.h"
#include "QCDNUM_Evolution.h"

#include "functional"

using std::function;
using std::sqrt;
using std::pow;
using std::cout;
using std::endl;
using std::isnan;
using std::vector;
using std::string;

double Mh;

const function<double(double)> pm_RT_distribution = [](double RT) {
    double mu = 0.05;
    double sigma = 1.;
    double result = 1./(sqrt(2.*M_PI)*sigma) * exp(-pow(RT-mu,2)/(2.*sigma*sigma));    
    return result;
};
const function<double(double)> pp_RT_distribution = [](double RT) {
    double mu = 0.05;
    double sigma = 1.;
    double result = 1./(sqrt(2.*M_PI)*sigma) * exp(-pow(RT-mu,2)/(2.*sigma*sigma));
    return result;
};

inline double zDiFFs_pm_QCDNUM_initial_FF(int *ipdf, double *zh )
{
    int id;
    if(*ipdf == 0) id = 0;
    else if( *ipdf == 1) id = 1;
    else if( *ipdf == 2) id = 2;
    else if( *ipdf == 3) id = 3;
    else if( *ipdf == 4) id = -1;
    else if( *ipdf == 5) id = -2;
    else if( *ipdf == 6) id = -3;
    else return 0.;

    double z_value = zh[0];
    double result = z_value * TMD_DiFFs_pm(z_value, Mh, id, pm_RT_distribution);
    return result;
}

inline double zDiFFs_pp_QCDNUM_initial_FF(int *ipdf, double *zh)
{
    int id;
    if(*ipdf == 0) id = 0;
    else if( *ipdf == 1) id = 1;
    else if( *ipdf == 2) id = 2;
    else if( *ipdf == 3) id = 3;
    else if( *ipdf == 4) id = -1;
    else if( *ipdf == 5) id = -2;
    else if( *ipdf == 6) id = -3;
    else return 0.;

    double z_value = *zh;

    double result = z_value * TMD_DiFFs_pp(z_value, Mh, id, pp_RT_distribution);
    return result;
}

inline void Evolution_DiFF()
{
    const double r20 = 111.96;
    const double alpha_s0 = 0.17;
    const double Q20 = 1.;
    const double q2thre[3] = {1.6, 17., 1000000.};
    QCDevol_init(r20, alpha_s0, Q20, q2thre);
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
    return result/zh;
}

inline double DiFFs_pp_QCDNUM_evolved_FF(int id, double zh, double mu2)
{
    double result = QCDNUM::fvalxq(6, id, zh, mu2, 1);
    return result/zh;
}

inline int test_QCDNUM_evolved_DiFF_TMD(double zh, double Mh_value, double mu2, int id)
{
    Mh = Mh_value;
    Evolution_DiFF();
    double result_pm = DiFFs_pm_QCDNUM_evolved_FF(id, zh, mu2);
    double result_pp = DiFFs_pp_QCDNUM_evolved_FF(id, zh, mu2);
    cout << "DiFFs_pm_QCDNUM_evolved_FF(" << id << ", " << zh << ", " << mu2 <<  ") = " << result_pm << endl;
    cout << "DiFFs_pp_QCDNUM_evolved_FF(" << id << ", " << zh << ", " << mu2 <<  ") = " << result_pp << endl;

    return 0;
}


#include "../include/Field-FeynmanModel.h"
#include "../include/Integration.h"
#include <cmath>

using namespace std;

inline double f(double eta)
{
    return (d + 1.0) * pow(eta, d);
}

inline double g(double eta)
{
    return (d + 1.) / eta;
}

inline double F(double eta)
{
    return f(1. - eta) / eta;
}

double FF_pion_plus_FFs_initial(const double &z, const int &id)
{
    double Au = gamma_value;
    double Ad = 0.;
    double As = 0.;
    double B = gamma_value * gamma_value;

    double Fbar = F(z) - f(1. - z);

    if (id == 2 || id == -1)
        return Au * f(1 - z) + B * Fbar;
    else if (id == 1 || id == -2 || id == 3 || id == -3)
        return B * Fbar;
    else
        return 0.;
}

double FF_pion_minus_FFs_initial(const double &z, const int &id)
{
    double Au = gamma_value;
    double Ad = 0.;
    double As = 0.;
    double B = gamma_value * gamma_value;

    double Fbar = F(z) - f(1. - z);

    if (id == -2 || id == 1)
        return Au * f(1 - z) + B * Fbar;
    else if (id == -1 || id == 2 || id == 3 || id == -3)
        return B * Fbar;
    else
        return 0.;
}

// Dihadron
inline int delta_ij(int i, int j)
{
    if (i == j)
        return 1;
    else
        return 0;
}

inline double gamma_index(int i)
{
    if (i == 1)
        return gamma_value;
    else if (i == 2)
        return gamma_value;
    else if (i == 3)
        return 1. - 2. * gamma_value;
    else if (i == -1)
        return gamma_value;
    else if (i == -2)
        return gamma_value;
    else if (i == -3)
        return 1. - 2. * gamma_value;
    else
        return 0;
}

double FF_dihadron_plus_minus_FFs_initial(const double &z1, const double &z2, const int &id)
{
    double plus_minus, minus_plus;
    {
        int q = id;
        int a = 2;
        int b = 1;
        int c = 1;
        int d = 2;

        struct integrand_params
        {
            int id;
            double z1;
            double z2;
        };

        auto integrand = [](double eta, integrand_params params) {
            double z1 = params.z1;
            double z2 = params.z2;
            int id = params.id;
            if (z1 + z2 > eta || eta >= 1.)
                return 0.;
            return g(eta) * f(1. - z1 / eta) * FF_pion_minus_FFs_initial(z2 / (eta - z1), id) / (eta * (eta - z1));
        };

        integrand_params params = {b, z1, z2};
        if (z1 + z2 >= .99)
            plus_minus = 0.;
        else
            plus_minus =
                delta_ij(q, a) * gamma_index(b) * f(1 - z1) * FF_pion_minus_FFs_initial(z2 / (1. - z1), b) / (1. - z1) +
                gamma_index(a) * gamma_index(b) * integrate<integrand_params>(z1 + z2, .99, integrand, params);
    }

    {
        int q = id;
        int a = 1;
        int b = 2;
        int c = 2;
        int d = 1;

        struct integrand_params
        {
            int id;
            double z1;
            double z2;
        };

        auto integrand = [](double eta, integrand_params params) {
            double z1 = params.z1;
            double z2 = params.z2;
            int id = params.id;
            if (z1 + z2 > eta || eta >= 1.)
                return 0.;
            return g(eta) * f(1. - z1 / eta) * FF_pion_plus_FFs_initial(z2 / (eta - z1), id) / (eta * (eta - z1));
        };

        integrand_params params = {b, z1, z2};
        if (z1 + z2 >= 0.99)
            minus_plus = 0.;
        else
            minus_plus =
                delta_ij(q, a) * gamma_index(b) * f(1 - z1) * FF_pion_plus_FFs_initial(z2 / (1. - z1), b) / (1. - z1) +
                gamma_index(a) * gamma_index(b) * integrate<integrand_params>(z1 + z2, .99, integrand, params);
    }

    return plus_minus + minus_plus;
}

double FF_dihadron_plus_plus_FFs_initial(const double &z1, const double &z2, const int &id)
{
    double plus_plus;
    {
        int q = id;
        int a = 2;
        int b = 1;
        int c = 2;
        int d = 1;

        struct integrand_params
        {
            int id;
            double z1;
            double z2;
        };

        auto integrand = [](double eta, integrand_params params) {
            double z1 = params.z1;
            double z2 = params.z2;
            int id = params.id;
            if (z1 + z2 > eta || eta >= 1.)
                return 0.;
            return g(eta) * f(1. - z1 / eta) * FF_pion_plus_FFs_initial(z2 / (eta - z1), id) / (eta * (eta - z1));
        };

        integrand_params params = {b, z1, z2};
        if (z1 + z2 >= .99)
            plus_plus = 0.;
        else
            plus_plus =
                delta_ij(q, a) * gamma_index(b) * f(1 - z1) * FF_pion_plus_FFs_initial(z2 / (1. - z1), b) / (1. - z1) +
                gamma_index(a) * gamma_index(b) * integrate<integrand_params>(z1 + z2, .99, integrand, params);
    }

    return plus_plus;
}

double TMD_DiFFs_pm_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(double)> &pm_RT_distribution)
{
    struct integrand_params
    {
        double zh;
        double Mh;
        int id;
    };

    function<double(double, integrand_params)> integrand = [&pm_RT_distribution](double xi, integrand_params params) {
        double zh = params.zh;
        double Mh = params.Mh;
        int id = params.id;
        if (id == 0)
            return 0.;

        double M1 = Mass_pion_charged;
        double M2 = Mass_pion_charged;

        double z1 = (zh * xi + zh) / 2.;
        double z2 = (zh - zh * xi) / 2.;
        double RT2 = ((z1 * z2 * pow(Mh, 2)) / (z1 + z2) - pow(M1, 2) * z2 - pow(M2, 2) * z1) / (z1 + z2);
        double RT;
        if (RT2 < 0.)
            return 0.;
        else
            RT = sqrt(RT2);

        double value_of_RT_part = pm_RT_distribution(RT);
        double value_of_FF_part = FF_dihadron_plus_minus_FFs_initial(z1, z2, id);

        double res = M_PI / 2. * Mh * (1 - pow(xi, 2)) * value_of_FF_part * value_of_RT_part;
        return res;
    };

    integrand_params params = {zh, Mh, id};
    double result = integrate<integrand_params>(-1, 1, integrand, params);
    return result;
}

double TMD_DiFFs_pp_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(double)> &pp_RT_distribution)
{
    struct integrand_params
    {
        double zh;
        double Mh;
        int id;
    };
    function<double(double, integrand_params)> integrand = [&pp_RT_distribution](double xi, integrand_params params) {
        double zh = params.zh;
        double Mh = params.Mh;
        int id = params.id;

        double z1 = (zh * xi + zh) / 2.;
        double z2 = (zh - zh * xi) / 2.;
        double M1 = Mass_pion_charged;
        double M2 = Mass_pion_charged;
        double RT2 = ((z1 * z2 * pow(Mh, 2)) / (z1 + z2) - pow(M1, 2) * z2 - pow(M2, 2) * z1) / (z1 + z2);
        double RT;
        if (RT2 < 0.)
            return 0.;
        else
            RT = sqrt(RT2);
        double value_of_FF_part = FF_dihadron_plus_plus_FFs_initial(z1, z2, id);

        double res = M_PI / 2. * Mh * (1 - pow(xi, 2)) * value_of_FF_part * pp_RT_distribution(RT);
        return res;
    };

    integrand_params params = {zh, Mh, id};
    double result = integrate<integrand_params>(-1, 1, integrand, params);
    return result;
}

double TMD_DiFFs_pm_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(int, double, double)> &DiFF_z1_z2,
                            const function<double(double)> &pm_RT_distribution)
{
    struct integrand_params
    {
        double zh;
        double Mh;
        int id;
    };

    function<double(double, integrand_params)> integrand = [&pm_RT_distribution, &DiFF_z1_z2](double xi,
                                                                                              integrand_params params) {
        double zh = params.zh;
        double Mh = params.Mh;
        int id = params.id;
        if (id == 0)
            return 0.;

        double M1 = Mass_pion_charged;
        double M2 = Mass_pion_charged;

        double z1 = (zh * xi + zh) / 2.;
        double z2 = (zh - zh * xi) / 2.;
        double RT2 = ((z1 * z2 * pow(Mh, 2)) / (z1 + z2) - pow(M1, 2) * z2 - pow(M2, 2) * z1) / (z1 + z2);
        double RT;
        if (RT2 < 0.)
            return 0.;
        else
            RT = sqrt(RT2);

        double value_of_RT_part = pm_RT_distribution(RT);
        double value_of_FF_part = DiFF_z1_z2(z1, z2, id);

        double res = M_PI / 2. * Mh * (1 - pow(xi, 2)) * value_of_FF_part * value_of_RT_part;
        return res;
    };

    integrand_params params = {zh, Mh, id};
    double result = integrate<integrand_params>(-1, 1, integrand, params);
    return result;
}

double TMD_DiFFs_pp_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(int, double, double)> &DiFF_z1_z2,
                            const function<double(double)> &pp_RT_distribution)
{
    struct integrand_params
    {
        double zh;
        double Mh;
        int id;
    };
    function<double(double, integrand_params)> integrand = [&pp_RT_distribution, &DiFF_z1_z2](double xi,
                                                                                              integrand_params params) {
        double zh = params.zh;
        double Mh = params.Mh;
        int id = params.id;

        double z1 = (zh * xi + zh) / 2.;
        double z2 = (zh - zh * xi) / 2.;
        double M1 = Mass_pion_charged;
        double M2 = Mass_pion_charged;
        double RT2 = ((z1 * z2 * pow(Mh, 2)) / (z1 + z2) - pow(M1, 2) * z2 - pow(M2, 2) * z1) / (z1 + z2);
        double RT;
        if (RT2 < 0.)
            return 0.;
        else
            RT = sqrt(RT2);
        double value_of_FF_part = DiFF_z1_z2(id, z1, z2);

        double res = M_PI / 2. * Mh * (1 - pow(xi, 2)) * value_of_FF_part * pp_RT_distribution(RT);
        return res;
    };

    integrand_params params = {zh, Mh, id};
    double result = integrate<integrand_params>(-1, 1, integrand, params);
    return result;
}
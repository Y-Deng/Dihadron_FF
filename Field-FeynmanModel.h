#pragma once
#include <cmath>
#include "Integration.h"

using std::pow;

// The parameters of the model
const double d = 1.5;
const double gamma_value = 0.46;

const double Mass_pion_charged = 0.134;

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

inline double FF_pion_plus_FFs(double *x, double *par)
{
    double z = x[0];
    int id = (int)par[0];
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

inline double FF_pion_minus_FFs(double *x, double *par)
{
    double z = x[0];
    int id = (int)par[0];
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

inline double FF_pion_plus_FFs(double z, int id)
{
    double q = (double)id;
    return FF_pion_plus_FFs(&z, &q);
}
inline double FF_pion_minus_FFs(double z, int id)
{
    double q = (double)id;
    return FF_pion_minus_FFs(&z, &q);
}

// The following two functions are used to do the DGLAP evolution by the QCDNUM package.
inline double FF_pion_plus_FFs_initial(int *ipdf, double *z)
{
    if(*ipdf == 0)
        return 0.;
    else if(*ipdf == 1)
        return FF_pion_plus_FFs(*z, 1);
    else if(*ipdf == 2)
        return FF_pion_plus_FFs(*z, 2);
    else if(*ipdf == 3)
        return FF_pion_plus_FFs(*z, 3);
    else if(*ipdf == 4)
        return FF_pion_plus_FFs(*z, -1);
    else if(*ipdf == 5)
        return FF_pion_plus_FFs(*z, -2);
    else if(*ipdf == 6)
        return FF_pion_plus_FFs(*z, -3);
    else
        return 0.;
}

inline double FF_pion_minus_FFs_initial(int *ipdf, double *z)
{
    if(*ipdf == 0)
        return 0.;
    else if(*ipdf == 1)
        return FF_pion_minus_FFs(*z, 1);
    else if(*ipdf == 2)
        return FF_pion_minus_FFs(*z, 2);
    else if(*ipdf == 3)
        return FF_pion_minus_FFs(*z, 3);
    else if(*ipdf == 4)
        return FF_pion_minus_FFs(*z, -1);
    else if(*ipdf == 5)
        return FF_pion_minus_FFs(*z, -2);
    else if(*ipdf == 6)
        return FF_pion_minus_FFs(*z, -3);
    else
        return 0.;
}

inline int delta_ij(int i, int j)
{
    if (i == j)
        return 1;
    else
       return 0;
}
inline double gamma_index(int i)
{
    if(i == 1) return gamma_value;
    else if(i == 2) return gamma_value;
    else if(i == 3) return 1. - 2.*gamma_value;
    else if(i == -1) return gamma_value;
    else if(i == -2) return gamma_value;
    else if(i == -3) return 1. - 2.*gamma_value;
    else return 0;
}

inline double FF_dihadron_plus_minus_FFs(double z1, double z2, int id)
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

        auto integrand = [](double eta, integrand_params params){
            double z1 = params.z1;
            double z2 = params.z2;
            int id = params.id;
            if( z1 + z2 > eta || eta >= 1. ) return 0.;
            return g(eta)*f(1. - z1/eta) * FF_pion_minus_FFs(z2/(eta-z1), id) /(eta*(eta - z1));
        };

        integrand_params params = {b, z1, z2};
        if(z1 + z2 >= .99) plus_minus = 0.;
        else plus_minus = delta_ij(q, a) * gamma_index(b) * f(1-z1) * FF_pion_minus_FFs(z2/(1.-z1), b) /(1.-z1) 
                            + gamma_index(a)*gamma_index(b) * integrate<integrand_params>(z1+z2, .99, integrand, params);

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
        
        auto integrand = [](double eta, integrand_params params){
            double z1 = params.z1;
            double z2 = params.z2;
            int id = params.id;
            if( z1 + z2 > eta || eta >= 1. ) return 0.;
            return g(eta)*f(1. - z1/eta) * FF_pion_plus_FFs(z2/(eta-z1), id) /(eta*(eta - z1));
        };

        integrand_params params = {b, z1, z2};
        if(z1 + z2 >= 0.99) minus_plus = 0.;
        else minus_plus = delta_ij(q, a) * gamma_index(b) * f(1-z1) * FF_pion_plus_FFs(z2/(1.-z1), b) /(1.-z1) 
                            + gamma_index(a)*gamma_index(b) * integrate<integrand_params>(z1+z2, .99, integrand, params);
    }

    return plus_minus + minus_plus;
}

inline double FF_dihadron_plus_plus_FFs(double z1, double z2, int id)
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

        auto integrand = [](double eta, integrand_params params){
            double z1 = params.z1;
            double z2 = params.z2;
            int id = params.id;
            if( z1 + z2 > eta || eta >= 1. ) return 0.;
            return g(eta)*f(1. - z1/eta) * FF_pion_plus_FFs(z2/(eta-z1), id) /(eta*(eta - z1));
        };

        integrand_params params = {b, z1, z2};
        if(z1 + z2 >= .99) plus_plus = 0.;
        else plus_plus = delta_ij(q, a) * gamma_index(b) * f(1-z1) * FF_pion_plus_FFs(z2/(1.-z1), b) /(1.-z1) 
                            + gamma_index(a)*gamma_index(b) * integrate<integrand_params>(z1+z2, .99, integrand, params);

    }

    return plus_plus;
}
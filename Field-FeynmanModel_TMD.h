#pragma once 

#include "Integration.h"
#include "Field-FeynmanModel.h"
#include "functional"
#include <iostream>
#include "map"

#include "BSpline_Interpolate1D.h"
#include "BSpline_Interpolate2D.h"

using std::map;
using std::function;
using std::sqrt;
using std::pow;
using std::cout;
using std::endl;
using std::isnan;



const map<int, BSplineInterpolate_2D> DiFF_pm_z1z2 = [](){
    map<int, BSplineInterpolate_2D> result;
    vector<int> ids = {1,2,3,-1,-2,-3};
    for(int id : ids)
    {
        string filename = "./DiFF_interpolation_data/DiFF_z1_z2_interpolation_" + std::to_string(id) + ".dat";
        BSplineInterpolate_2D interpolator(filename);
        result[id] = interpolator;
    }
    return result;
}();

inline double TMD_DiFFs_pm(const double &zh, const double& Mh, const int& id, const function<double(double)> &pm_RT_distribution)
{
    struct integrand_params
    {
        double zh;
        double Mh;
        int id;
    };

    function< double(double, integrand_params)> integrand = [&pm_RT_distribution](double xi, integrand_params params) {
        double zh = params.zh;
        double Mh = params.Mh;
        int id = params.id;
        if(id == 0) return 0.;

        double M1 = Mass_pion_charged;
        double M2 = Mass_pion_charged;

        double z1 = (zh*xi + zh)/2.;
        double z2 = (zh - zh*xi)/2.;
        double RT2 = ( ( z1*z2 *pow(Mh,2) )/(z1+z2) - pow(M1,2)*z2 - pow(M2,2)*z1 ) /(z1+ z2);
        double RT;
        if(RT2 < 0.) return 0.;
        else RT = sqrt(RT2);
        
        double value_of_RT_part = pm_RT_distribution(RT);
        double value_of_FF_part = FF_dihadron_plus_minus_FFs(z1, z2, id);
        // double value_of_FF_part = DiFF_pm_z1z2.at(id)(z1, z2);
    
        double res = M_PI/2. * Mh * (1-pow(xi,2)) * value_of_FF_part * value_of_RT_part;
        return res;
    };

    integrand_params params = {zh, Mh, id};
    double result = integrate<integrand_params>(-1,1,integrand,params);
    return result;
}

inline double TMD_DiFFs_pp(double zh, double Mh, int id, const function<double(double)> &pp_RT_distribution)
{
    struct integrand_params
    {
        double zh;
        double Mh;
        int id;
    };
    function< double(double, integrand_params)> integrand = [&pp_RT_distribution](double xi, integrand_params params) {
        double zh = params.zh;
        double Mh = params.Mh;
        int id = params.id;

        double z1 = (zh*xi + zh)/2.;
        double z2 = (zh - zh*xi)/2.;
        double M1 = Mass_pion_charged;
        double M2 = Mass_pion_charged;
        double RT2 =  ( ( z1*z2 *pow(Mh,2) )/(z1+z2) - pow(M1,2)*z2 - pow(M2,2)*z1   ) /(z1+ z2);
        double RT;
        if(RT2 < 0.) return 0.;
        else RT = sqrt(RT2);
        double value_of_FF_part = FF_dihadron_plus_plus_FFs(z1, z2, id);
    
        double res = M_PI/2. * Mh * (1-pow(xi,2)) * value_of_FF_part * pp_RT_distribution(RT);
        return res;
    };

    integrand_params params = {zh, Mh, id};
    double result = integrate<integrand_params>(-1, 1, integrand, params);
    return result;
}
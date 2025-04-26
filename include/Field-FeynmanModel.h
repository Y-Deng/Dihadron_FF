#pragma once

#include "functional"

using std::function;

// The parameters of the model
const double d = 1.5;
const double gamma_value = 0.46;

const double Mass_pion_charged = 0.134;

double FF_pion_plus_FFs_initial(const double &z, const int &id);
double FF_pion_minus_FFs_initial(const double &z, const int &id);

double FF_dihadron_plus_minus_FFs_initial(const double &z1, const double &z2, const int &id);

double FF_dihadron_plus_plus_FFs_initial(const double &z1, const double &z2, const int &id);

double TMD_DiFFs_pm_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(double)> &pm_RT_distribution);

double TMD_DiFFs_pp_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(double)> &pp_RT_distribution);

double TMD_DiFFs_pm_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(int, double, double)> &DiFF_z1_z2,
                            const function<double(double)> &pm_RT_distribution);

double TMD_DiFFs_pp_initial(const double &zh, const double &Mh, const int &id,
                            const function<double(int, double, double)> &DiFF_z1_z2,
                            const function<double(double)> &pp_RT_distribution);
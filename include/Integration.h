#pragma once

#include "gsl/gsl_errno.h"
#include "gsl/gsl_integration.h"
#include "gsl/gsl_math.h"

#include "functional"
#include "iostream"
#include "stdexcept"
#include "string"
#include <cmath>

class GSLIntegrationError : public std::runtime_error
{
  public:
    GSLIntegrationError(const std::string &msg) : std::runtime_error(msg)
    {
    }
};

template <typename T> using integrand_function = std::function<double(double eta, T par)>;

template <typename T> double integrate(double lower_limit, double upper_limit, integrand_function<T> func, T par)
{
    static auto error_handler = gsl_set_error_handler_off();

    double result, error;
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(10000);
    struct integrand_struct
    {
        integrand_function<T> func;
        T par;
    };
    auto integrand = [](double eta, void *params) {
        integrand_struct *p = (integrand_struct *)params;
        double value = p->func(eta, p->par);
        return value;
    };
    integrand_struct par_struct = {func, par};

    gsl_function F;
    F.function = integrand;
    F.params = &par_struct;

    try
    {
        int status = gsl_integration_qags(&F, lower_limit, upper_limit, 0, 1e-3, 10000, w, &result, &error);
        if (status != GSL_SUCCESS)
        {
            std::cerr << "Integration failed "
                      << "Integration result: " << result << " ± " << error << std::endl;
            throw GSLIntegrationError(std::string("GSL Integration Error: ") + gsl_strerror(status));
        }
    }
    catch (const GSLIntegrationError &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    gsl_integration_workspace_free(w);

    return result;
}
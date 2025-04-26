#include "BSpline_Interpolate.h"
#include "DiFF_TMD.h"
#include "Tools.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void output_DiFF_z1_z2()
{
    int z1_degree = 2;
    int z2_degree = 2;
    int z1_num_ctrl = 100;
    int z2_num_ctrl = 100;
    double z1_lower = 0.02;
    double z1_upper = 1.;
    double z2_lower = 0.2;
    double z2_upper = 2.;

    vector<double> z1_grid = linspace<double>(z1_lower + 1.e-3, z1_upper - 1.e-3, z1_num_ctrl);
    vector<double> z2_grid = linspace<double>(z2_lower + 1.e-3, z2_upper - 1.e-3, z2_num_ctrl);

    vector<int> flavors = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    for (auto id : flavors)
    {
        cout << "flavor: " << id << endl;
        vector<vector<double>> pm_DiFF_z1_z2(z1_grid.size(), vector<double>(z2_grid.size()));
        vector<vector<double>> pp_DiFF_z1_z2(z1_grid.size(), vector<double>(z2_grid.size()));
        for (size_t i = 0; i < z1_grid.size(); i++)
        {
            for (size_t j = 0; j < z1_grid.size(); j++)
            {
                pm_DiFF_z1_z2[i][j] = FF_dihadron_plus_minus_FFs_initial(z1_grid[i], z2_grid[j], id);
                pp_DiFF_z1_z2[i][j] = FF_dihadron_plus_plus_FFs_initial(z1_grid[i], z2_grid[j], id);
            }
        }
        BSplineInterpolate_2D interpolator_pm(z1_degree, z2_degree, z1_lower, z1_upper, z2_lower, z2_upper, z1_grid,
                                              z2_grid, pm_DiFF_z1_z2);
        BSplineInterpolate_2D interpolator_pp(z1_degree, z2_degree, z1_lower, z1_upper, z2_lower, z2_upper, z1_grid,
                                              z2_grid, pp_DiFF_z1_z2);

        string pm_filename = "pm_DiFF_z1_z2_" + to_string(id) + ".txt";
        string pp_filename = "pp_DiFF_z1_z2_" + to_string(id) + ".txt";
        interpolator_pm.save(pm_filename);
        interpolator_pp.save(pp_filename);
    }
}

int main()
{
    output_DiFF_z1_z2();
    return 0;
}
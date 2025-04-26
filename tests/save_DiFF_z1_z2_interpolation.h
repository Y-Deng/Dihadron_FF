#pragma once

#include "../include/BSpline_Interpolate.h"
#include "../include/Field-FeynmanModel.h"
#include "../include/Tools.h"

#include "string"
#include "vector"

#include "ROOT/TAxis.h"
#include "ROOT/TCanvas.h"
#include "ROOT/TGraph.h"

using std::string;
using std::vector;

inline int save_DiFF_z1_z2_interpolation(string filename) {
  double interpolation_z_lower = 0.0;
  double interpolation_z_upper = 1.0;
  int interpolation_z_num_points = 80;
  int interpolation_BSpline_degree = 3;

  vector<double> interpolation_z_points =
      linspace(interpolation_z_lower + 1.e-5, interpolation_z_upper - 1.e-5,
               interpolation_z_num_points);

  vector<int> flavor_ids = {1, 2, 3, -1, -2, -3};

  for (int i_flavor = 0; i_flavor < flavor_ids.size(); ++i_flavor) {
    int id = flavor_ids[i_flavor];
    vector<vector<double>> interpolation_DiFF_z1_z2_points =
        [&interpolation_z_num_points, &interpolation_z_points, &id]() {
          vector<vector<double>> result(
              interpolation_z_num_points,
              vector<double>(interpolation_z_num_points));
          for (int i = 0; i < interpolation_z_num_points; ++i) {
            for (int j = 0; j < interpolation_z_num_points; ++j) {
              double z1 = interpolation_z_points[i];
              double z2 = interpolation_z_points[j];
              double DiFF_z1_z2 =
                  FF_dihadron_plus_minus_FFs_initial(z1, z2, id);
              result[i][j] = DiFF_z1_z2;
            }
          }

          return result;
        }();

    BSplineInterpolate_2D interpolation_DiFF_z1_z2(
        interpolation_BSpline_degree, interpolation_BSpline_degree,
        interpolation_z_lower, interpolation_z_upper, interpolation_z_lower,
        interpolation_z_upper, interpolation_z_points, interpolation_z_points,
        interpolation_DiFF_z1_z2_points);

    string filename_DiFF_z1_z2 = filename + "_" + std::to_string(id) + ".dat";
    interpolation_DiFF_z1_z2.save(filename_DiFF_z1_z2);

    int check_index = 10;
    TCanvas *c = new TCanvas("c", "c", 2400, 600);
    TGraph *g =
        new TGraph(interpolation_z_num_points, &interpolation_z_points[0],
                   &interpolation_DiFF_z1_z2_points[check_index][0]);
    g->GetYaxis()->SetLimits(-10, 100.0);
    g->GetYaxis()->SetRangeUser(-10, 100.0);
    g->SetMarkerStyle(20);
    g->SetMarkerSize(1.0);
    g->Draw("AP");

    vector<double> test_DiFF(interpolation_z_num_points);
    for (int i = 0; i < interpolation_z_num_points; ++i) {
      test_DiFF[i] = interpolation_DiFF_z1_z2(
          interpolation_z_points[check_index], interpolation_z_points[i]);
    }

    TGraph *g_test = new TGraph(interpolation_z_num_points,
                                &interpolation_z_points[0], &test_DiFF[0]);
    g_test->SetMarkerStyle(24);
    g_test->SetMarkerSize(1.0);
    g_test->Draw("PL same");

    stringstream ss;
    ss << filename << "_" << id << ".png";
    c->SaveAs(ss.str().c_str());
  }

  return 0;
}
#include "BSpline_Interpolate1D.h"
#include "BSpline_Interpolate2D.h"

#include "save_DiFF_z1_z2_interpolation.h"

#include "test_BSpline_interpolate.h"

#include "Field-FeynmanModel.h"
#include "DiFF_TMD.h"
#include "string"
#include "chrono"


using namespace std;

int test(int argc, char* argv[])
{
    double zh = 0.2;
    double Mh_value = 0.5;
    double mu2 = 11;
    int id = 2;

    auto start = std::chrono::high_resolution_clock::now(); 
    test_QCDNUM_evolved_DiFF_TMD(zh, Mh_value, mu2, id);
    auto end = std::chrono::high_resolution_clock::now(); 

    std::chrono::duration<double> elapsed = end - start;
    cout << "elapsed time: " << elapsed.count() << "s\n";

    return 0;
}

int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now(); 
    test_3D_BSpline_interpolate();
    auto end = std::chrono::high_resolution_clock::now(); 
    std::chrono::duration<double> elapsed = end - start;
    cout << "elapsed time: " << elapsed.count() << "s\n";

    return 0;
}
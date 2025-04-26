#include "../include/BSpline_Interpolate.h"
#include "../src/test_BSpline_interpolate.h"

using namespace std;

int main(int argc, char *argv[])
{
    // Test the BSpline_Interpolate1D class
    test_1D_BSpline_interpolate();
    cout << "finished test 1D" << endl;
    test_2D_BSpline_interpolate();
    cout << "finished test 2D" << endl;
    test_3D_BSpline_interpolate();
    return 0;
}
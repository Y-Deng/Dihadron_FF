#include "../include/BSpline_Interpolate.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include <Eigen/src/Core/Matrix.h>
#include <algorithm>
#include <array>
#include <vector>

using namespace std;
using namespace Eigen;

using SpMat = SparseMatrix<double>;
using Elem = Triplet<double>;

// int findSpan(double x, const VectorXd &knots, int degree)
// {
//     int n = knots.size() - degree - 1;
//     if (x == knots(n))
//         return n - 1;
//     int low = degree, high = n, mid;
//     while (low <= high)
//     {
//         mid = (low + high) / 2;
//         if (x < knots[mid])
//             high = mid - 1;
//         else if (x >= knots[mid + 1])
//             low = mid + 1;
//         else
//             return mid;
//     }
//     return -1; // error
// }

int findSpan(double x, const Eigen::VectorXd &knots, int degree)
{
    int n = knots.size() - degree - 1;

    // 特别处理边界：x == 最后一个节点
    if (x >= knots[n])
        return n - 1;

    if (x <= knots[degree])
        return degree;

    int low = degree, high = n - 1, mid;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < knots[mid])
            high = mid - 1;
        else if (x >= knots[mid + 1])
            low = mid + 1;
        else
            return mid;
    }

    // 这个 return 理论上不会被触发，但保险加一个 fallback
    return degree;
}

// std::vector<int> activeBasisFunctions(double x, const VectorXd &knots, int degree)
// {
//     int span = findSpan(x, knots, degree);
//     std::vector<int> indices;
//     for (int i = span - degree; i <= span; ++i)
//         indices.push_back(i);
//     return indices;
// }

std::vector<int> activeBasisFunctions(double x, const VectorXd &knots, int degree)
{
    int span = findSpan(x, knots, degree);

    if (span < degree)
        span = degree; // 防止负数

    int max_index = knots.size() - 1;
    if (span > max_index)
        span = max_index;

    std::vector<int> indices;
    for (int i = span - degree; i <= span; ++i)
    {
        if (i >= 0 && i <= max_index) // 添加越界保护
            indices.push_back(i);
    }

    return indices;
}
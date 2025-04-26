#include "../include/BSpline.h"
#include "../include/BSpline_Interpolate.h"
#include <Eigen/Sparse>
#include <Eigen/src/Core/Matrix.h>

#include <chrono>
#include <iostream>
#include <vector>

using namespace Eigen;
using namespace std;

using SpMat = SparseMatrix<double>;
using T = Triplet<double>;

int test_Eigen_Solve_BSpine_Interpolation_Matrix() {
  // VectorXd knot =

  return 0;
}

int main() {
  const int n = 10;        // 矩阵大小
  const int bandwidth = 2; // 对角 ±1 共三条带

  vector<T> tripletList;

  // 构造带状稀疏矩阵
  for (int i = 0; i < n; ++i) {
    for (int j = max(0, i - bandwidth); j <= min(n - 1, i + bandwidth); ++j) {
      double value = (i == j) ? 4.0 : -1.0; // 中间对角线为4，旁边为-1
      tripletList.emplace_back(i, j, value);
    }
  }

  SpMat A(n, n);
  A.setFromTriplets(tripletList.begin(), tripletList.end());

  // 生成已知解 x_true
  VectorXd x_true(n);
  for (int i = 0; i < n; ++i)
    x_true(i) = i + 1;

  // 计算 b = A * x_true
  VectorXd b = A * x_true;

  // 求解 Ax = b
  SparseLU<SpMat> solver;
  solver.compute(A);
  if (solver.info() != Success) {
    cerr << "分解失败！" << endl;
    return -1;
  }

  VectorXd x = solver.solve(b);
  if (solver.info() != Success) {
    cerr << "求解失败！" << endl;
    return -1;
  }

  // 打印结果
  cout << "原始 x_true:\n" << x_true.transpose() << endl;
  cout << "求解 x:\n" << x.transpose() << endl;
  cout << "误差范数: " << (x - x_true).norm() << endl;

  return 0;
}

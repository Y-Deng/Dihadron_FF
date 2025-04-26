#include "../include/Tools.h"
#include <complex>
#include <gsl/gsl_linalg.h> // GSL线性代数库

#include <initializer_list>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

using namespace std;

// template <typename T> std::vector<T> flatten(const std::vector<std::vector<T>> &nestedVec)
// {
//     std::vector<T> flattenedVec;
//     for (const auto &vec : nestedVec)
//     {
//         flattenedVec.insert(flattenedVec.end(), vec.begin(), vec.end());
//     }
//     return flattenedVec;
// }
// template vector<double> flatten(const vector<vector<double>> &);

// // 使用GSL求解线性方程组Ax=b
// void solve_linear_system_LU(int n, const std::vector<double> &A_data, const std::vector<double> &b_data,
//                             std::vector<double> &x_out)
// {
//     // 分配GSL矩阵和向量
//     gsl_matrix *A = gsl_matrix_alloc(n, n);
//     gsl_vector *b = gsl_vector_alloc(n);
//     gsl_vector *x = gsl_vector_alloc(n);
//     gsl_permutation *p = gsl_permutation_alloc(n);

//     // 填充矩阵A和向量b
//     for (int i = 0; i < n; ++i)
//     {
//         gsl_vector_set(b, i, b_data[i]);
//         for (int j = 0; j < n; ++j)
//         {
//             gsl_matrix_set(A, i, j, A_data[i * n + j]);
//         }
//     }

//     // LU分解解方程
//     int signum;
//     if (gsl_linalg_LU_decomp(A, p, &signum) != GSL_SUCCESS)
//     {
//         std::cerr << "LU decomposition failed!" << std::endl;
//         return;
//     }
//     if (gsl_linalg_LU_solve(A, p, b, x) != GSL_SUCCESS)
//     {
//         std::cerr << "LU solve failed!" << std::endl;
//         return;
//     }

//     // 提取结果
//     x_out.resize(n);
//     for (int i = 0; i < n; ++i)
//     {
//         x_out[i] = gsl_vector_get(x, i);
//     }

//     // 释放资源
//     gsl_matrix_free(A);
//     gsl_vector_free(b);
//     gsl_vector_free(x);
//     gsl_permutation_free(p);
// }

// vector<double> solve_linear_system(vector<vector<double>> A, vector<double> b)
// {
//     int n = b.size();
//     int m = A.size();
//     if (m != n)
//     {
//         std::cerr << "Error: A and b have different sizes!" << std::endl;
//         return vector<double>();
//     }

//     for (auto line : A)
//     {
//         if (line.size() != n)
//         {
//             std::cerr << "Error: A is not a square matrix!" << std::endl;
//             return vector<double>();
//         }
//     }

//     vector<double> Platten_A = flatten(A);

//     vector<double> x_out;
//     solve_linear_system_LU(n, Platten_A, b, x_out);

//     return x_out;
// }

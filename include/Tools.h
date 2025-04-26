#pragma once

#include <iostream>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;

// 生成等间距的数组，使用方法与python相同
template <typename T> vector<T> linspace(const T &start, const T &end, const int &num)
{
    vector<T> result(num);
    T step = (end - start) / (num - 1);
    for (int i = 0; i < num; ++i)
    {
        result[i] = start + i * step;
    }
    return result;
}

// 打印矢量和矩阵
template <typename T> void print_vector(const vector<T> &vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T> void print_matrix(const vector<vector<T>> &mat)
{
    for (int i = 0; i < mat.size(); ++i)
    {
        for (int j = 0; j < mat[i].size(); ++j)
        {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T> std::vector<T> flatten(const std::vector<std::vector<T>> &nestedVec)
{
    std::vector<T> flattenedVec;
    for (const auto &vec : nestedVec)
    {
        flattenedVec.insert(flattenedVec.end(), vec.begin(), vec.end());
    }
    return flattenedVec;
}

// 将二维的矩阵压平
// 实例化模板
// extern template vector<double> flatten<double>(const vector<vector<double>> &nestedVec);
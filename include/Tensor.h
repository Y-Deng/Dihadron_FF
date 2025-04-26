#include <initializer_list>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <vector>

template <typename T> class Tensor
{
  private:
    std::vector<size_t> shape;   // 每一阶的维度
    std::vector<size_t> strides; // 用于多维索引到1D映射
    std::vector<T> data;         // 张量数据，flattened

    // 根据 shape 计算 strides
    void compute_strides()
    {
        strides.resize(shape.size());
        size_t stride = 1;
        for (int i = shape.size() - 1; i >= 0; --i)
        {
            strides[i] = stride;
            stride *= shape[i];
        }
    }

    size_t total_size() const
    {
        return std::accumulate(shape.begin(), shape.end(), size_t(1), std::multiplies<size_t>());
    }

    size_t compute_offset(const std::vector<size_t> &indices) const
    {
        if (indices.size() != shape.size())
            throw std::invalid_argument("Incorrect number of indices.");
        size_t offset = 0;
        for (size_t i = 0; i < indices.size(); ++i)
            offset += strides[i] * indices[i];
        return offset;
    }

  public:
    // 构造函数：任意阶数的维度参数
    template <typename... Dims> explicit Tensor(Dims... dims) : shape{static_cast<size_t>(dims)...}
    {
        static_assert(sizeof...(Dims) >= 1, "Tensor must have at least one dimension.");
        compute_strides();
        data.resize(total_size());
    }

    // 获取 shape
    const std::vector<size_t> &get_shape() const
    {
        return shape;
    }

    // 获取元素（只读）
    template <typename... Indices> const T &operator()(Indices... indices) const
    {
        std::vector<size_t> idx{static_cast<size_t>(indices)...};
        return data[compute_offset(idx)];
    }

    // 获取元素（可写）
    template <typename... Indices> T &operator()(Indices... indices)
    {
        std::vector<size_t> idx{static_cast<size_t>(indices)...};
        return data[compute_offset(idx)];
    }

    // 获取底层扁平化数据
    const std::vector<T> &flat_data() const
    {
        return data;
    }
};

/*! \headerfile std::array.hpp "include/QLab/math/std::array.hpp"
    \brief std::array
 *
 * class which imitates n-dim std::array
 */

#ifndef QLAB_MATH_ARRAY_HPP_GOWKGNDK
#define QLAB_MATH_ARRAY_HPP_GOWKGNDK

#include <cstddef>
#include <memory>
#include <vector>
#include <array>
#include <functional>
#include <algorithm>

namespace {
    using std::vector;
}

namespace QLab {


//! n-dim array
/*!
    This class implements the array concept in linear algebra
 */
template <typename T, unsigned Dim>
class Array
{
public:
    using value_type = T;
    using size_type  = std::size_t;
    using shape_type = std::array<size_type, Dim>;

    static constexpr unsigned dim = Dim;
    static constexpr size_type size(shape_type);

    //! constructors
    explicit Array() : data_(std::make_unique<vector<value_type>>()), shape_{} {};
    explicit Array(const shape_type, value_type = T());
    template<typename InputIt>
    explicit Array(const shape_type, InputIt first, InputIt last);
    Array(const Array &);
    Array(Array &&);

    //! copy assignment operator
    Array& operator=(const Array &);
    Array& operator=(Array &&);

    //! swap
    void swap(Array & other) noexcept {data_.swap(other.data_);} ;

    //! size
    /*!
     *  return the size (n_1 * n_2 * ... * n_dim) of the Array
     */
    size_type size() {return size(shape_);}

    /*! \name Comparison
     *  Detailed description. Details. 
     */
    //@{
    bool operator==(const Array&) const;
    bool operator!=(const Array&) const;
    //@}


private:
    std::unique_ptr<vector<value_type>> data_;
    shape_type shape_;
};

//template <typename T, unsigned Dim>
//void Array<T, Dim>::swap( Array & other) noexcept
//{
//    data_.swap(other.data_);
//}

/*! \name Unary operators
 *	
 */
//@{
template <typename T, unsigned Dim>
Array<T, Dim>&& operator+(const Array<T, Dim>&);
template <typename T, unsigned Dim>
Array<T, Dim>&& operator+(Array<T, Dim>&&);
template <typename T, unsigned Dim>
Array<T, Dim>&& operator-(const Array<T, Dim>&);
template <typename T, unsigned Dim>
Array<T, Dim>&& operator-(Array<T, Dim>&&);
//@}

template <typename T, unsigned Dim>
Array<T, Dim>::Array(const shape_type shape, value_type value)
{
    shape_type tmp_shape = shape;
    auto tmp_data = std::make_unique<vector<T>>(size(shape), value);
    shape_.swap(tmp_shape);
    data_.swap(tmp_data);
}

template <typename T, unsigned Dim>
template <typename InputIt>
Array<T, Dim>::Array(const shape_type shape, InputIt first, InputIt last)
{
    shape_type tmp_shape = shape;
    auto tmp_data = std::make_unique<vector<T>>(first, last);
    shape_.swap(tmp_shape);
    data_.swap(tmp_data);
}

template <typename T, unsigned Dim>
Array<T, Dim>::Array(const Array & other)
{
    auto tmp_data = std::make_unique<vector<T>>(*other.data_);
    data_.swap(tmp_data);
}

template <typename T, unsigned Dim>
Array<T, Dim>::Array(Array && other)
{
    data_ = std::make_unique<vector<T>>();
    data_.swap(other.data_);
}

template <typename T, unsigned Dim>
constexpr auto Array<T, Dim>::size(shape_type shape) -> size_type
{
    if (shape.empty())
    {
        return 0;
    }
    size_type size (1);
    for (int i = 0; i < shape.size(); i++)
    {
        size *= shape[i];
    }
    return size;
}

template <typename T, unsigned Dim>
bool Array<T, Dim>::operator==(const Array& rhs) const
{
    return (shape_ == rhs.shape_) && (data_ == rhs.data_);
}

template <typename T, unsigned Dim>
bool Array<T, Dim>::operator!=(const Array& rhs) const
{
    return !operator==(rhs);
}

template <typename T, unsigned Dim>
Array<T, Dim>&& operator+(const Array<T, Dim>& a)
{
    Array<T, Dim> result(a);
    return std::move(result);
}

template <typename T, unsigned Dim>
Array<T, Dim>&& operator+(Array<T, Dim>&& a)
{
    return std::move(a);
}

template <typename T, unsigned Dim>
Array<T, Dim>&& operator-(const Array<T, Dim>& a)
{
    Array<T, Dim> result(a);
    std::transform(result.begin(), result.end(), result.begin(), std::negate<T>());
    return std::move(result);
}

template <typename T, unsigned Dim>
Array<T, Dim>&& operator-(Array<T, Dim>&& a)
{
    std::transform(a.begin(), a.end(), a.begin(), std::negate<T>());
    return std::move(a);
}


} // namespace QLab  

#endif // end of include guard: QLAB_MATH_ARRAY_HPP_GOWKGNDK

#ifndef QLAB_MATH_ARRAY_HPP_GOWKGNDK
#define QLAB_MATH_ARRAY_HPP_GOWKGNDK

namespace QLab {


template <typename Element, unsigned Dim = 1>
class Array
{
public:
    using element_type = Element;
    static constexpr unsigned dim() {return dim_;}

private:
    static constexpr unsigned dim_ = Dim;

};


} // namespace QLab  

#endif // end of include guard: QLAB_MATH_ARRAY_HPP_GOWKGNDK

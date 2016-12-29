#ifndef QLAB_UTILITIES_TRAITS_HPP_PGJTKIAA
#define QLAB_UTILITIES_TRAITS_HPP_PGJTKIAA

#include <type_traits>
#include "QLab/utilities/int_adapter.hpp"

namespace QLab {

// IntAdapter type traits
template<typename T> struct treat_as_floating_point : std::is_floating_point<T> {} ;

template<typename T>
struct treat_as_floating_point<IntAdapter<T>> : std::true_type {};


} // namespace QLab  

#endif // end of include guard: QLAB_UTILITIES_TRAITS_HPP_PGJTKIAA

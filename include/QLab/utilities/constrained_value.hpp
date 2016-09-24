#ifndef UTILITIES_CONSTRAINED_VALUE_HPP
#define UTILITIES_CONSTRAINED_VALUE_HPP


#include <stdexcept>

namespace QLab
{


template <typename ValuePolicy>
class ConstrainedValue
{
public:
    using ValueT = typename ValuePolicy::ValueT;
    
    // TODO: check if assign value_ some value
    ConstrainedValue (ValueT value) {
        if (ValuePolicy::validate(value)) {
            value_  = value;
        } else {
            ValuePolicy::on_error(value);
        }
        
    }
    // all cases expecting ValueT should accept ConstrainedValueT<ValuePolicy<ValueT>>
    operator ValueT () const { return value_; }

private:
    ValueT value_;
};


template <typename ValueT_, ValueT_ min>
class LowerBounded
{
public:
    using ValueT = ValueT_;

    static bool validate (ValueT value) {
        if (value < min) {
            return false;
        } else {
            return true;
        }
    }

    static void on_error(ValueT value) {
        throw std::out_of_range("violated lower bound constraint");
    }

};


template <typename ValueT_, ValueT_ max>
class UpperBounded
{
public:
    using ValueT = ValueT_;

    static bool validate (ValueT value) {
        if (value > max) {
            return false;
        } else {
            return true;
        }
    }

    static void on_error(ValueT value) {
        throw std::out_of_range("violated upper bound constraint");
    }

};


template <class ValueT_, ValueT_ min, ValueT_ max>
class BiBounded {
public:
    using ValueT = ValueT_;

    static bool validate (ValueT value) {
        if (value < min) {
            return false;
        } else if (value > max) {
            return false;
        } else {
            return true;
        }

    }
    
    static void on_error(ValueT value) {
        throw std::out_of_range("violated bi bound constraint");
    }

};


} // namespace QLab  


#endif // end of include guard: UTILITIES_CONSTRAINED_VALUE_HPP

#ifndef UTILITIES_CONSTRAINED_VALUE_HPP
#define UTILITIES_CONSTRAINED_VALUE_HPP


#include <stdexcept>

namespace QLab
{


template <typename ValuePolicy>
class ConstrainedValue
{
public:
    using value_type = typename ValuePolicy::value_type;
    
    // TODO: check if assign value_ some value
    ConstrainedValue (value_type value) {
        if (ValuePolicy::validate(value)) {
            value_  = value;
        } else {
            ValuePolicy::on_error(value);
        }
        
    }
    // all cases expecting value_type should accept ConstrainedValueT<ValuePolicy<value_type>>
    operator value_type () const { return value_; }

private:
    value_type value_;
};


template <typename Value_, Value_ min>
class LowerBounded
{
public:
    using value_type = Value_;

    static bool validate (value_type value) {
        if (value < min) {
            return false;
        } else {
            return true;
        }
    }

    static void on_error(value_type value) {
        throw std::out_of_range("violated lower bound constraint");
    }

};


template <typename Value_, Value_ max>
class UpperBounded
{
public:
    using value_type = Value_;

    static bool validate (value_type value) {
        if (value > max) {
            return false;
        } else {
            return true;
        }
    }

    static void on_error(value_type value) {
        throw std::out_of_range("violated upper bound constraint");
    }

};


template <class Value_, Value_ min, Value_ max>
class BiBounded {
public:
    using value_type = Value_;

    static bool validate (value_type value) {
        if (value < min) {
            return false;
        } else if (value > max) {
            return false;
        } else {
            return true;
        }

    }
    
    static void on_error(value_type value) {
        throw std::out_of_range("violated bi bound constraint");
    }

};


} // namespace QLab  


#endif // end of include guard: UTILITIES_CONSTRAINED_VALUE_HPP

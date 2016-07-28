
#include <stdexcept>

namespace QLab
{


template <class value_policy>
class constrained_value_t
{
public:
    using value_t = typename value_policy::value_t;
    
    // TODO: check if assign value_ some value
    constrained_value_t (value_t value) {
        if (value_policy::validate(value)) {
            value_  = value;
        } else {
            value_policy::on_error(value);
        }
        
    }
    // all cases expecting value_t should accept constrained_value_t<value_policy<value_t>>
    operator value_t () const { return value_; }

private:
    value_t value_;
};


template <class value_t_, value_t_ min, value_t_ max>
class double_bound {
public:
    using value_t = value_t_;

    static bool validate(value_t value) {
        if (value < min) {
            return false;
        } else if (value > max) {
            return false;
        } else {
            return true;
        }

    }
    
    static void on_error(value_t value) {
        throw std::out_of_range("violated double bound constraint");
    }

};


} // namespace QLab  

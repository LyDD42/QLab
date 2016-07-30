
#include <stdexcept>

namespace QLab
{


template <class ValuePolicy>
class ConstrainedValueT
{
public:
    using ValueT = typename ValuePolicy::ValueT;
    
    // TODO: check if assign value_ some value
    ConstrainedValueT (ValueT value) {
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


template <class ValueT_, ValueT_ min, ValueT_ max>
class DoubleBound {
public:
    using ValueT = ValueT_;

    static bool validate(ValueT value) {
        if (value < min) {
            return false;
        } else if (value > max) {
            return false;
        } else {
            return true;
        }

    }
    
    static void on_error(ValueT value) {
        throw std::out_of_range("violated double bound constraint");
    }

};


} // namespace QLab  

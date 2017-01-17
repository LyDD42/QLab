#ifndef QLAB_PATTERNS_OBSERVER_HPP_01FIWB5E
#define QLAB_PATTERNS_OBSERVER_HPP_01FIWB5E

#include <set>
#include <memory>

namespace QLab {


class Observable;
class Observer;


class Observable {
public:
    using set_type  = std::set<Observer*>;
    using size_type = set_type::size_type;
    using iterator  = set_type::iterator;

    Observable();
    Observable( const Observable & );
    Observable& operator= ( const Observable& );

    virtual ~Observable();
    void notifyObservers () ;

    std::pair<iterator, bool> registerObserver( Observer* );
    size_type unregisterObserver( Observer* );

private:
    set_type observers_;

};

class Observer {
public:
    using set_type = std::set<std::shared_ptr<Observable>>;
    using iterator = set_type::iterator;

private:


};


} // namespace QLab  

#endif // end of include guard: QLAB_PATTERNS_OBSERVER_HPP_01FIWB5E

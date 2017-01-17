#ifndef QLAB_PATTERNS_SINGLETON_CPP_MYVODS4H
#define QLAB_PATTERNS_SINGLETON_CPP_MYVODS4H


namespace QLab {


template <typename T>
class Singleton
{
public:
    Singleton() {} ;
    Singleton( Singleton& ) = delete;
    Singleton& operator=( Singleton& ) = delete;
    T& instance() { return instance_; } ;

private:
    T instance_;
};


} // namespace QLab  



#endif // end of include guard: QLAB_PATTERNS_SINGLETON_CPP_MYVODS4H

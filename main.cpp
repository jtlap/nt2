/*
#include <iostream>
#include <complex>

#include <nt2/sdk/meta/category.hpp>

namespace nt2 { namespace tag
{
  struct scalar_      {};
  struct arithmetic_  {};

  struct simd_        {};

  struct complex_     {};
} }

template<class T, std::size_t R>
struct  scalar_
      : nt2::tag::category<scalar_<T,R>,0,R>
{
  typedef nt2::tag::scalar_ tag(T);
};

template<class T, class X,std::size_t R>
struct  simd_
      : nt2::tag::category<simd_<T,X,R>,1,R>
{
  typedef nt2::tag::simd_ tag(T,X);
};

template<class T, std::size_t R> struct expr_   : nt2::tag::category<expr_<T,R>,2,R>   {  typedef T tag; };
template<class T, std::size_t R> struct const_  : nt2::tag::category<const_<T,R>,3,R>  {  typedef T tag; };

#include <nt2/sdk/functor/functor.hpp>

struct foo_op {};

namespace nt2 { namespace functors
{
  template<class X,class I>
  struct call<foo_op,tag::scalar_(X),I>
  {
    typedef float result_type;

    float operator()(float d, float s) { return (d+s); }
  };

  template<class I>
  struct call<foo_op,tag::scalar_(tag::arithmetic_),I>
  {
    template<class Sig> struct result;
    template<class This,class T, class U>
    struct result<This(T,U)>
    {
      typedef T& type;
    };

    template<class T, class U> inline
    T& operator()(T& d, U const& s) { return (d=s); }
  };
} }

namespace nt2 { namespace meta
{
  template<> struct category_of<double> : scalar_<tag::arithmetic_,0> {};
  template<> struct category_of<float>  : scalar_<tag::arithmetic_,0>  {};
  template<> struct category_of<int>    : scalar_<tag::arithmetic_,0>  {};

  template<class T>
  struct category_of< std::complex<T> > : scalar_< tag::complex_,0 > {};
} }

int main()
{
  float u;
  nt2::functors::functor<foo_op> f;
  f(u,3.f);
  std::cout << u << std::endl;

}
*/

#include <nt2/sdk/errors/trap.hpp>
#include <boost/mpl/bool.hpp>

template<int N> static inline void foo()
{
  nt2::sys::trap< boost::mpl::bool_<(N<4)> >();
}

int main()
{
  foo<7>();
  foo<1>();
  foo<3>();
}

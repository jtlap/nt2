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
#include <nt2/sdk/details/type_id.hpp>

struct foo_op {};

namespace nt2 { namespace functors
{
  template<class I>
  struct call<foo_op,tag::scalar_(tag::arithmetic_),I>
  {
    template<class Sig> struct result;
    template<class This,class T, class U>
    struct result<This(T,U)>
    {
      typedef T type;
    };

    template<class T, class U> inline
    T operator()(T const & d, U const& s) { return (d+s); }
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


#include <nt2/sdk/meta/any.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/type_traits/is_same.hpp>

  using nt2::meta::any;
  using boost::is_same;
  using boost::mpl::_1;

template<class... Args> struct test : any< is_same<_1,bool>, Args...>::type {};

int main()
{
  float u = 4;
  nt2::functors::functor<foo_op> f;
  std::cout << f(u,3.f) << std::endl;

  std::cout << test<float>::value << std::endl;
  std::cout << test<bool>::value << std::endl;
  std::cout << test<boost::mpl::vector<float,float,float,bool,float> >::value << std::endl;
}

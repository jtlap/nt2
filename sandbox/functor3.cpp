#include <iostream>
#include <vector>
#include <boost/mpl/if.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/enable_if_type.hpp>
#include <nt2/sdk/functor/details/tags.hpp>

using namespace std;

namespace nt2 { namespace tag
{
  struct unknown_     {};
  struct fundamental_ {};
  struct arithmetic_  {};
  struct bool_    {};
  struct float_   {}; struct double_    {};
  struct integer_ {}; struct real_      {};
  struct signed_  {}; struct unsigned_  {};
  struct int_     {}; struct uint_      {};
  struct type8_   {}; struct type16_    {}; struct type32_  {}; struct type64_  {};
  struct ints8_   {}; struct ints16_    {}; struct ints32_  {}; struct ints64_  {};
  struct int8_    {}; struct int16_     {}; struct int32_   {}; struct int64_   {};
  struct uint8_   {}; struct uint16_    {}; struct uint32_  {}; struct uint64_  {};
} }

namespace nt2 { namespace meta
{
  template<class T> struct unknown_ {};
  template<class T> struct fundamental_ : unknown_<T> { typedef unknown_<T> parent; };
  template<class T> struct arithmetic_  : fundamental_<T> { typedef fundamental_<T> parent; };
  template<class T> struct integer_     : arithmetic_<T>  { typedef arithmetic_<T> parent; };

  template<class T> struct signed_
        : boost::mpl::if_ < boost::is_integral<T>
                                  , integer_<T>
                                  , arithmetic_<T>
                                  >::type
  {
    typedef typename boost::mpl::if_< boost::is_integral<T>
                                    , integer_<T>
                                    , arithmetic_<T>
                                    >::type   parent;
  };

  template<class T> struct unsigned_  : integer_<T>
  {
    typedef integer_<T>     parent;
    typedef tag::unsigned_  type;
  };
  template<class T> struct real_      : signed_<T>
  {
    typedef signed_<T>  parent;
    typedef tag::real_  type;
  };

  template<class T> struct int_       : signed_<T>    { typedef signed_<T>    parent; };
  template<class T> struct uint_      : unsigned_<T>  { typedef unsigned_<T>  parent; };

  template<class T>
  struct  type8_
        : boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type
  {
    typedef typename boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type parent;
  };

  template<class T>
  struct  type16_
        : boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type
  {
    typedef typename boost::mpl::if_ < boost::is_signed<T>
                                  , int_<T>
                                  , uint_<T>
                                  >::type parent;
  };

  template<class T>
  struct  type32_
        : boost::mpl::if_ < boost::is_floating_point<T>
                          , real_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type
  {
    typedef typename boost::mpl::if_ < boost::is_floating_point<T>
                          , real_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type parent;
  };

  template<class T>
  struct  type64_
        : boost::mpl::if_ < boost::is_floating_point<T>
                          , real_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type
  {
    typedef typename boost::mpl::if_ < boost::is_floating_point<T>
                          , real_<T>
                          , typename boost::mpl::if_< boost::is_signed<T>
                                                    , int_<T>
                                                    , uint_<T>
                                                    >::type

                          >::type parent;
  };

  template<class T> struct ints8_   : type8_<T>  { typedef type64_<T> parent; };
  template<class T> struct ints16_  : type16_<T> { typedef type64_<T> parent; };
  template<class T> struct ints32_  : type32_<T> { typedef type64_<T> parent; };
  template<class T> struct ints64_  : type64_<T> { typedef type64_<T> parent; };

  template<class T> struct int8_    : ints8_<T>  { typedef ints8_<T>  parent; };
  template<class T> struct int16_   : ints16_<T> { typedef ints16_<T> parent; };
  template<class T> struct int32_   : ints32_<T> { typedef ints32_<T> parent; };
  template<class T> struct int64_   : ints64_<T> { typedef ints64_<T> parent; };
  template<class T> struct uint8_   : ints8_<T>  { typedef ints8_<T>  parent; };
  template<class T> struct uint16_  : ints16_<T> { typedef ints16_<T> parent; };

  template<class T> struct uint32_  : ints32_<T>
  {
    typedef ints32_<T>  parent;
    typedef tag::uint32_ type;
  };

  template<class T> struct uint64_  : ints64_<T> { typedef ints64_<T> parent; };
  template<class T> struct double_  : type64_<T> { typedef type64_<T> parent; };
  template<class T> struct float_   : type32_<T> { typedef type32_<T> parent; };

  template<class T> struct bool_    : fundamental_<T> { typedef fundamental_<T> parent; };
} }

typedef nt2::functors::complement_ cmp;

template<class Sig> struct call_ {};

#define M0(z,n,t) nt2::meta::BOOST_PP_SEQ_ELEM(n,t) const&
#define M1(z,n,t) typename nt2::meta::BOOST_PP_SEQ_ELEM(n,t)::type

#define NT2_REGISTER_DISPATCH(Tag,Seq)                              \
template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(Seq),class A)>      \
call_<Tag(BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),M1,Seq))>            \
dispatch(Tag const&, BOOST_PP_ENUM(BOOST_PP_SEQ_SIZE(Seq),M0,Seq) ) \
/**/

template<class Tag,class A0>
call_<Tag(nt2::tag::unknown_)>
dispatch(Tag const&, nt2::meta::unknown_<A0> const& );

template<class Tag,class A0,class A1>
call_<Tag(nt2::tag::unknown_,nt2::tag::unknown_)>
dispatch(Tag const&, nt2::meta::unknown_<A0> const& , nt2::meta::unknown_<A1> const& );

NT2_REGISTER_DISPATCH(cmp, (uint32_<A0>)(real_<A1>) );
NT2_REGISTER_DISPATCH(cmp, (real_<A0>) );
//NT2_REGISTER_DISPATCH(cmp, (signed_<A0>) );
NT2_REGISTER_DISPATCH(cmp, (unsigned_<A0>) );

namespace nt2 { namespace meta
{
  template<class T> struct base_hierarchy { typedef unknown_<T> type; };

  template<> struct base_hierarchy<char> { typedef int8_<char> type; };
  template<> struct base_hierarchy<short> { typedef int16_<short> type; };
  template<> struct base_hierarchy<int> { typedef int32_<int> type; };
  template<> struct base_hierarchy<long long int> { typedef int64_<long long int> type; };
  template<> struct base_hierarchy<unsigned char> { typedef uint8_<unsigned char> type; };
  template<> struct base_hierarchy<unsigned short> { typedef uint16_<unsigned short> type; };
  template<> struct base_hierarchy<unsigned int> { typedef uint32_<unsigned int> type; };
  template<> struct base_hierarchy<unsigned long long int> { typedef uint64_<unsigned long long int> type; };
  template<> struct base_hierarchy<float> { typedef float_<float> type; };
  template<> struct base_hierarchy<double> { typedef double_<double> type; };
  template<> struct base_hierarchy<bool> { typedef bool_<double> type; };
} }

#define NT2_REGISTER_HIERARCHY(Name)                                \
namespace nt2                                                       \
{                                                                   \
  namespace tag { struct Name {}; }                                 \
  namespace meta                                                    \
  {                                                                 \
    template<class T> struct Name : Name< typename T::parent >      \
    {                                                               \
      typedef Name< typename T::parent > parent;                    \
      typedef tag::Name type(typename T::type);                     \
    };                                                              \
    template<class T> struct Name< nt2::meta::fundamental_<T> > {}; \
  }                                                                 \
}                                                                   \
/**/

NT2_REGISTER_HIERARCHY(vector_)

namespace nt2 { namespace meta
{
  template<class T, class A>
  struct base_hierarchy< std::vector<T,A> >
  {
    typedef vector_<typename base_hierarchy<T>::type > type;
  };
} }

struct foo { double t[10]; };

template<class T> foo
dispatch( nt2::meta::vector_< nt2::meta::double_<T> > const&);

template<class T> double
dispatch( nt2::meta::vector_< nt2::meta::signed_<T> > const&);

namespace nt2 { namespace meta
{
  template<class Sig> struct dispatch_call;

  template<class Tag, class A0>
  struct dispatch_call<Tag(A0)>
  {
    typedef typename nt2::meta::strip<A0>::type               arg0_t;
    typedef typename nt2::meta::base_hierarchy<arg0_t>::type  hierarchy0_t;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( nested
                                    , dispatch( Tag()
                                              , hierarchy0_t()
                                              )
                                    )
    typedef typename nested::type                             type;
  };

  template<class Tag, class A0, class A1>
  struct dispatch_call<Tag(A0,A1)>
  {
    typedef typename nt2::meta::strip<A0>::type               arg0_t;
    typedef typename nt2::meta::strip<A1>::type               arg1_t;
    typedef typename nt2::meta::base_hierarchy<arg0_t>::type  hierarchy0_t;
    typedef typename nt2::meta::base_hierarchy<arg1_t>::type  hierarchy1_t;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( nested
                                    , dispatch( Tag()
                                              , hierarchy0_t()
                                              , hierarchy1_t()
                                              )
                                    )
    typedef typename nested::type                             type;
  };
} }

int main()
{
  cout
  << nt2::type_id<nt2::meta::dispatch_call<cmp(char)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(short)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(int)>::type>() << "\n\n";
  cout
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned char)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned short)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned int)>::type>() << "\n\n";
  cout
  << nt2::type_id<nt2::meta::dispatch_call<cmp(float)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(double)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned int,double)>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(double,double)>::type>() << "\n";
}

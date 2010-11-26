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
  struct scalar_  {};
  struct simd_    {};
} }

// new files
#include <nt2/sdk/functor/forward.hpp>
#include <nt2/sdk/functor/details/call.hpp>
#include <nt2/sdk/functor/details/dispatch.hpp>
#include <nt2/sdk/functor/meta/hierarchy.hpp>
#include <nt2/sdk/functor/meta/hierarchy_of.hpp>

typedef nt2::functors::complement_ cmp;


NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (uint32_<A0>)(real_<A1>) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (real_<A0>) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (unsigned_<A0>) );
////////////////////////////////////////////////////////////////////////////////
// Local macro to generate the dispatch selector
////////////////////////////////////////////////////////////////////////////////
#define M0(z,n,t) BOOST_PP_CAT(elem,n)()
/**/

#define NT2_DISPATCH_TYPES(z,n,t)                                               \
typedef typename strip<BOOST_PP_CAT(A,n)>::type BOOST_PP_CAT(arg,n);            \
typedef typename hierarchy_of<BOOST_PP_CAT(arg,n)>::type  BOOST_PP_CAT(elem,n); \
/**/

#define NT2_DISPATCH_CALL(z,n,t)                                                    \
template<class Tag, BOOST_PP_ENUM_PARAMS(n,class A), class Site>                    \
struct dispatch_call<Tag(BOOST_PP_ENUM_PARAMS(n,A)), Site>                          \
{                                                                                   \
  BOOST_PP_REPEAT(n,NT2_DISPATCH_TYPES,~)                                           \
  BOOST_TYPEOF_NESTED_TYPEDEF_TPL ( nested                                          \
                                  , details::                                       \
                                    dispatch( Tag(), Site(), BOOST_PP_ENUM(n,M0,~)) \
                                  )                                                 \
  typedef typename nested::type                             type;                   \
};                                                                                  \
/**/

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // dispatch_call finds the proper call overload for evaluating a given
  // functor over a set of types on a given site
  //////////////////////////////////////////////////////////////////////////////
  template<class Sig, class Site> struct dispatch_call;
  BOOST_PP_REPEAT_FROM_TO(1,4,NT2_DISPATCH_CALL,~)
} }

#undef M0
#undef NT2_DISPATCH_TYPES
#undef NT2_DISPATCH_CALL



NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (signed_<A0>) );
//NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (real_<A0>)(real_<A1>)  );

NT2_REGISTER_HIERARCHY(vector_)

namespace nt2 { namespace meta
{
  template<class T, class A>
  struct hierarchy_of< std::vector<T,A> >
  {
    typedef vector_<typename hierarchy_of<T>::type > type;
  };
} }

NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (vector_< nt2::meta::integer_<A0> >) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (vector_< nt2::meta::real_<A0> >) );


int main()
{
  cout
//  << nt2::type_id<nt2::meta::dispatch_call<cmp(std::vector<short>), nt2::tag::scalar_>::type>() << "\n"
//  << nt2::type_id<nt2::meta::dispatch_call<cmp(std::vector<float>), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(char), nt2::tag::scalar_>::type>() << "\n"
  /*<< nt2::type_id<nt2::meta::dispatch_call<cmp(short), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(int), nt2::tag::scalar_>::type>() << "\n\n";
  cout
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned char), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned short), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned int), nt2::tag::scalar_>::type>() << "\n\n";
  cout
  << nt2::type_id<nt2::meta::dispatch_call<cmp(float), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(double), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(unsigned int,double), nt2::tag::scalar_>::type>() << "\n"
  /*<< nt2::type_id<nt2::meta::dispatch_call<cmp(double,double), nt2::tag::scalar_>::type>() << "\n"*/;
}

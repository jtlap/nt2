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
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (unsigned_<A0>) )
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
  << nt2::type_id<nt2::meta::dispatch_call<cmp(char), nt2::tag::scalar_>::type>() << "\n"
  /*<< nt2::type_id<nt2::meta::dispatch_call<cmp(short), nt2::tag::scalar_>::type>() << "\n"
    << nt2::type_id<nt2::meta::dispatch_call<cmp(std::vector<short>), nt2::tag::scalar_>::type>() << "\n"
    << nt2::type_id<nt2::meta::dispatch_call<cmp(std::vector<float>), nt2::tag::scalar_>::type>() << "\n"
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

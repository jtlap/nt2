#include <iostream>
#include <vector>

//#include <nt2/sdk/meta/strip.hpp>

using namespace std;

namespace nt2 { namespace tag
{
  struct scalar_  {};
  struct simd_    {};
} }

// new files
#include <nt2/sdk/functor/forward.hpp>
#include <nt2/sdk/functor/details/call.hpp>
#include <nt2/sdk/functor/meta/hierarchy.hpp>
#include <nt2/sdk/functor/details/dispatch.hpp>
#include <nt2/sdk/functor/meta/hierarchy_of.hpp>

// test
#include <nt2/sdk/functor/details/tags.hpp>
#include <nt2/sdk/details/type_id.hpp>

typedef nt2::functors::complement_ cmp;

NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0)(A1), (uint32_<A0>)(real_<A1>) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0), (real_<A0>) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0), (unsigned_<A0>) )
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0), (signed_<A0>) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0), (real_<A0>)(real_<A0>)  );

NT2_REGISTER_HIERARCHY(vector_)

namespace nt2 { namespace meta
{
  template<class T, class A>
  struct hierarchy_of< std::vector<T,A> >
  {
    typedef vector_<typename hierarchy_of<T>::type > type;
  };
} }

NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0), (vector_< nt2::meta::integer_<A0> >) );
NT2_REGISTER_DISPATCH(cmp, tag::scalar_, (A0), (vector_< nt2::meta::real_<A0> >) );

int main()
{
  cout
  << nt2::type_id<nt2::meta::dispatch_call<cmp(char), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(short), nt2::tag::scalar_>::type>() << "\n"
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
  << nt2::type_id<nt2::meta::dispatch_call<cmp(float,float), nt2::tag::scalar_>::type>() << "\n"
  << nt2::type_id<nt2::meta::dispatch_call<cmp(double,double), nt2::tag::scalar_>::type>() << "\n"
;//  << nt2::type_id<nt2::meta::dispatch_call<cmp(double,float), nt2::tag::scalar_>::type>() << "\n";
}

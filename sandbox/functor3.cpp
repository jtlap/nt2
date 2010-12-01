#include <iostream>
#include <vector>

//#include <nt2/sdk/meta/strip.hpp>

using namespace std;

namespace nt2 { namespace tag
{
  struct cpu_  {};
} }

// new files
#include <nt2/sdk/functor/functor.hpp>

// test
#include <nt2/sdk/functor/details/tags.hpp>
#include <nt2/sdk/details/type_id.hpp>

typedef nt2::tag::complement_ cmp;
#include <nt2/sdk/functor/preprocessor/function.hpp>

NT2_FUNCTION_IMPLEMENTATION(cmp,ffff,2)
NT2_FUNCTION_IMPLEMENTATION(cmp,ffff,1)

NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0)(A1), (uint32_<A0>)(real_<A1>) );
NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0), (real_<A0>) );
NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0), (unsigned_<A0>) )
NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0), (signed_<A0>) );
NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0), (real_<A0>)(real_<A0>)  );

NT2_REGISTER_HIERARCHY(vector_)

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::complement_(tag::real_),tag::cpu_,Dummy> : callable
  {
    typedef float result_type;

    template<class A0> inline
    result_type operator()(A0 const& a0) const
    {
      return 3.1415*a0;
    }
  };

  template<class Dummy>
  struct call<tag::complement_(tag::real_,tag::real_),tag::cpu_,Dummy> : callable
  {
    typedef float result_type;

    template<class A0, class A1> inline
    result_type operator()(A0 const& a0,A1 const& a1) const
    {
      return a1*a0;
    }
  };

  template<class Dummy>
  struct call<tag::complement_(tag::signed_),tag::cpu_,Dummy> : callable
  {
    typedef float result_type;

    template<class A0> inline
    result_type operator()(A0 const& a0) const
    {
      return -a0;
    }
  };

  template<class Dummy>
  struct call<tag::complement_(tag::vector_(tag::real_)),tag::cpu_,Dummy> : callable
  {
    typedef float result_type;

    template<class A0> inline
    result_type operator()(A0 const& a0) const
    {
      return a0.size();
    }
  };
} }

namespace nt2 { namespace meta
{
  template<class T, class A>
  struct hierarchy_of< std::vector<T,A> >
  {
    typedef vector_<typename hierarchy_of<T>::type > type;
  };
} }

NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0), (vector_< nt2::meta::integer_<A0> >) );
NT2_REGISTER_DISPATCH(cmp, tag::cpu_, (A0), (vector_< nt2::meta::real_<A0> >) );

int main()
{
  std::vector<float> k(1337);

  cout << ffff('A') << "\n";
  cout << ffff(1000.) << "\n";
  cout << ffff(k) << "\n";
  cout << ffff(1000.f,0.001f) << "\n";
}

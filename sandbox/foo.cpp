#include <iostream>
#include <nt2/sdk/simd/native.hpp>

using namespace std;
using namespace nt2;
using namespace nt2::simd;


#define M0(z,n,t)
NT2_REGISTER_DISPATCH ( Tag , tag::cpu_, (Tag)(X)
                      , ((simd_< arithmetic_<A0>, X >))
                        ((simd_< arithmetic_<A0>, X >))
                      )

NT2_REGISTER_DISPATCH ( tag::plus_       , tag::cpu_, (A0)
                      , ((simd_< arithmetic_<A0>, tag::sse_ >))
                        ((simd_< arithmetic_<A0>, tag::sse_ >))
                      )

namespace nt2 { namespace ext
{
  template<class Tag, class X, class Dummy>
  struct  call<Tag( tag::simd_(tag::arithmetic_,X)
                , tag::simd_(tag::arithmetic_,X)
                ), tag::cpu_, Dummy>
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>  struct
    result<This(A0,A1)> : meta::strip<A0>  {};

    NT2_FUNCTOR_CALL(2) { puts("COMMON"); return a0; }
  };

// template<class Dummy>
//  struct  call<tag::plus_ ( tag::simd_(tag::arithmetic_,tag::sse_)
//                          , tag::simd_(tag::arithmetic_,tag::sse_)
//                          ), tag::cpu_, Dummy>
//        : callable
//  {
//    template<class Sig> struct result;
//    template<class This,class A0, class A1>  struct
//    result<This(A0,A1)> : meta::strip<A0>  {};
//
//    NT2_FUNCTOR_CALL(2) { puts("SSE 2"); return a0; }
//  };

} }

int main()
{
   native<float,tag::sse_> x,y;

   x = nt2::add(y,y);

}

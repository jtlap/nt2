//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSSE3_LOOKUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSSE3_LOOKUP_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shli.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0)(A1),
                         ((simd_<type8_<A0>,tag::sse_>))
                         ((simd_<ints8_<A1>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_<tag::type8_, tag::sse_> ,
                           tag::simd_<tag::ints8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
      {
      return simd::native_cast<A0>(_mm_shuffle_epi8(a0, a1));
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0)(A1),
                         ((simd_<type32_<A0>,tag::sse_>))
                         ((simd_<ints32_<A1>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_<tag::type32_, tag::sse_> ,
                           tag::simd_<tag::ints32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
      {
      typedef typename simd::native<int8_t, tag::sse_> type8;
        const type8 inc = {{0x302010003020100LL,0x302010003020100LL}};
        const type8 dup = {{0x404040400000000LL,0xc0c0c0c08080808LL}};
        type8 i1 = {_mm_shuffle_epi8(shli(a1, 2), dup)};
        type8  r  = {_mm_shuffle_epi8(simd::native_cast<type8>(a0), i1+inc )};
        return simd::native_cast<A0>(r);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
		      (A0)(A1),
                         ((simd_<type64_<A0>,tag::sse_>))
                         ((simd_<ints64_<A1>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_<tag::type64_, tag::sse_> ,
                           tag::simd_<tag::ints64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
      {
      typedef typename simd::native<int8_t, tag::sse_> type8;
//    const v128_int8_t inc(0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7 );
//    const v128_int8_t dup(0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8 );
      const type8 inc = {{506097522914230528ll,506097522914230528ll}};
      const type8 dup = {{0ll,578721382704613384ll}};
      const type8 i1 =  {_mm_shuffle_epi8(shli(a1, 3), dup)};
      const type8 r  =  {_mm_shuffle_epi8(simd::native_cast<type8>(a0), i1+inc)};
      return simd::native_cast<A0>(r);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::lookup_, tag::cpu_,
                         (A0)(A1),
                         ((simd_<type16_<A0>,tag::sse_>))
                         ((simd_<ints16_<A1>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::lookup_(tag::simd_<tag::type16_, tag::sse_> ,
                           tag::simd_<tag::ints16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
      {
      typedef typename simd::native<int8_t, tag::sse_> type8;
//    const type8 inc(0,1,0,1,0,1,0,1,0,1,1,0,1,0,1,0,1);
//    const type8 dup(0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14);
      const type8 inc = {{72058693566333184ll,72058693566333184ll}};
      const type8 dup = {{434038829347897344ll,1012760212052510728ll}};
      const type8 i1 = {_mm_shuffle_epi8(shli(a1, 1), dup)};
      const type8 r =  {_mm_shuffle_epi8(simd::native_cast<type8>(a0), plus(i1, inc))};//add increment
      return simd::native_cast<A0>(r);
      }
  };
} }

#endif
// modified by jt the 05/01/2011

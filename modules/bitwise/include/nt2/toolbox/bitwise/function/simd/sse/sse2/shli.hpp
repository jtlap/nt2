//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHLI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHLI_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                       (A0)(A1),
                       ((simd_<type8_<A0>,tag::sse_>))
                       ((integer_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::simd_<tag::type8_, tag::sse_>,
                         tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type result_type;
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_> gen_type;
      result_type const Mask1 =  simd::native_cast<result_type>(integral_constant<gen_type, 0x00ff00ff00ff00ffll>());
      result_type const Mask2 =  simd::native_cast<result_type>(integral_constant<gen_type, 0xff00ff00ff00ff00ll>());
      result_type tmp  = b_and(a0, Mask1);
      result_type tmp1 = {_mm_slli_epi16(tmp, a1)};
      tmp1 = b_and(tmp1, Mask1);
      tmp = b_and(a0, Mask2);
      result_type tmp3 = {_mm_slli_epi16(tmp, a1)};
      result_type tmp2 = b_and(tmp3, Mask2);
      return tmp1 | tmp2;	
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                       (A0)(A1),
                       ((simd_<type32_<A0>,tag::sse_>))
                       ((integer_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::simd_<tag::type32_, tag::sse_>,
                         tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename meta::as_integer<A0,signed>::type sint;
      sint const that = { _mm_slli_epi32(simd::native_cast<sint>(a0),a1)};
            return simd::native_cast<A0>(that);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                       (A0)(A1),
                       ((simd_<type64_<A0>,tag::sse_>))
                       ((integer_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::simd_<tag::type64_, tag::sse_>,
                         tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename meta::as_integer<A0,signed>::type sint;
        sint const that ={ _mm_slli_epi64(simd::native_cast<sint>(a0), a1)};
        return simd::native_cast<A0>(that);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                       (A0)(A1),
                       ((simd_<type16_<A0>,tag::sse_>))
                       ((integer_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::simd_<tag::type16_, tag::sse_>,
                         tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = {_mm_slli_epi16(a0, a1)};
      return that;
    }
  };
} }

#endif
// modified by jt the 04/01/2011
// modified manually jt the 05/01/2011    

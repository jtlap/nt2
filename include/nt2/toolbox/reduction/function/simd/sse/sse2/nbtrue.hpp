//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/popcnt.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nbtrue_, tag::cpu_,
                         (A0),
                         ((simd_<arithmetic_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nbtrue_(tag::simd_<tag::arithmetic_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    typedef int32_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename simd::native<typename meta::int8_t_<A0>::type,tag::sse_> i8type;
      i8type tmp = {is_nez(a0)};
      return nt2::popcnt(_mm_movemask_epi8(tmp))*meta::cardinal_of<A0>::value >> 4;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nbtrue_, tag::cpu_,
                         (A0),
                         ((simd_<double_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nbtrue_(tag::simd_<tag::double_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    typedef int32_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      int32_t  r = _mm_movemask_pd(is_nez(a0));
      return   (r&1)+(r>>1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nbtrue_, tag::cpu_,
                         (A0),
                         ((simd_<float_<A0>,tag::sse_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::nbtrue_(tag::simd_<tag::float_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    typedef int32_t result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type type;
      int32_t  r = _mm_movemask_ps(is_nez(a0));
      return   (r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3);
      //      return nt2::popcnt(_mm_movemask_ps(is_nez(cast<type>(a0))));
    }
  };
} }

#endif
// modified by jt the 05/01/2011
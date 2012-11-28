//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOG1P_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_LOG1P_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/log1p.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/seladd.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0 > ::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      log(oneplus(tofloat(a0)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::log1p_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      result_type u = oneplus(a0);
      return if_else(eq(u, Inf<A0>()),
                     u, if_else(lt(nt2::abs(a0), Eps<result_type>()),
                                a0,
                                seladd(is_nez(u),
                                       log(u),
                                       -((u-One<A0>())-a0)/u)
                                )
                     );
      // cancels errors with IEEE arithmetic
    }
  };
} }




#endif

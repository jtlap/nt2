//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_NTHROOT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_NTHROOT_HPP_INCLUDED

#include <nt2/exponential/functions/nthroot.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nthroot_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<integer_<A0>,X>))
                              ((simd_<integer_<A1>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::nthroot(nt2::tofloat(a0), a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::nthroot_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<integer_<A1>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_logical<A0>::type  bA0;
      typedef typename meta::as_logical<A1>::type  bA1;
      A0 x =  nt2::abs(a0);
      A0 aa1 = nt2::tofloat(a1);
      A0 y =nt2::pow(x,rec(aa1));
      bA1 nul_a1 = nt2::is_eqz(a1);
      A0 a11 = nt2::tofloat(a1-nt2::if_else_zero(nul_a1, Mone<A1>()));
      y = nt2::seladd( nt2::logical_or(nt2::is_nez(y), nul_a1)
                     , y
                     , -(nt2::pow(y, aa1) - x)/(aa1* nt2::pow(y, nt2::minusone(a11)))
                     );

      // Correct numerical errors (since, e.g., 64^(1/3) is not exactly 4)
      // by one iteration of Newton's method
      bA0 invalid = nt2::logical_and(nt2::logical_and(is_ltz(a0), nt2::is_even(a1)), nt2::is_nez(a1));
      return nt2::if_zero_else(
        nt2::is_eqz(a0),
        nt2::if_nan_else(
          invalid,
          nt2::if_else(
            nt2::is_eqz(aa1),
            nt2::One<A0>(),
            nt2::if_else(
              l_or(eq(a1, nt2::One<A1>()), nt2::is_inf(a0)),
              a0,
              nt2::bitwise_or(y, nt2::bitofsign(a0))
            )
          )
        )
      );
    }
  };
} }

#endif

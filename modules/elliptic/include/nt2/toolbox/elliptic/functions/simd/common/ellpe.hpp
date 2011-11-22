//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLPE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLPE_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellpe_, tag::cpu_,
                        (A0)(X),
                        ((simd_<arithmetic_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef result_type type;
      return nt2::ellpe(tofloat(a0));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellpe_, tag::cpu_,
                        (A0)(X),
                        ((simd_<double_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      return map(functor<tag::ellpe_>(), a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellpe_, tag::cpu_,
                        (A0)(X),
                        ((simd_<single_<A0>,X>))
                       )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 temp = horner< NT2_HORNER_COEFF_T(sA0, 11,
                               (0x392102f5,
                                0x3b246c1b,
                                0x3c0e578f,
                                0x3c2fe240,
                                0x3bfebca9,
                                0x3bf882cf,
                                0x3c3d8b3f,
                                0x3cb2d89a,
                                0x3d68ac90,
                                0x3ee2e430,
                                0x3f800000) ) > (a0)
      -log(a0)*a0*horner< NT2_HORNER_COEFF_T(sA0, 10,
                                 (0x38098de4,
                                  0x3a84557e,
                                  0x3bd53114,
                                  0x3c8a54f6,
                                  0x3cd67118,
                                  0x3d0925e1,
                                  0x3d2ef92b,
                                  0x3d6fffe9,
                                  0x3dc00000,
                                  0x3e800000
                                  ) ) > (a0);
      return select(is_eqz(a0),
                One<A0>(),
                if_nan_else(b_or(gt(a0, One<A0>()), is_ltz(a0)), temp));
    }
  };
} }
#endif

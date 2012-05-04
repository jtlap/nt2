//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLINT_2_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLINT_2_HPP_INCLUDED
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/toolbox/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/toolbox/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::ellint_2(tofloat(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return map(functor<tag::ellint_2_>(), a0);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_2_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return map(functor<tag::ellint_2_>(), a0);
      // broken TO DO      
//       typedef typename meta::scalar_of<A0>::type sA0;
//       A0 x = nt2::abs(a0);
//       const A0 a = nt2::sqrt(oneminus(x));
//       const A0 z = horner< NT2_HORNER_COEFF_T(sA0, 11,
//                               (0x392102f5,
//                                0x3b246c1b,
//                                0x3c0e578f,
//                                0x3c2fe240,
//                                0x3bfebca9,
//                                0x3bf882cf,
//                                0x3c3d8b3f,
//                                0x3cb2d89a,
//                                0x3d68ac90,
//                                0x3ee2e430,
//                                0x3f800000) ) > (a)
//                 -nt2::log(a)*a*horner< NT2_HORNER_COEFF_T(sA0, 10,
//                                     (0x38098de4,
//                                      0x3a84557e,
//                                      0x3bd53114,
//                                      0x3c8a54f6,
//                                      0x3cd67118,
//                                      0x3d0925e1,
//                                      0x3d2ef92b,
//                                      0x3d6fffe9,
//                                      0x3dc00000,
//                                      0x3e800000
//                                      ) ) > (a);
//       return gt(x,One<A0>())|z;
     }
  };
} }


#endif

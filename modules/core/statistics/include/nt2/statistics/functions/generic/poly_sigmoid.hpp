//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_POLY_SIGMOID_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_POLY_SIGMOID_HPP_INCLUDED
#include <nt2/statistics/functions/poly_sigmoid.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/constants/quarter.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <boost/simd/sdk/math.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( poly_sigmoid_, tag::cpu_
                              , (A0)
                              , (generic_< single_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      A0 x = abs(a0);
      A0 z = horner< NT2_HORNER_COEFF_T(stype, 7,
                                        (0x30c78a28, // 1.451842196551088e-09
                                         0x36e5e147, // 6.850957538119073e-06
                                         0xb9bc6a48, // -3.593733872799021e-04
                                         0x3bea4bea, // 7.150163116231881e-03
                                         0xbd89d648, // -6.730323710481008e-02
                                         0x3e992cd8, // 2.991702637377551e-01
                                         0x3efd215d, // 4.943951644544352e-01
                                         0x34209587
                                        ) ) > (x);
      z =  if_else(ge(x, One<A0>()), One<A0>(), z);
      return if_else(is_lez(a0), oneminus(z), z);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( poly_sigmoid_, tag::cpu_
                              , (A0)
                              , (generic_< double_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      A0 x = abs(a0);
      A0 z = horner< NT2_HORNER_COEFF_T(stype, 7,
                                        (0x3e8412b0ed1f5556ll, // 1.451842196551088e-09
                                         0x3eabc642f1141980ll, // 6.850957538119073e-06
                                         0xbf31ba7f9adb17ebll, // -3.593733872799021e-04
                                         0x3f7aeb116a917e92ll, // 7.150163116231881e-03
                                         0xbfb0d1869948d422ll, // -6.730323710481008e-02
                                         0x3fd30cbb031bd190ll, // 2.991702637377551e-01
                                         0x3fdfa7ba3772fd17ll  // 4.943951644544352e-01
                                        ) ) > (x);
      z =  if_else(ge(x, One<A0>()), One<A0>(), z);
      return if_else(is_lez(a0), oneminus(z), z);
    }
  };
} }

#endif


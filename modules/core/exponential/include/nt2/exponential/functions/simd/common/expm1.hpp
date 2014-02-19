//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPM1_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_EXPM1_HPP_INCLUDED

#include <nt2/exponential/functions/expm1.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/twenty.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/fast_ldexp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_not_equal.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0>::type int_type;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 k =  round2even(double_constant<A0, 0x3ff71547652b82fell>()*a0);
      int_type ki =  toint(-k);
      A0 hi = a0 - k* double_constant<A0, 0x3fe62e42fee00000ll>(); //ln2HI;
      A0 lo = k*double_constant<A0, 0x3dea39ef35793c76ll>(); //ln2LO;
      A0 x = hi-lo;
      A0 hxs = sqr(x)*Half<A0>();
      A0 r1 = One<A0>()+hxs*horner <NT2_HORNER_COEFF_T(sA0, 5,
                                                       (0xBE8AFDB76E09C32Dll,
                                                        0x3ED0CFCA86E65239ll,
                                                        0xBF14CE199EAADBB7ll,
                                                        0x3F5A01A019FE5585ll,
                                                        0xBFA11111111110F4ll)
                                                      )> (hxs);
      A0 t  = Three<A0>()-r1*Half<A0>()*x;
      A0 e  = hxs*((r1-t)/(Six<A0>() - x*t));
      A0 c = (hi-x)-lo;
      e  = (x*(e-c)-c)-hxs;

      A0 two2mk = fast_ldexp(One<A0>(), ki);
      A0 ct1= oneminus(two2mk)-(e-x);
      A0 ct2= oneplus((x-(e+two2mk)));

      A0 y = if_else(lt(k, Twenty<A0>()),ct1,ct2);
      y =  fast_ldexp(y, toint(k));
      #ifndef BOOST_SIMD_NO_INFINITIES
      return if_else(eq(a0, Minf<A0>()),Mone<A0>(),
                     if_else(eq(a0, Inf<A0>()), a0, y)
                    );
      #else
      return y;
      #endif
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expm1_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      const A0 u =  exp(a0);
      const bA0 p = logical_or(is_eqz(u),is_inf(u));
      const A0 y1 = minusone(u);
      const bA0 m = logical_and(logical_not(p), is_not_equal(u, One<A0>()));
      const A0 y2 = y1*(a0/nt2::log(u));
      return if_else(p,y1,if_else(m, y2, a0));
    }
  };
} }

#endif

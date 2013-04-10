//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_SPENCE_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTIONS_SIMD_COMMON_SPENCE_HPP_INCLUDED

#include <nt2/toolbox/euler/functions/spence.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/polevl.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/six.hpp>



namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::spence(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::spence_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      static boost::array<sA0, 8> A = {{
        sA0(4.65128586073990045278E-5),
        sA0(7.31589045238094711071E-3),
        sA0(1.33847639578309018650E-1),
        sA0(8.79691311754530315341E-1),
        sA0(2.71149851196553469920E0),
        sA0(4.25697156008121755724E0),
        sA0(3.29771340985225106936E0),
        sA0(1.00000000000000000126E0),
      }};
      static boost::array<sA0, 8> B = {{
        sA0(6.90990488912553276999E-4),
        sA0(2.54043763932544379113E-2),
        sA0(2.82974860602568089943E-1),
        sA0(1.41172597751831069617E0),
        sA0(3.63800533345137075418E0),
        sA0(5.03278880143316990390E0),
        sA0(3.54771340985225096217E0),
        sA0(9.99999999999999998740E-1),
      }};
      static const A0 C = (nt2::Pi<A0>()*nt2::Pi<A0>())/nt2::Six<A0>();
      A0 x = a0;
      bA0 flag2 =  nt2::gt(x, nt2::Two<A0>());
      x = nt2::if_else(flag2, rec(x), x);
      bA0 flag =  nt2::gt(x,nt2::One<A0>()+nt2::Half<A0>());
      bA0 flag1=  nt2::lt(x,nt2::Half<A0>());
      flag2 = nt2::logical_or(flag2, flag);
      A0 w =  nt2::if_else(flag,
                           nt2::minusone(nt2::rec(x)),
                           nt2::if_else(flag1, -x, nt2::minusone(x)));
      A0 y = -w*nt2::polevl(w,A)/nt2::polevl(w,B);
      y = nt2::if_else(flag1, C -nt2::log(x) * nt2::log(nt2::oneminus(x))-y,y);
      y = nt2::if_else(flag2, nt2::Mhalf<A0>()*nt2::sqr(nt2::log(x))-y,y);
      return nt2::if_else(nt2::is_eqz(a0), C, y);
    }
  };
} }


#endif

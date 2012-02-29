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
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/sdk/simd/logical.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
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
      return spence(tofloat(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
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
      static const A0 C = (Pi<A0>()*Pi<A0>())/Six<A0>();
      A0 x = a0;
      bA0 flag2 =  gt(x, Two<A0>());
      x = sel(flag2, rec(x), x);
      bA0 flag =  gt(x,One<A0>()+Half<A0>());
      bA0 flag1=  lt(x,Half<A0>());
      flag2 = logical_or(flag2, flag);
      A0 w =  sel(flag, minusone(rec(x)), sel(flag1, -x, minusone(x)));
      A0 y = -w*polevl(w,A)/polevl(w,B);
      y = sel(flag1, C -log(x) * log(One<A0>()-x)-y,y);
      y = sel(flag2, Mhalf<A0>()*sqr(log(x))-y,y);
      return sel(is_eqz(a0), C, y);
    }
  };
} }


#endif

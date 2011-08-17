/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_FACTORIAL_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/abss.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/round.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
			     (A0)(X),
                      ((simd_<real_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::round(nt2::gamma(oneplus(nt2::trunc(nt2::abs(a0)))));
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<integer_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
	using boost::simd::bitwise_cast; 
	typedef typename meta::as_real<A0>::type ftype;
	ftype r = nt2::factorial(nt2::tofloat(a0));
	return sel(gt(r,tofloat(Valmax<A0>())), Valmax<A0>(), bitwise_cast<A0>(nt2::toint(r))); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<int32_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  sel(eq(a00, Two<A0>()),     Two<A0>(),  r);
      r =  sel(eq(a00, Three<A0>()),   Six<A0>(), r); 
      r =  sel(eq(a00, Four<A0>()),    Fact_4<A0>(), r); 
      r =  sel(eq(a00, Five<A0>()),    Fact_5<A0>(), r);
      r =  sel(eq(a00, Six<A0>()),     Fact_6<A0>() , r);
      r =  sel(eq(a00, Seven<A0>()),   Fact_7<A0>(), r);
      r =  sel(eq(a00, Eight<A0>()),   Fact_8<A0>() , r); 
      r =  sel(eq(a00, Nine<A0>()),    Fact_9<A0>(), r);
      r =  sel(eq(a00, Ten<A0>()),     Fact_10<A0>(), r);
      r =  sel(eq(a00, Eleven<A0>()),  Fact_11<A0>(), r);
      return sel(ge(a00, Twelve<A0>()), Valmax<A0>(), r);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<int16_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  sel(eq(a00, Two<A0>()), Two<A0>(),  r);
      r =  sel(eq(a00, Three<A0>()), Six<A0>(), r); 
      r =  sel(eq(a00, Four<A0>()), Fact_4<A0>(), r); 
      r =  sel(eq(a00, Five<A0>()), Fact_5<A0>(), r);
      r =  sel(eq(a00, Six<A0>()),  Fact_6<A0>() , r);
      r =  sel(eq(a00, Seven<A0>()),Fact_7<A0>(), r);
      return sel(ge(a00, Eight<A0>()), Valmax<A0>(), r);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<uint16_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  sel(eq(a00, Two<A0>()), Two<A0>(),  r);
      r =  sel(eq(a00, Three<A0>()), Six<A0>(), r); 
      r =  sel(eq(a00, Four<A0>()), Fact_4<A0>(), r); 
      r =  sel(eq(a00, Five<A0>()), Fact_5<A0>(), r);
      r =  sel(eq(a00, Six<A0>()),  Fact_6<A0>() , r);
      r =  sel(eq(a00, Seven<A0>()), Fact_8<A0>(), r);
      r =  sel(eq(a00, Eight<A0>()), Fact_9<A0>() , r); 
      return sel(ge(a00, Nine<A0>()), Valmax<A0>(), r);
    }
  };

    NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type8_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  sel(eq(a00, Two<A0>()), Two<A0>(),  r);
      r =  sel(eq(a00, Three<A0>()), Six<A0>(), r); 
      r =  sel(eq(a00, Four<A0>()), Fact_4<A0>(), r); 
      r =  sel(eq(a00, Five<A0>()), Fact_5<A0>(), r);
      return sel(gt(a00, Five<A0>()), Valmax<A0>(), r);
    }
  };
} }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of factorial.hpp
// /////////////////////////////////////////////////////////////////////////////

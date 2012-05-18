//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLIK_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLIK_HPP_INCLUDED
#include <nt2/toolbox/elliptic/functions/ellik.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/tan.hpp>
#include <nt2/include/functions/simd/ceil.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellik_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ellik(tofloat(a0), tofloat(a1));
    }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellik_, tag::cpu_
			      , (A0)(X)
			      , ((simd_<double_<A0>,X>))((simd_<double_<A0>,X>))
			      )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
      {
	return map(functor<tag::ellik_>(), a0, a1);
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellik_, tag::cpu_
			      , (A0)(X)
			      , ((simd_<single_<A0>,X>))((simd_<single_<A0>,X>))
			      )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
      {
	return map(functor<tag::ellik_>(), a0, a1);
	// broken TO DO
	//       A0 phi = nt2::abs(a0);
	//       A0 m = a1;
	//       A0 a = One<A0>();
	//       A0 b = oneminus(m);
	
	//       b = sqrt(b);
	//       A0 c = sqrt(m);
	//       A0 d = One<A0>();
	//       A0 t = tan(phi);
	//       A0 mod = ceil(phi/Pi<A0>());
	//       while( nt2::any(gt(abs(c), nt2::abs(a)*Eps<A0>())) )
	//       {
	//         A0 temp = b/a;
	//         phi = phi + atan(t*temp) + mod*Pi<A0>();
	//         mod = ceil(phi/Pi<A0>());
	//         t = oneplus(temp)/(rec(t)-temp*t);
	//         c = average(a,-b);
	//         temp = sqrt(a*b);
	//         a = average(a,b);
	//         b = temp;
	//         d += d;
	//       }
	//       A0 temp = (atan(t) + mod * Pi<A0>())/(d * a);
	//       temp = b_xor(temp, bitofsign(a0));
	//       return b_or(b_or(is_ltz(a1), gt(a1, One<A0>())), temp);
      }
  };
} }


#endif

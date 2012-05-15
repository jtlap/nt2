//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_F_LOG_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_LOGS_F_LOG_HPP_INCLUDED

#include <boost/fusion/include/vector_tie.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/bitwise_and.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/fast_frexp.hpp>
#include <nt2/include/functions/simd/genmask.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>


namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0,
		 class Style , 
		 class base_A0 = typename meta::scalar_of<A0>::type> 
      struct logarithm{};
      
      //////////////////////////////////////////////////////////////////////////////
      // math log functions
      //////////////////////////////////////////////////////////////////////////////

      template < class A0 > 
      struct logarithm< A0, tag::not_simd_type, float>
      {
      
	static inline void kernel_log(const A0& a0,
				      A0& fe,
				      A0& x,
				      A0& x2,
				      A0& y)
	{
	  typedef typename meta::as_integer<A0, signed>::type int_type;
	  typedef typename meta::strip<A0>::type stA0; 
	  int_type e;
	  boost::fusion::vector_tie(x, e) = fast_frexp(a0);
	  int_type x_lt_sqrthf = -(single_constant<stA0, 0x3f3504f3>() > x);
	  e += x_lt_sqrthf;
	  //     if (x_lt_sqrthf) x+= x;
	  //     x += single_constant<A0, 0xbf800000>();
	  x += b_and(x, x_lt_sqrthf)+single_constant<stA0,0xbf800000>();
	  x2 = sqr(x);
	  A0 y1 = madd(single_constant<stA0, 0x3d9021bb>() ,x2,single_constant<stA0, 0x3def251a>() );
	  A0 y2 = madd(single_constant<stA0, 0xbdebd1b8>() ,x2,single_constant<stA0, 0xbdfe5d4f>() );
	  y1 = madd(y1,x2,single_constant<stA0, 0x3e11e9bf>() );
	  y2 = madd(y2,x2,single_constant<stA0, 0xbe2aae50>() );
	  y1 = madd(y1,x2,single_constant<stA0, 0x3e4cceac>() );
	  y2 = madd(y2,x2,single_constant<stA0, 0xbe7ffffc>() );
	  y1 = madd(y1,x2,single_constant<stA0, 0x3eaaaaaa>() );
	  y = madd(x,y2,y1)*x*x2;
	  fe = tofloat(e);
	}
	
	static inline A0 log(const A0& a0)
	{
	  typedef typename meta::strip<A0>::type stA0; 
	  if (a0 == Inf<stA0>()) return a0;
	  if (is_eqz(a0)) return Minf<stA0>();
	  if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<stA0>();
	  A0 x, fe, x2, y;
	  kernel_log(a0, fe, x, x2, y);
	  y = madd(fe, single_constant<stA0, 0xb95e8083>(), y);
	  y = madd(Mhalf<stA0>(), x2, y);
	  A0 z  = x + y;
	  return madd(single_constant<stA0, 0x3f318000>(), fe, z);
	}
	
	static inline A0 log2(const A0& a0)
	{
	  typedef typename meta::strip<A0>::type stA0; 
	  if (a0 == Inf<stA0>()) return a0;
	  if (is_eqz(a0)) return Minf<stA0>();
	  if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<stA0>();
	  A0 x, fe, x2, y;
	  kernel_log(a0, fe, x, x2, y);
	  y =  madd(Mhalf<stA0>(),x2, y);
	  // multiply log of fraction by log2(e)
	  A0 z = madd( x
		       , single_constant<stA0, 0x3ee2a8ed>()
		       , mul(y,single_constant<stA0, 0x3ee2a8ed>())// 0.44269504088896340735992
		       );
	  return ((z+y)+x)+fe;
	}
	
	static inline A0 log10(const A0& a0)
	{
	  typedef typename meta::strip<A0>::type stA0; 
	  if (a0 == Inf<stA0>()) return a0;
	  if (is_eqz(a0)) return Minf<stA0>();
	  if (nt2::is_nan(a0)||is_ltz(a0)) return Nan<stA0>();
	  A0 x, fe, x2, y;
	  kernel_log(a0, fe, x, x2, y);
	  y =  amul(y, Mhalf<stA0>(), x2);
	  // multiply log of fraction by log10(e) and base 2 exponent by log10(2)
	  A0 z = mul(x+y, single_constant<stA0, 0x3a37b152>());//7.00731903251827651129E-4f // log10(e)lo
	  z = amul(z, y, single_constant<stA0, 0x3ede0000>()); //4.3359375E-1f	       // log10(e)hi
	  z = amul(z, x, single_constant<stA0, 0x3ede0000>());
	  z = amul(z, fe, single_constant<stA0, 0x39826a14>());//3.0078125E-1f              // log10(2)hi
	  return amul(z, fe, single_constant<stA0, 0x3e9a0000 >());//2.48745663981195213739E-4f // log10(2)lo
	}
      }; 
    }
  }
}


#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_IMPL_LOGS_F_LOG_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_IMPL_LOGS_F_LOG_HPP_INCLUDED
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/fast_frexp.hpp>
#include <nt2/include/functions/genmask.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/amul.hpp>
#include <nt2/include/functions/madd.hpp>
#include <nt2/sdk/constant/digits.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      //////////////////////////////////////////////////////////////////////////////
      // math log functions
      //////////////////////////////////////////////////////////////////////////////

      template < class A0 >
      struct logarithm< A0, tag::simd_type, float>
      {
	static inline void kernel_log(const A0& a0,
				      A0& fe,
				      A0& x,
				      A0& x2,
				      A0& y)
	{
	  typedef typename meta::as_integer<A0, signed>::type int_type;
	  int_type e;
	  boost::fusion::tie(x, e) = fast_frexp(a0);
	  // 	std::cout << "x " << x << " e " << e << std::endl;
	  // 	bf::tie(x, e) = frexp(a0);
	  // 	std::cout << "x " << x << " e " << e << std::endl;
	  int_type x_lt_sqrthf = simd::native_cast<int_type>(gt(single_constant<A0, 0x3f3504f3>(),x));
	  e = e+x_lt_sqrthf;
	  x = x+b_and(x, x_lt_sqrthf)+single_constant<A0, 0xbf800000>();
	  x2 = sqr(x);
	  A0 y1 = madd(single_constant<A0, 0x3d9021bb>() ,x2,single_constant<A0, 0x3def251a>() );
	  A0 y2 = madd(single_constant<A0, 0xbdebd1b8>() ,x2,single_constant<A0, 0xbdfe5d4f>() );
	  y1 = madd(y1,x2,single_constant<A0, 0x3e11e9bf>() );
	  y2 = madd(y2,x2,single_constant<A0, 0xbe2aae50>() );
	  y1 = madd(y1,x2,single_constant<A0, 0x3e4cceac>() );
	  y2 = madd(y2,x2,single_constant<A0, 0xbe7ffffc>() );
	  y1 = madd(y1,x2,single_constant<A0, 0x3eaaaaaa>() );
	  y = madd(x,y2,y1)*x*x2;
	  fe = tofloat(e);
	}

	static inline A0 log(const A0& a0)
	{
	  A0 x, fe, x2, y;
	  kernel_log(a0, fe, x, x2, y);
	  y = madd(fe, single_constant<A0, 0xb95e8083>(), y);
	  y = madd(Mhalf<A0>(), x2, y);
	  A0 z  = x + y;
	  // 	std::cout << "fe " << fe << std::endl;
	  // 	std::cout << "z  " << z << std::endl;
	  // 	std::cout << "a0 " << a0 << std::endl;
	  // 	std::cout << "rec(a0) " << rec(a0) << std::endl;
	  A0 y1 = a0-rec(abs(a0));// trick to reduce selection testing
	  A0 y2 = madd(single_constant<A0, 0x3f318000>(), fe, z);
	  // 	std::cout << "y1 " << y1 << std::endl;
	  // 	std::cout << "y2 " << y2 << std::endl;
	  return seladd(is_inf(y1),b_or(y2, b_or(is_ltz(a0), is_nan(a0))),y1);
	}

	static inline A0 log2(const A0& a0)
	{
	  A0 x, fe, x2, y;
	  kernel_log(a0, fe, x, x2, y);
	  y =  madd(Mhalf<A0>(),x2, y);
	  // multiply log of fraction by log2(e)
	  A0 z = madd(x,single_constant<A0, 0x3ee2a8ed>(),mul(y,single_constant<A0, 0x3ee2a8ed>()));// 0.44269504088896340735992
	  A0 z1 = ((z+y)+x)+fe;
	  A0 y1 = a0-rec(abs(a0)); // trick to reduce selection testing
	  return seladd(is_inf(y1),b_or(z1, b_or(is_ltz(a0), is_nan(a0))),y1);
	}

	static inline A0 log10(const A0& a0)
	{
	  A0 x, fe, x2, y;
	  kernel_log(a0, fe, x, x2, y);
	  y =  amul(y, -Half<A0>(), x2);
	  // multiply log of fraction by log10(e) and base 2 exponent by log10(2)
	  A0 z = mul(x+y, single_constant<A0, 0x3a37b152>());//7.00731903251827651129E-4f // log10(e)lo
	  z = amul(z, y, single_constant<A0, 0x3ede0000>()); //4.3359375E-1f	       // log10(e)hi
	  z = amul(z, x, single_constant<A0, 0x3ede0000>());
	  z = amul(z, fe, single_constant<A0, 0x39826a14>());//3.0078125E-1f              // log10(2)hi
	  z = amul(z, fe, single_constant<A0, 0x3e9a0000>());//2.48745663981195213739E-4f // log10(2)lo
	  A0 y1 = a0-rec(abs(a0)); // trick to reduce selection testing
	  return seladd(is_inf(y1), b_or(z, b_or(is_ltz(a0), is_nan(a0))),y1);
	}
      };
    }
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_log.hpp<2>
// /////////////////////////////////////////////////////////////////////////////

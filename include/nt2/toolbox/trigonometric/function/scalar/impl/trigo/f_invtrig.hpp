/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_IMPL_TRIGO_F_INVTRIG_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_DETAILS_SCALAR_IMPL_TRIGO_F_INVTRIG_HPP_INCLUDED

#include <nt2/core/numeric/function/bitofsign.hpp>
#include <nt2/core/numeric/function/oneminus.hpp>
#include <nt2/core/numeric/function/oneplus.hpp>
#include <nt2/core/numeric/function/sqr.hpp>
#include <nt2/core/numeric/function/sqrt.hpp>
#include <nt2/core/numeric/function/bitwise_notand.hpp>
#include <nt2/core/numeric/function/bitwise_xor.hpp>
#include <nt2/core/numeric/function/rec.hpp>
#include <nt2/core/numeric/function/bitwise_and.hpp>
#include <nt2/core/numeric/function/select.hpp>
#include <nt2/core/numeric/function/sign.hpp>
#include <nt2/core/numeric/function/is_ltz.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
	static inline float asin(const  float& a0)
	{
	  typedef float A0;
	  A0 sign, x, z;
	  //	bf::tie(sign, x) = sign_and_abs(a0);
	  x = nt2::abs(a0);
	  sign = bitofsign(a0);
	  if ((x < Const<A0,0x38d1b717>())) return a0;
	  if ((x >  One<A0>())) return Nan<A0>();
	  bool bx_larger_05    = (x > Half<A0>());
	  if (bx_larger_05)
	    {
	      z = Half<A0>()*oneminus(x);
	      x =  sqrt(z);
	    }
	  else
	    {
	      z = sqr(x);
	    }
	  A0 z1 = fma(z,  Const<A0,0x3d2cb352>(), Const<A0,0x3cc617e3>());
	  z1 = fma(z1, z, Const<A0,0x3d3a3ec7>());
	  z1 = fma(z1, z, Const<A0,0x3d9980f6>());
	  z1 = fma(z1, z, Const<A0,0x3e2aaae4>());
	  z1 = fma(z1, z*x, x);
	  if(bx_larger_05)
	    {
	      z1 = z1+z1;
	      z1 = Pio_2<A0>()-z1;
	    }
	  return b_xor(z1, sign);
	}

	static inline float acos(const  float& a0)
	{
	  if (a0 < -Half<float>())
	    return Pi<float>()-nt2::details::internal::asin( nt2::sqrt(oneplus(a0)*Half<float>()))*Two<float>();
	  else if (a0 > Half < float>())
	    return nt2::details::internal::asin( nt2::sqrt(oneminus(a0)*Half<float>()))*Two<float>();
	  return (Pio_2<float>()-nt2::details::internal::asin(a0));
	}

	static inline float atan(const  float& a0)
	{
	  typedef float A0;
  	  if (iseqz(a0))  return a0;
  	  if (isinf(a0)) return Pio_2<A0>()*sign(a0);
          A0 y;
	  A0 x = abs(a0);
	  A0 sgn =  bitofsign(a0);
	  if( x >Const<float,0x401a827a>())//2.414213562373095 )  /* tan 3pi/8 */
	    {
	      y = Pio_2<A0>();
	      x = -rec(x);
	    }

	  else if( x > Const<float,0x3ed413cd>()) //0.4142135623730950f ) /* tan pi/8 */
	    {
	      y = Pio_4<A0>();
	      x = minusone(x)/oneplus(x);
	    }
	  else
	    y = 0.0;

	  A0 z = sqr(x);
 	  A0 z1 = fma(z,  Const<A0,0x3da4f0d1>(),Const<A0,0xbe0e1b85>());
 	  A0 z2 = fma(z,  Const<A0,0x3e4c925f>(),Const<A0,0xbeaaaa2a>());
 	  z1 = fma(z1, sqr(z), z2);
 	  y =  add(y, madd(x, mul( z1, z), x));
// 	  y +=
// 	    ((( 8.05374449538e-2 * z
// 		- 1.38776856032E-1) * z
// 	      + 1.99777106478E-1) * z
// 	     - 3.33329491539E-1) * z * x
// 	    + x;

	  return b_xor(sgn, y );

	}
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_invtrig.hpp
// /////////////////////////////////////////////////////////////////////////////

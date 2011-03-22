/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_F_PIO2_REDUCING_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_F_PIO2_REDUCING_HPP_INCLUDED

#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/sdk/constant/digits.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      // trigonometric float reduction algoritms in the [-pi/4, pi/4] range.
      // this reductions are used in the accurate and fast
      // trigonometric functions with different policies
      template < class A0, class base_A0 = typename meta::scalar_of<A0>::type >  struct pio2_reducing{};

      template < class A0>  struct pio2_reducing < A0, float>
      {
	typedef typename meta::as_integer<A0, signed>::type int_type;
	typedef typename meta::scalar_of<int_type>::type   sint_type;

	static inline int_type noreduction(const A0& x, A0& xr,  A0& xc)
	{
	  xr =  x;
	  xc = Zero<A0>();
	  return Zero<int_type>();
	}

	static inline int_type cephes_reduction(const A0& x, A0& xr, A0& xc)
	{
	  //	  A0 xi = round2even(x* Const<A0,invpio2>());
	  int_type n = toint(x* single_constant<A0,0x3f22f984>()+Half<A0>());
	  A0 xi =  tofloat(n);
	  xr = x-xi*single_constant<A0,0x3fc90f80>();
	  xr -= xi*single_constant<A0,0x37354400 >();
	  xr -= xi*single_constant<A0,0x2e85a300>();
	  xc = Zero<A0>();
	  return n;
	}

	static inline int_type fdlibm_medium_reduction(const A0& t, A0& xr, A0& xc)
	{
	  A0 fn = round2even(t*single_constant<A0,0x3f22f984>());
	  A0 r  = t-fn*single_constant<A0,0x3fc90f80>();
	  A0 w  = fn*single_constant<A0,0x37354443>();	/* 1st round good to 40 bit */
	  A0 t2 = r;
	  w  = fn*single_constant<A0,0x37354400>();
	  r  = t2-w;
	  w  = fn*single_constant<A0,0x2e85a308>()-((t2-r)-w);
	  t2 = r;	                        /* 2nd round will cover all possible cases */
	  w  = fn*single_constant<A0,0x2e85a300>();
	  r  = t2-w;
	  w  = fn*single_constant<A0,0x248d3132>()-((t2-r)-w);
	  xr = r-w;
	  xc = (r-xr)-w;
	  return  toint(fn);
	}

	static inline int_type fdlibm_big_reduction(const A0& /*t*/, A0& /*xr*/, A0& /*xc*/)
	{
	  int_type i = Zero<int_type>();
	  //	  bf::tie(xr, xc, i) = nt2::rem_pio2(t);
	  return i;
	}
      };
    }
  }

}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_pio2_reducing.hpp
// /////////////////////////////////////////////////////////////////////////////

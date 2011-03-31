/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_TRIG_BASE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_TRIG_BASE_HPP_INCLUDED

//#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo/f_pio2_reducing.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/sdk/simd/tags.hpp>

// trigonometric functions are implemented using the classical cephes/fdlibm/libc principles
// however the formal reduce/eval/return is properly divided to allow choices versus
// speed, accuracy and  SIMD vectorisation
//
// On small ranges performance can be obtained with almost full accuracy (1 ulp) at 10
// cycles per element for a cosine computation using SIMD. But if one require full accuracy
// on the full float or double range, the prize can grow up to few thousands of cycle for
// some big values of input.
// See the NT2 technical documentation for more insights


namespace nt2
{
  namespace details
  {
    // in the class defined below:
    // A0 is the argument type of the trigonometric functions
    //
    // Up to now, only floating real based on IEEE 754 float or double are supported
    // (sorry no long double yet for lack of portability)
    // The possible conversion of integer types to floating ones in scalar (not simd)
    // is already addressed in the primary functors invocations namely cos_, sin_ etc.

    namespace internal
    {

      // This class expose the public static members:
      // cosa     x -> cos(a*x)
      // sina     x -> sin(a*x)
      // tana     x -> tan(a*x)
      // cota     x -> cot(a*x)
      // sincosa  x -> cos(a*x) and sin(a*x)
      // "a" is not a run time parameter !
      // It stands as a remainder that according the Tag it can be considered
      // as a scale factor for the input of values:
      //   1           radian_tag,
      //   pi          pi_tag
      //   pi/180      degree_tag,
      // but the scaling is internal to the algorithm to provide better accuracy
      // and better performance.

      // It heritates of a reduction and an evaluation class to perform
      // the appropriate range reductions and function evaluations.

      // In this file stands the scalar version !
      // Some definitions are useless but provide facilities of comparaison with
      // the SIMD implementation
      //
      template < class A0,
		 class unit_tag,
		 class precision_tag, 
		 class style > 
      struct trig_base{};

      template < class A0,
		 class unit_tag >
      struct trig_base<A0,unit_tag,trig_tag,tag::not_simd_type>
      {
	typedef trig_reduction<A0,unit_tag,trig_tag>                       redu_t;
	typedef trig_evaluation<A0,trig_tag,tag::not_simd_type>            eval_t;
	typedef typename meta:: scalar_of<A0>::type                           sA0; // scalar version of A0
	typedef typename meta::as_integer<A0, signed>::type              int_type; // signed integer type associated to A0
	typedef typename meta::scalar_of<int_type>::type                sint_type; // scalar version of the associated type

	// for all functions the scalar algorithm is:
	// * quick return (or exception raising TODO) for inf and nan or specific invalid cases inputs
	// * test for possible ask result to standard library call if more efficient
	// * range reduction
	// * computation of sign and evaluation selections flags
	// * evaluations
	// * return with flag based corrections

	static inline A0 cosa(const A0& a0)
	{
	  static const sint_type de = sizeof(sint_type)*8-1;   // size in bits of the scalar types minus one
	  if (is_invalid(a0)) return Nan<A0>(); //Nan or Inf input
	  A0 x =  nt2::abs(a0);
	  if (redu_t::replacement_needed(x))
	    {
	      return redu_t::cos_replacement(a0);
	    }
	  else
	    {
	      A0 xr = Zero<A0>(), xc;
	      int_type n = redu_t::reduce(x, xr, xc);
	      int_type swap_bit = n&One<int_type>();
	      int_type sign_bit = shli(b_xor(swap_bit, (n&2)>>1), de);
	      A0 z = sqr(xr);
	      if (is_nez(swap_bit))
		{
		  z = eval_t::sin_eval(z, xr, xc);
		}
	      else
		{
		  z = eval_t::cos_eval(z, xr, xc);
		}
	      return b_xor(z,sign_bit);
	    }
	}

	static inline A0 sina(const A0& a0)
	{
	  static const sint_type de = sizeof(sint_type)*8-1;
	  if (is_invalid(a0)) return Nan<A0>();
	  A0 x =  nt2::abs(a0);
	  if (redu_t::replacement_needed(x))
	    {
	      return redu_t::sin_replacement(a0);
	    }
	  else
	    {
	      A0 xr = Zero<A0>(), xc;
	      int_type n = redu_t::reduce(x, xr, xc);
	      int_type swap_bit = n&One<int_type>();
	      A0 sign_bit = b_xor(bitofsign(a0), shli(n&Two<int_type>(), de-1));
	      A0 z = sqr(xr);
	      if (is_eqz(swap_bit))
		{
		  z = eval_t::sin_eval(z, xr, xc);
		}
	      else
		{
		  z = eval_t::cos_eval(z, xr, xc);
		}
	      return b_xor(z,sign_bit);
	    }
	}

	static inline A0 tana(const A0& a0)
	{
	  if (redu_t::tan_invalid(a0)) return Nan<A0>();
	  if (is_eqz(a0)) return a0;
	  A0 x =  nt2::abs(a0);
	  if (redu_t::replacement_needed(x))
	    {
	      return redu_t::tan_replacement(a0);
	    }
	  else
	    {
	      A0 xr = Zero<A0>(), xc, y;
	      int_type n = redu_t::reduce(x, xr, xc);
	      y = eval_t::tan_eval(xr, xc, 1-((n&1)<<1));
	      // 1 -- n even
	      //-1 -- n odd
	      return b_xor(y, bitofsign(a0));
	    }
	}
	static inline A0 cota(const A0& a0)
	{
	  if (redu_t::cot_invalid(a0)) return Nan<A0>();
	  A0 x =  nt2::abs(a0);
	  if (redu_t::replacement_needed(x))
	    {
	      return redu_t::cot_replacement(a0);
	    }
	  else
	    {
	      const A0 bos =  bitofsign(a0);
	      if (!a0) return b_or(Inf<A0>(), bos); 
	      A0 xr, xc, y;
	      int_type n = redu_t::reduce(x, xr, xc);
	      y = eval_t::cot_eval(xr, xc, 1-((n&1)<<1));
	      return b_xor(y, bos);
	    }
	}


	static inline void sincosa(const A0& a0, A0& s, A0& c)
	{
	  if (is_invalid(a0)) { s = c = Nan<A0>(); return; }
	  A0 x =  nt2::abs(a0);
	  if (redu_t::replacement_needed(x))
	    {
	      redu_t::sincos_replacement(a0, s, c);
	    }
	  else
	    {
	      static const sint_type de = sizeof(sint_type)*8-1;
	      A0 xr, xc;
	      int_type n = redu_t::reduce(x, xr, xc);
	      int_type swap_bit = n&One<int_type>();
	      A0 z = sqr(xr);
	      int_type cos_sign_bit = shli(b_xor(swap_bit, (n&Two<int_type>())>>1), de);
	      A0 sin_sign_bit = b_xor(bitofsign(a0), shli(n&Two<int_type>(), de-1));

	      if (is_nez(swap_bit))
		{
		  c = eval_t::sin_eval(z, xr, xc);
		  s = eval_t::cos_eval(z, xr, xc);
		}
	      else
		{
		  c = eval_t::cos_eval(z, xr, xc);
		  s = eval_t::sin_eval(z, xr, xc);
		}
	      c = b_xor(c,cos_sign_bit);
	      s = b_xor(s,sin_sign_bit);
	    }
	}
      };
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of trig_base.hpp
// /////////////////////////////////////////////////////////////////////////////

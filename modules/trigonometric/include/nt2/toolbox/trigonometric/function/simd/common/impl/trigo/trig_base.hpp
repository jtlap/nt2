/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_IMPL_TRIGO_TRIG_BASE_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_IMPL_TRIGO_TRIG_BASE_HPP_INCLUDED

#include <nt2/include/functions/any.hpp>
//#include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo/f_pio2_reducing.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/sdk/simd/tags.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0, class unit_tag> 
      struct trig_base < A0, unit_tag, trig_tag, tag::simd_type >
      {
	typedef trig_reduction<A0,unit_tag,trig_tag>                       redu_t;
	typedef trig_evaluation<A0,trig_tag,tag::simd_type>                eval_t;
	typedef typename meta::scalar_of<A0>::type                            sA0; // scalar version of A0
	typedef trig_reduction<sA0,unit_tag,trig_tag>                     sredu_t;
	typedef typename meta::as_integer<A0, signed>::type              int_type; // signed integer type associated to A0
	typedef typename meta::scalar_of<int_type>::type                sint_type; // scalar version of the associated type   

	// for all functions the scalar algorithm is:
	// * test for possible return to standard libraries calls which are mapped on vectors elements
	// * range reduction
	// * computation of sign and evaluation selections flags
	// * evaluations of the two branches and selection using flags
	// * return with flag based corrections and inf and nan or specific invalid cases inputs considerations

	

	static inline A0 cosa(const A0& a0)
	{
	  static const sint_type de = sizeof(sint_type)*8-1;            // size in bits of the scalar types minus one
	  A0 x = nt2::abs(a0);
	  if (any(redu_t::replacement_needed(x)))
	    {
	      return map(&sredu_t::cos_replacement, a0);
	    }
	  else
	    {
	      A0 xr = Zero<A0>(), xc;
	      int_type n =  redu_t::reduce(x, xr, xc); 
	      int_type swap_bit = n&One<int_type>();
	      int_type sign_bit = shli(b_xor(swap_bit, shri(n&Two<int_type>(), 1)), de); 
	      A0 z = sqr(xr);
	      const A0 testnan = is_invalid(a0);
	      z = select(is_nez(swap_bit),eval_t::sin_eval(z, xr, xc),eval_t::cos_eval(z, xr, xc)); 
	      z = b_xor(z,sign_bit);
	      return b_or(testnan, z);
	    }
	}

	static inline A0 sina(const A0& a0)
	{
	  static const sint_type de = sizeof(sint_type)*8-1;            // size in bits of the scalar types minus one
	  A0 x = nt2::abs(a0);
	  if (any(redu_t::replacement_needed(x)))
	    {
	      return map(&sredu_t::sin_replacement, a0);
	    }
	  else
	    {
	      A0 xr, xc;
	      int_type n = redu_t::reduce(x, xr, xc);
	      int_type swap_bit = n&One<int_type>();
	      A0 sign_bit = b_xor(bitofsign(a0), shli(n&Two<int_type>(), de-1)); 
	      A0 z = sqr(xr);
	      z = b_xor(select(is_eqz(swap_bit),eval_t::sin_eval(z, xr, xc),eval_t::cos_eval(z, xr, xc)),sign_bit); 
	      const A0 testnan = is_invalid(a0);
	      return b_or(testnan, z);
	    }
	}

	static inline A0 tana(const A0& a0)
	{
	  A0 x =  nt2::abs(a0); 
	  if (any(redu_t::replacement_needed(x)))
	    {
	      return map(&sredu_t::tan_replacement, a0);
	    }
	  else
	    {	  
	      A0 xr = Zero<A0>(), xc, y;
	      int_type n = redu_t::reduce(x, xr, xc);
	      y = eval_t::tan_eval(xr, xc, oneminus(shli((n&One<int_type>()), 1)));           // 1 -- n even
							                              //-1 -- n odd 
	      A0 testnan = redu_t::tan_invalid(a0);
	      return b_or(testnan, b_xor(y, bitofsign(a0)));	  	      
	    }
	}

	static inline A0 cota(const A0& a0)
	{
	  A0 x =  nt2::abs(a0); 
	  if (any(redu_t::replacement_needed(x)))
	    {
	      return map(&sredu_t::cot_replacement, a0);
	    }
	  else
	    {	   
	      A0 xr, xc, y;
	      int_type n = redu_t::reduce(x, xr, xc);
	      y = eval_t::cot_eval(xr, xc, oneminus(shli((n&One<int_type>()), 1)));           // 1 -- n even
							                              //-1 -- n odd 
	      A0 testnan = redu_t::cot_invalid(a0); 
	      return b_or(testnan, b_xor(y, bitofsign(a0)));	  	      
	    }
	}
	// simultaneous cosa and sina function
	static inline void sincosa(const A0& a0, A0& s, A0& c)
	{
	  static const sint_type de = sizeof(sint_type)*8-1;            // size in bits of the scalar types minus one
	  A0 x =  nt2::abs(a0);
	  if (false && any(redu_t::replacement_needed(x)))
	    {
	      // map(&sredu_t::sincos_replacement, a0, s, c);
	    }
	  else
	    {
	      A0 xr, xc;
	      int_type n = redu_t::reduce(x, xr, xc);
	      int_type swap_bit = n&One<int_type>();
	      A0 z = nt2::sqr(xr);
	      int_type cos_sign_bit = shli(b_xor(swap_bit, shri(n&Two<int_type>(), 1)), de); 
	      int_type sin_sign_bit = b_xor(shli(n&Two<int_type>(), de-1), bitofsign(a0)); 
	      A0 t1 = eval_t::sin_eval(z, xr, xc);
	      A0 t2 = eval_t::cos_eval(z, xr, xc);
	      int_type test = is_nez(swap_bit);
	      A0 invalid = is_invalid(a0); 
	      c = b_or(invalid,b_xor(sel(test, t1, t2),cos_sign_bit));
	      s = b_or(invalid,b_xor(sel(test, t2, t1),sin_sign_bit)); 
	    }
	}
        static inline A0    scale       (const A0& a0){return a0*trig_ranges<A0,unit_tag>::scale();            }
	
      }; 
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of trig_base.hpp
// /////////////////////////////////////////////////////////////////////////////

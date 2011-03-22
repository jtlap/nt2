/*******************************************************************************
 *         Copyright 2003-2009 LASMEA UMR 6602 CNRS/U.B.P & ENSCCF   
 *         Copyright 2007-2009 IEF    UMR 8622 CNRS/Univ Paris Sud XI
 *         Copyright 2009-2009 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef __NT2__SUPPORT__NUMERIC__SCALAR__FUNCTIONS__IMPLEMENTATION__EXPLOG__F_EXPO_FINALIZATION__HPP__INCLUDED
#define __NT2__SUPPORT__NUMERIC__SCALAR__FUNCTIONS__IMPLEMENTATION__EXPLOG__F_EXPO_FINALIZATION__HPP__INCLUDED

////////////////////////////////////////////////////////////////////////////////


namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0, class speed_tag> struct exp_finalization < A0, speed_tag, fast_tag, float> 
      {
	static inline A0 finalize(const A0&, const A0& x,
				  const A0& c, const A0 & k, 
				  const A0& hi,const A0& lo)
	{
	  A0 y =   oneminus(((lo-(x*c)/(Two<A0>()-c))-hi));
	  return fast_ldexp(y, toint(k));
	}
      };
      template < class A0 > struct exp_finalization < A0, two_tag, fast_tag, float> 
      {
	static inline A0 finalize(const A0& a0, const A0& x,
				  const A0& c, const A0 & k, 
				  const A0& ,const A0& )
	{
	  A0 y = oneminus(((-(x*c)/(Two<A0>()-c))-x));
	  return fast_ldexp(y, toint(k));
	}
      };
      template < class A0 > struct exp_finalization < A0, two_tag, accu_tag, float> 
      {
	static inline A0 finalize(const A0& a0, const A0& x,
				  const A0& c, const A0 & k, 
				  const A0& ,const A0& )
	{
	  A0 y = oneminus(((-(x*c)/(Two<A0>()-c))-x));
	  y = fast_ldexp(y, toint(k));
	  // adjust for 2^n n flint
	  return where(isflint(a0), round2even(y), y);
	}
      };
      
      template < class A0 > struct exp_finalization < A0, ten_tag, accu_tag, float> 
      {
	static inline A0 finalize(const A0& a0, const A0&  ,
				  const A0& c , const A0& k, 
				  const A0&   , const A0& )
	{
	  
	  A0 y = fast_ldexp(c, toint(k));
	  //adjust for 10^n n flint
	  return where( (isgtz(a0) && isflint(a0)) , round2even(y), y); 
	}
      }; 
      
    }	
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_expo_finalization.hpp
// /////////////////////////////////////////////////////////////////////////////

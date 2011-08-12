//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_LOG_BASE_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPLOG_LOG_BASE_HPP_INCLUDED
#include <nt2/core/numeric/functions/is_nan.hpp>
#include <nt2/core/numeric/functions/is_ltz.hpp>


namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0,
		 class Tag,
		 class Style , 
		 class base_A0 = typename meta::scalar_of<A0>::type> 
      struct logarithm{}; 


      template < class A0, class Tag> 
      struct logarithm< A0, Tag, not_simd_type >
      {
	typedef log_approximation<A0,Tag>                          approx_t;
	typedef log_finalization<A0,Tag>                         finalize_t; 
	// compute log in base a of x, where a is 1, 2 or ten depending on Tag
	static inline A0 loga(const A0& a0)
	{
	  if (a0 == Inf<A0>()) return a0;
	  if (iseqz(a0)) return Minf<A0>();
	  if (nt2::isnan(a0)||isltz(a0)) return Nan<A0>();
	  A0 x, fe, x2, y;
	  approx_t::kernel_log(a0, fe, x, x2, y);
	  return finalize_t::finalize(fe, x, x2, y); 
	}
      }; 	
    }
  }
}


#endif

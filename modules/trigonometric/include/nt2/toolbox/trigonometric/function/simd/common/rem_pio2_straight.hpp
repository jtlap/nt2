//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_REM_PIO2_STRAIGHT_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_REM_PIO2_STRAIGHT_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
namespace nt2 { namespace meta
{
  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementation when real
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::rem_pio2_straight_, tag::cpu_,
			     (A0)(X),
			     ((simd_ < real_<A0>, X > ))
			     ((simd_ < real_<A0>, X > ))
			     ((simd_ < real_<A0>, X > ))
			     )
  {
    typedef typename meta::as_integer<A0>::type result_type;    
    inline result_type operator()(A0 const& x, A0 & xr, A0& xc) const
      {
	//	  static int i = 0;
	//	  std::cout << "fdlibm_straight_reduction " << i++ << std::endl; 
	xr = x-Pio2_1<A0>();
	xr -= Pio2_2<A0>();
	xr -= Pio2_3<A0>();
	xc = Zero<A0>();
	return One<result_type>(); 
    }
  }; 
} }
#endif

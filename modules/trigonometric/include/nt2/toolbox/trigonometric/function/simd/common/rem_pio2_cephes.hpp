//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_REM_PIO2_CEPHES_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_REM_PIO2_CEPHES_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
#include <nt2/include/functions/fast_toint.hpp>

namespace nt2 { namespace meta
{
  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementation when real
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::rem_pio2_cephes_, tag::cpu_,
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
	//	  std::cout << "fdlibm_cephes_reduction " << i++ << std::endl;
        A0 xi =  round2even(x*Twoopi<A0>()); 
	  //	result_type n = fast_toint(x*Twoopi<A0>()+Half<A0>());
	  //	A0 xi = tofloat(n); //b_or(is_invalid(x), tofloat(n));
	xr = x-xi*Pio2_1<A0>();
	xr -= xi*Pio2_2<A0>();
	xr -= xi*Pio2_3<A0>();
	xc = Zero<A0>();
	return fast_toint(xi); 
    }
  }; 
} }
#endif

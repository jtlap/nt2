//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_REM_PIO2_MEDIUM_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_REM_PIO2_MEDIUM_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
namespace nt2 { namespace meta
{
  /////////////////////////////////////////////////////////////////////////////
  // reference based Implementation when real
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::rem_pio2_medium_, tag::cpu_,
			     (A0)(X),
			     ((simd_ < real_<A0>, X > ))
			     ((simd_ < real_<A0>, X > ))
			     ((simd_ < real_<A0>, X > ))
			     )
  {
    typedef typename meta::as_integer<A0>::type result_type;    
    inline result_type operator()(A0 const& t, A0 & xr, A0& xc) const
      {
	//	  static int i = 0;
	//	  std::cout << "fdlibm_medium_reduction " << i++ << std::endl; 
	A0 fn = round2even(t*Invpio_2<A0>());
	A0 r  = t-fn*Pio2_1<A0>(); 
	A0 w  = fn*Pio2_1t<A0>(); 
	A0 t2 = r;
	w  = fn*Pio2_2<A0>();
	r  = t2-w;
	w  = fn*Pio2_2t<A0>()-((t2-r)-w);
	t2 = r;	                        
	w  = fn*Pio2_3<A0>(); 
	r  = t2-w;
	w  = fn*fn*Pio2_3t<A0>()-((t2-r)-w);
	xr = r-w;
	xc = (r-xr)-w;
	return  toint(fn);    
    }
  }; 
} }
#endif

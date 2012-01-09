//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_SQRT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_SQRT_HPP_INCLUDED
#include <nt2/toolbox/arithmetic/functions/sqrt.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/inf.hpp>   
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <iostream>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        typedef typename meta::as_real<A0>::type rA0;
        typedef typename meta::as_logical<rA0>::type lA0;
        rA0 x = nt2::abs(real(a0));
        rA0 y = nt2::abs(imag(a0));
        lA0 gtxy = gt(x, y); 
        rA0 r = if_else(gtxy, y/x, x/y);
        rA0 rr= nt2::sqrt(oneplus(sqr(r)));
        rA0 sqrtx = sqrt(x); 
        rA0 w = if_else(gtxy,
                        sqrtx*sqrt(Half<rA0>()*oneplus(rr)),
                        sqrt(y)*sqrt(Half<rA0>()*(r+rr)));
        rA0 tmp = negif(is_ltz(imag(a0)), w); 
        A0 z = if_else(is_gez(real(a0)),
                       result_type(w, imag(a0)*Half<rA0>()/w),
                       result_type(tmp, imag(a0)*Half<rA0>()/tmp));
        return if_else(is_real(a0),
                       if_else(is_gez(real(a0)),
                               result_type(sqrtx,Zero<rA0>()),
                               result_type(Zero<rA0>(),sqrtx)),
                       z); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_complex<rA0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
          const rA0 root = nt2::sqrt(nt2::abs(imag(a0)))*Sqrt_2o_2<rA0>();
          result_type res = result_type(root, sign(imag(a0))*root); 
          return if_else(is_eqz(a0), result_type(Zero<rA0>()), res); 
    }
  };
  
} }

#endif

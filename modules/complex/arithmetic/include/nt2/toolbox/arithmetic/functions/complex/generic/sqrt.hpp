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
#include <nt2/toolbox/constant/common.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/pure.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/inf.hpp>   
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        typedef typename meta::as_real<A0>::type rtype;
        typedef typename meta::as_logical<rtype>::type ltype;
        rtype x = nt2::abs(real(a0));
        rtype y = nt2::abs(imag(a0));
        ltype gtxy = gt(x, y);
        ltype gezra0 = is_gez(real(a0)); 
        rtype r = if_else(gtxy, y/x, x/y);
        rtype rr= nt2::sqrt(oneplus(sqr(r)));
        rtype sqrtx = sqrt(x); 
        rtype w = if_else(gtxy,
                          sqrtx*sqrt(Half<rtype>()*oneplus(rr)),
                          sqrt(y)*sqrt(Half<rtype>()*(r+rr)));
        rtype tmp = negif(is_ltz(imag(a0)), w); 
        A0 z = if_else(gezra0,
                       result_type(w, imag(a0)*Half<rtype>()/w),
                       result_type(tmp, imag(a0)*Half<rtype>()/tmp)
                       );
        z = if_else(is_real(a0),
                    if_else(gezra0,
                            result_type(sqrtx,Zero<rtype>()),
                            result_type(Zero<rtype>(),sqrtx)),
                    if_else(is_imag(a0),
                            nt2::sqrt(pure(a0)),
                            z)
                    ); 
        if (all(is_finite(z))) return z;                      
        z = if_else(eq(imag(a0), Inf<rtype>()),
                    result_type(Inf<rtype>(), Inf<rtype>()),
                    z);
        z = if_else(logical_andnot(eq(real(a0), Minf<rtype>()), is_nan(imag(a0))),
                    result_type(if_else_zero(eq(imag(a0), Inf<rtype>()), imag(a0)),
                                copysign(Inf<rtype>(), imag(a0))
                                ),
                    z);
        return z;    
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
                              , (generic_< imaginary_< arithmetic_<A0> > >)
                              )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        const rtype root = nt2::sqrt(nt2::abs(imag(a0)))*Sqrt_2o_2<rtype>();
        result_type res = result_type(root, sign(imag(a0))*root); 
        return if_else(is_eqz(a0), Zero<result_type>(), res); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sqrt_, tag::cpu_, (A0)
                              , (generic_< dry_< arithmetic_<A0> > >)
                              )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<rtype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        const rtype root = nt2::sqrt(nt2::abs(real(a0))); 
        return if_else(is_ltz(a0),
                       result_type(Zero<rtype>(), root),
                       result_type(root)); 
      }
  };
} }

#endif

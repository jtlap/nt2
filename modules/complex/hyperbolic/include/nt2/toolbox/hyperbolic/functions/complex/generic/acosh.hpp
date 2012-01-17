//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_ACOSH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_COMPLEX_GENERIC_ACOSH_HPP_INCLUDED
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>

//  cacosh(conj(z)) = conj(cacosh(z)).
//  cacosh(±0 + i0) returns +0 + i-Fð /2.-A
//  cacosh(x + i $B!g(B) returns +$B!g(B + i-Fð /2, for finite x.-A
//  cacosh(x + iNaN) returns NaN + iNaN and optionally raises the invalid floating-point exception, for finite x.
//  cacosh($B!]!g(B + iy) returns +$B!g(B + i-Fð , for positive-signed finite y.-A
//  cacosh(+$B!g(B + iy) returns +$B!g(B + i0, for positive-signed finite y.
//  cacosh($B!]!g(B + i $B!g(B) returns +$B!g(B + i3-Fð /4.-A
//  cacosh(+$B!g(B + i $B!g(B) returns +$B!g(B + i-Fð /4.-A
//  cacosh(±$B!g(B + iNaN) returns +$B!g(B + iNaN.
//  cacosh(NaN + iy) returns NaN + iNaN and optionally raises the -F¡¡invalid floating-point exception, for finite y.-A
//  cacosh(NaN + i $B!g(B) returns +$B!g(B + iNaN.
//  cacosh(NaN + iNaN) returns NaN + iNaN.

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype; 
      A0 y = result_type(minusone((real(a0)-imag(a0))*(real(a0)+imag(a0))), 
                         Two<rtype>()*real(a0)*imag(a0));
      A0 res = nt2::log(nt2::sqrt(y)+a0);
      return res;     
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      rtype y = oneplus(sqr(imag(a0)));
      A0 res = nt2::log(A0(nt2::sqrt(y))+a0);
      return res;     
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::acosh(real(a0))); 
    }
  };
  
} }

#endif

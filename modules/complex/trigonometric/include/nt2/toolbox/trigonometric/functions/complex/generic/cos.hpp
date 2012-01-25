//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_COS_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_COS_HPP_INCLUDED
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
/* ccos (x + I * y) = cos (x) * cosh (y) - I * (sin (x) * sinh (y)) */

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cos_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype; 
      rtype c, s, ch, sh;
      sincos(real(a0), s, c);
      sinhcosh(imag(a0), sh, ch);
      return result_type(c*ch, if_zero_else(logical_or(is_imag(a0), is_real(a0)), -s*sh));     
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cos_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_dry<rA0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::cosh(imag(a0))); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cos_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_dry<rA0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return result_type(nt2::cos(real(a0))); 
    }
  };
} }

#endif

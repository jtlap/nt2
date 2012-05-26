//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_COSD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_COSD_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/functions/cosd.hpp>
#include <nt2/include/functions/sincosd.hpp>
#include <nt2/include/functions/sinhcosh.hpp>
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/cosh.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/cosd.hpp>
#include <nt2/include/constants/deginrad.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosd_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype; 
      rtype c, s, ch, sh;
      sincosd(nt2::real(a0), s, c);
      sinhcosh(nt2::imag(a0)*Deginrad<rtype>(), sh, ch);
      return result_type(c*ch, if_zero_else(logical_or(is_imag(a0), is_real(a0)), -s*sh));     
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosd_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_dry<rtype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::cosh(nt2::imag(a0)*Deginrad<rtype>())); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cosd_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_dry<rA0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::cosd(nt2::real(a0))); 
    }
  };
} }

#endif

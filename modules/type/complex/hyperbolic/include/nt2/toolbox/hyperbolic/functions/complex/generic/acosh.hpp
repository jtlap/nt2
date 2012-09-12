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
#include <nt2/toolbox/hyperbolic/functions/acosh.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_else.hpp> 
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/acos.hpp>

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/nan.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      // acosh(a0) = +/-i acos(a0)
      // Choosing the sign of multiplier to give nt2::real(acosh(a0)) >= 0
      // we have compatibility with C99.
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::as_logical<rtype>::type ltype;
      result_type res = nt2::acos(a0);
      res = if_else(logical_notand(is_nan(nt2::imag(res)), is_lez(nt2::imag(res))),
                    mul_i(res), mul_minus_i(res)); 
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
      result_type res = nt2::acos(a0);
      res = if_else(logical_notand(is_nan(nt2::imag(res)), is_lez(nt2::imag(res))),
                    mul_i(res), mul_minus_i(res)); 
      return res;     
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acosh_, tag::cpu_, (A0)
                            , (generic_< dry_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      result_type res = nt2::acos(a0);
      res = if_else(logical_notand(is_nan(nt2::imag(res)), is_lez(nt2::imag(res))),
                    mul_i(res),
                    mul_minus_i(res)); 
      return res;     
    }
  };
  
} }

#endif

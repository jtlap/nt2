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
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/none.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/if_else.hpp> 
#include <nt2/include/functions/if_zero_else.hpp>

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/nan.hpp>
#include <iostream>

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
      typedef typename meta::as_logical<rtype>::type ltype;
      A0 y = result_type(minusone((real(a0)-imag(a0))*(real(a0)+imag(a0))), 
                         Two<rtype>()*real(a0)*imag(a0));
      A0 res = nt2::log(nt2::sqrt(y)+a0);
      if(none(is_inf(a0))) return res;
      ltype isnana0 = is_nan(imag(a0));
//      ltype ipos = is_ltz(imag(a0));
//       A0 aa0 = if_else(ipos, a0, conj(a0));
         A0 aa0 = a0; 
//       res = if_else(ipos, res, conj(res));
      res = if_else(logical_andnot(eq(real(aa0), Inf<rtype>()), is_nan(imag(aa0))),
                    Inf<A0>(),
                    res);
      res = if_else(eq(real(aa0), Minf<rtype>()),
                    result_type(Inf<rtype>(),Pi<rtype>()), 
                    res);
      res = if_else(eq(imag(aa0), Inf<rtype>()),
                    if_else(eq(real(aa0), Minf<rtype>()),
                            result_type(Inf<rtype>(),Three<rtype>()*Pi<rtype>()/Four<rtype>()), 
                            result_type(Inf<rtype>(),Pio_2<rtype>())), 
                    res);
//       res =  if_else(ipos, res, conj(res)); 
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

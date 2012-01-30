//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_EXP_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_EXP_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/exp.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp_, tag::cpu_
                            , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rtype; 
      rtype c, s;
      sincos(imag(a0), s, c);
      rtype rho = nt2::exp(real(a0)); 
      return if_else(logical_or(is_real(a0), eq(real(a0), Minf<rtype>())),
                     result_type(rho, Zero<rtype>()),
                     rho*result_type(c, s)); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp_, tag::cpu_
                            , (A0)
                            , (generic_< imaginary_<floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type             rtype; 
    typedef typename meta::as_complex<rtype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      rtype  c, s;
      nt2::sincos(imag(a0), s, c); 
      return result_type(c, s); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exp_, tag::cpu_
                            , (A0)
                            , (generic_< dry_<floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(nt2::exp(real(a0))); 
    }
  };  
} }


#endif

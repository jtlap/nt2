//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SIMD_COMMON_PROD_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SIMD_COMMON_PROD_HPP_INCLUDED
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::prod_, tag::cpu_, (A0)(X)
                                     , ((simd_< complex_< arithmetic_<A0> >, X>))
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_complex<stype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      A0 rho = nt2::abs(a0);
      A0 theta = arg(a0);
      return frompolar(prod(rho), sum(theta)); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::prod_, tag::cpu_, (A0)(X)
                                     , ((simd_< imaginary_< arithmetic_<A0> >, X >))
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_real<stype>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      const result_type signedness = (meta::cardinal_of<A0>::value <= 2) ? Mone<result_type>() : One<result_type>(); 
      return nt2::prod(imag(a0))*signedness; 
    }
  };
  
} }

#endif

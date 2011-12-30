//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SIMD_COMMON_PROD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_SIMD_COMMON_PROD_HPP_INCLUDED
#include <boost/simd/include/functions/prod.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/arg.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::prod_, tag::cpu_, (A0)(X)
                                     , ((simd_< complex_< arithmetic_<A0> >, X>))
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_complex<stype>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      A0 rho = boost::simd::abs(a0);
      A0 theta = arg(a0);
      return frompolar(prod(rho), sum(theta)); 
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::prod_, tag::cpu_, (A0)(X)
                                     , ((simd_< imaginary_< arithmetic_<A0> >, X >))
                            )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::scalar_of<rtype>::type stype;
    typedef typename meta::as_real<stype>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const result_type signedness = (meta::cardinal_of<A0>::value <= 2) ? Mone<result_type>() : One<result_type>(); 
      return boost::simd::prod(imag(a0))*signedness; 
    }
  };
  
} } }

#endif

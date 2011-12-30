//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_RSQRT_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/rsqrt.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/is_gtz.hpp>
#include <boost/simd/include/functions/sign.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/constants/sqrt_2o_2.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rsqrt_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type rA0;
      rA0 r = boost::simd::abs(a0);
      return rec(result_type(boost::simd::sqrt(r+a0), sign(imag(a0))*boost::simd::sqrt(r-a0))*Sqrt_2o_2<rA0>());//TODO optimize
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::rsqrt_, tag::cpu_, (A0)
                            , (generic_< imaginary_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type rA0;
    typedef typename meta::as_complex<rA0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      const rA0 root = rsqrt(boost::simd::abs(imag(a0))); 
      return result_type(One<result_type>(), sign(imag(a0)))*root*Sqrt_2o_2<rA0>(); 
    }
  };
  
} } }

#endif

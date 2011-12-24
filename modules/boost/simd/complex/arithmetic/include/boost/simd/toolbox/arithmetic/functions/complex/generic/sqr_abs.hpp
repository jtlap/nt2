//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_SQR_ABS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_SQR_ABS_HPP_INCLUDED
#include <boost/simd/toolbox/arithmetic/functions/sqr_abs.hpp>
#include <boost/simd/include/functions/real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/sdk/complex/imaginary.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqr_abs_, tag::cpu_, (A0)
                            , (generic_< complex_< arithmetic_<A0> > >)
                            )
  {
    typedef typename meta::real_of<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return adds(sqr_abs(real(a0)) + sqr_abs(real(a0))); 
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::sqr_abs_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::real_of<A0>::type result_type;
      return sqr(real(a0)) + sqr(real(a0)); 
    }
  };
  
} } }

#endif

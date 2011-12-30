//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_SPLATTED_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMPLEX_COMMON_SPLATTED_MAXIMUM_HPP_INCLUDED
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/maximum.hpp>
#include <boost/simd/sdk/complex/meta/as_complex.hpp>
#include <boost/simd/sdk/complex/meta/as_real.hpp>
#include <boost/simd/include/functions/imag.hpp>
#include <boost/simd/include/functions/real.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splatted_maximum_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<complex_<arithmetic_<A0> >,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return splat<A0>(maximum(a0))
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splatted_maximum_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<imaginary_<arithmetic_<A0> >,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return splat<A0>(maximum(a0))
    }
  };
   
} } }


#endif

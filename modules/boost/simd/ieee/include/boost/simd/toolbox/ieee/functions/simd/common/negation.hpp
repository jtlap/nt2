//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEGATION_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEGATION_HPP_INCLUDED
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::negation_, tag::cpu_,
                           (A0)(X),
                           ((simd_<arithmetic_<A0>,X>))
                           ((simd_<arithmetic_<A0>,X>))
                          )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return  if_else(is_ltz(a1),-a0,if_else_zero(is_nez(a1), a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::negation_, tag::cpu_,
                           (A0)(X),
                           ((simd_<unsigned_<A0>,X>))
                           ((simd_<unsigned_<A0>,X>))
                          )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
        return  is_nez(a1)&a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::negation_, tag::cpu_,
                           (A0)(X),
                           ((simd_<floating_<A0>,X>))
                           ((simd_<floating_<A0>,X>))
                          )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 tmp = if_else(is_nez(a1), a0, a1);
      A0 ma0 =  unary_minus(a0); 
      tmp = if_else(is_ltz(a1), ma0, tmp);
      tmp = select(is_nan(a1), a1, tmp); 
      return tmp;
    }
  };
} } }
#endif

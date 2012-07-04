//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_CLZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_CLZ_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/clz.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/oneminus.hpp>
#include <boost/simd/include/functions/reversebits.hpp>
#include <boost/simd/include/functions/ffs.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/if_else.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::clz_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t =  bitwise_cast<result_type>(a0); 
      typedef typename meta::scalar_of<A0>::type s_type;
      const result_type siz = boost::simd::splat<result_type>(sizeof(s_type)*8); 
      return if_else(is_eqz(a0), siz, 
                     minusone(boost::simd::ffs(boost::simd::reversebits(t)))); 
    }
  };
} } }


#endif

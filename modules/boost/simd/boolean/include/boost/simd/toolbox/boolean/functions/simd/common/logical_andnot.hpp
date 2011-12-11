//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_LOGICAL_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_LOGICAL_ANDNOT_HPP_INCLUDED
#include <boost/simd/toolbox/boolean/functions/logical_andnot.hpp>
#include <boost/simd/include/functions/bitwise_andnot.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/mask2logical.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  // FIXME: only enable if sizeof(A0) == sizeof(as_arithmetic<A0>::type)
  // but what do we do if A0 is logical. We have also to enforce that
  // A0 and A1 are compatable TODO
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::logical_andnot_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<fundamental_<A0>,X>))
                              ((simd_<fundamental_<A1>,X>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return mask2logical(b_andnot(genmask(a0), genmask(a1)));
    }
  };
} } }


#endif

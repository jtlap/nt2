//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOGICAL_OR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOGICAL_OR_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/bitwise_or.hpp>
#include <boost/simd/include/constants/digits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::logical_or_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<fundamental_<A0>,X>))((simd_<fundamental_<A1>,X>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
     return is_nez(a0) | is_nez(a1);
    }
  };
} } }


#endif

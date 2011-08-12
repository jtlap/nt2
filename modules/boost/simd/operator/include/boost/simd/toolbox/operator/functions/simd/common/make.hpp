//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_MAKE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_MAKE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// make for SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::make_, tag::cpu_, (A0)(X)
                            , ((target_< simd_< arithmetic_<A0>, X > >))
                            )
  {
    typedef simd::native<A0, X> result_type;
    #define M0(z,n,t)                                                 \
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(n)                                        \
    {                                                                 \
      BOOST_SIMD_ALIGNED_TYPE(A0) tmp[n] = {  BOOST_PP_ENUM_PARAMS(n, a)  }; \
      return load<simd::native<A0, X> >(&tmp[0], 0);                  \
    }
    
    BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
  };
} } }

#endif

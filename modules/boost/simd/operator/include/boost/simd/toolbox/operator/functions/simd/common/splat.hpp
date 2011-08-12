//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_SPLAT_HPP_INCLUDED

#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/include/functions/load.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (unspecified_<A0>)
                              ((target_< simd_< unspecified_<A1>, X > >))
                            )
  {
    typedef typename A1::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<result_type>::type sA1;
      
      BOOST_SIMD_ALIGNED_TYPE(sA1) tmp[boost::simd::meta::cardinal_of<result_type>::value];
      for(int i = 0; i != boost::simd::meta::cardinal_of<result_type>::value; ++i)
        tmp[i] = a0;
      
      return load<result_type>(&tmp[0], 0);
    }
  };
} } }


#endif

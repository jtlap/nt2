//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_POSMIN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_POSMIN_HPP_INCLUDED
#include <boost/simd/toolbox/reduction/functions/posmin.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::posmin_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                        )
  {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename dispatch::meta::as_integer<stype, signed>::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      result_type p = 0;
      stype m = a0[0];
      for(size_t i=1; i < boost::simd::meta::cardinal_of<A0>::value; i++)// TODO UNROLL
      {
        if (m > a0[i]) { m = a0[i]; p = static_cast<result_type>(i); }
      }
      return p;
    }
  };
} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SCALAR_POSMAX_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SCALAR_POSMAX_HPP_INCLUDED
#include <boost/simd/toolbox/reduction/functions/posmax.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::posmax_, tag::cpu_,
                        (A0),
                        (scalar_<fundamental_<A0> > )
                       )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    inline result_type operator()(A0 const&)const 
    {
      return Zero<result_type>();
    }
  };
} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INT_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INT_SPLAT_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    template<boost::simd::int64_t I>
    struct Intpattern 
    { 
      template<class Target, class Dummy=void> 
      struct apply : meta::int_c<Target, Target(I)> {};  
    };
  }

  template<class Target, boost::simd::int64_t N> 
  inline Target integral_constant()
  {
    typename dispatch::make_functor< tag::Intpattern<N>, Target >::type callee;
    return callee( dispatch::meta::as_<Target>() );
  }
} }

#endif

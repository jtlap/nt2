//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_SIMD_COMMON_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <boost/simd/toolbox/boolean/functions/if_zero_else_one.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/one.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_zero_else_one_
                                      , tag::cpu_
                                      , (A0)(X)
                                      , ((simd_<unspecified_<A0>,X>))
                                )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else(a0, Zero<A0>(), One<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_zero_else_one_
                                      , tag::cpu_
                                      , (A0)(X)
                                      , ((simd_<logical_<A0>,X>))
                                )
  {
    typedef typename A0::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else(a0, Zero<result_type>(), One<result_type>());
    }
  };
} } }

#endif

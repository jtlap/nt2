//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_CTZ_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_CTZ_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/ctz.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/minusone.hpp>
#include <boost/simd/include/functions/simd/ffs.hpp>
#include <boost/simd/include/functions/simd/all.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::ctz_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, unsigned>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type t =  bitwise_cast<result_type>(a0);
      typedef typename meta::scalar_of<A0>::type s_type;

      BOOST_ASSERT_MSG( all(t), "ctz not defined for 0" );
      return minusone(boost::simd::ffs(t));
    }
  };
} } }


#endif

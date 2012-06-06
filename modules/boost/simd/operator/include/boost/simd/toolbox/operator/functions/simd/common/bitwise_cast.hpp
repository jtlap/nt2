//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/bitwise_cast.hpp>
#include <boost/mpl/assert.hpp>

namespace boost { namespace simd
{
  /* We avoid going through the dispatching system becauses it may
   * causes ICEs when A0 is a vector type */
  template<class A0, class T, class X>
  struct bitwise_cast_impl<A0, simd::native<T, X> >
  {
    typedef simd::native<T, X> Target;

    BOOST_MPL_ASSERT_MSG
    ( (sizeof(A0) == sizeof(Target))
    , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
    , (A0, Target)
    );

    typedef Target const& type;
    static BOOST_FORCEINLINE type call(A0 const& a0)
    {
      return reinterpret_cast<type>(a0);
    }
  };
} }

#endif

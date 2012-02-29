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

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, tag::cpu_, (A0)(A1)(X)
                            , (unspecified_<A0>)
                              ((target_<simd_<unspecified_<A1>, X> >))
                            )
  {
    typedef typename A1::type const& result_type;
   
    BOOST_MPL_ASSERT_MSG
    ( (sizeof(A0) == sizeof(typename A1::type))
    , BOOST_SIMD_TARGET_IS_NOT_SAME_SIZE_AS_SOURCE_IN_BITWISE_CAST
    , (A0&,typename A1::type&)
    );
      
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return reinterpret_cast<result_type>(a0);
    }
  };
} } }

#endif

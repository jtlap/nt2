//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/simd/toolbox/swar/functions/repeat_lower_half.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::repeat_lower_half_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_< unspecified_<A0>, X>))
                                    )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0) const
    {
      result_type that;
      const std::size_t  middle = meta::cardinal_of<A0>::value/2;
      for(std::size_t i=0;i<middle;++i)
      {
        that[i] = that[i+middle] = a0[i];
      }
      return that;
    }
  };
} } }

#endif

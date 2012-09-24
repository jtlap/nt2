//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_INTERLEAVE_ODD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_INTERLEAVE_ODD_HPP_INCLUDED

#include <boost/simd/toolbox/swar/functions/interleave_odd.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::interleave_odd_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< unspecified_<A0>, X>))
                                      ((simd_< unspecified_<A1>, X>))
                                    )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      result_type that;
      const std::size_t n = meta::cardinal_of<A0>::value;
      for(std::size_t i=0;i<n;i+= 2) 
      {
        that[i]   = a0[i+1];
        that[i+1] = a1[i+1];
      }
      return that;
    }
  };
} } }

#endif

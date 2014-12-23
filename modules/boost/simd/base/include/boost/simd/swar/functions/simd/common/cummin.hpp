//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_CUMMIN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_CUMMIN_HPP_INCLUDED

#include <boost/simd/swar/functions/cummin.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/scalar/min.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT         ( cummin_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = a0;
      for(size_t i=1; i!=meta::cardinal_of<A0>::value; ++i)
        that[i] = boost::simd::min(that[i-1], that[i]);
      return that;
    }
  };

   BOOST_DISPATCH_IMPLEMENT         ( cummin_, tag::cpu_
                                   , (A0)(A1)(X)
                                   , ((simd_<arithmetic_<A0>,X>))
                                     (unspecified_<A1>)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = a0;
      for(size_t i=meta::cardinal_of<A0>::value-1; i!=0; --i)
        that[i] = boost::simd::min(that[i-1], that[i]);
      return that;
    }
  };
} } }

#endif

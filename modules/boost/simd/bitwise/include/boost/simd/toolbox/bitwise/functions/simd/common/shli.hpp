//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_SHLI_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SIMD_COMMON_SHLI_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/shli.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/map.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shli_, tag::cpu_, (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename dispatch::meta::as_unsigned<A0>::type ntype;
      return simd::bitwise_cast<A0>( map( typename dispatch::make_functor<tag::shift_left_, A0>::type()
                                       , simd::bitwise_cast<ntype>(a0)
                                       , splat<ntype>(a1)
                                       )
                                  );
    }
  };
} } }

#endif

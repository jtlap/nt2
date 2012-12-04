//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_BITINTEGER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_BITINTEGER_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/bitinteger.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/is_positive.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitinteger_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type a00 = simd::bitwise_cast<result_type>(a0);
      return select(boost::simd::is_positive(a0), a00, Signmask<result_type>()-a00 );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitinteger_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return simd::bitwise_cast<result_type>(a0);
    }
  };
} } }


#endif

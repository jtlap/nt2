//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_MAXLEFTSHIFT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_MAXLEFTSHIFT_HPP_INCLUDED

#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

BOOST_SIMD_STD_CONSTANT_TAG(Maxleftshift)
BOOST_SIMD_STD_CONSTANT_DEF(Maxleftshift)

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::Maxleftshift, tag::cpu_,(A0)
                            , (target_< scalar_< arithmetic_<A0> > >)
                            )
  {
    typedef typename dispatch::meta::as_integer<A0,signed>::type  result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename meta::scalar_of<result_type>::type base_t;
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(base_t)*CHAR_BIT-1 );
      return boost::simd::splat<result_type>(value);
    }
  };
} } }

#endif

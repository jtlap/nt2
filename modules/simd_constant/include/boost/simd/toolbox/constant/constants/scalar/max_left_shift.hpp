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

#include <boost/simd/sdk/meta/from_bits.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/sdk/meta/adapted_traits.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace meta
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( tag::max_left_shift_, tag::cpu_,(A0)
                            , (target_< scalar_< arithmetic_<A0> > >)
                            )
  {
    typedef typename
            as_integer<typename strip<A0>::type::type,signed>::type  result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typedef typename meta::scalar_of<result_type>::type base_t;
      BOOST_STATIC_CONSTANT(std::size_t, value = sizeof(base_t)*CHAR_BIT-1 );
      return splat<result_type>(value);
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_INFINITES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_INFINITES_HPP_INCLUDED

#include <boost/simd/sdk/meta/from_bits.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/include/constants/properties.hpp>

#define BOOST_SIMD_LOCAL(NAME,DOUBLE,FLOAT,ARITH)                     \
namespace boost { namespace dispatch { namespace meta                 \
{                                                                     \
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)           \
                            , (target_< scalar_<double_<A0> > >)      \
                            )                                         \
  {                                                                   \
    typedef typename strip<A0>::type::type result_type;               \
                                                                      \
    BOOST_DISPATCH_FUNCTOR_CALL(1)                                    \
    {                                                                 \
      ignore_unused(a0);                                              \
      typename boost::simd::meta::from_bits<result_type>::type const  \
      that = {DOUBLE};                                                \
      return boost::simd::splat<result_type>(that.value);             \
    }                                                                 \
  };                                                                  \
                                                                      \
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)           \
                            , (target_< scalar_<float_<A0> > >)       \
                            )                                         \
  {                                                                   \
    typedef typename strip<A0>::type::type result_type;               \
                                                                      \
    BOOST_DISPATCH_FUNCTOR_CALL(1)                                    \
    {                                                                 \
      ignore_unused(a0);                                              \
      typename boost::simd::meta::from_bits<result_type>::type const  \
      that = {FLOAT};                                                 \
      return boost::simd::splat<result_type>(that.value);             \
    }                                                                 \
  };                                                                  \
                                                                      \
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)           \
                            , (target_< scalar_< arithmetic_<A0> > >) \
                            )                                         \
  {                                                                   \
    typedef typename strip<A0>::type::type result_type;               \
                                                                      \
    BOOST_DISPATCH_FUNCTOR_CALL(1)                                    \
    {                                                                 \
      ignore_unused(a0);                                              \
      return ARITH;                                                   \
    }                                                                 \
  };                                                                  \
} } }                                                                 \
/**/

BOOST_SIMD_LOCAL(boost::simd::tag::inf_   , 0x7FF0000000000000LL, 0x7F800000, boost::simd::Valmax<result_type>())
BOOST_SIMD_LOCAL(boost::simd::tag::m_inf_ , 0xFFF0000000000000LL, 0xFF800000, boost::simd::Valmin<result_type>())
BOOST_SIMD_LOCAL(boost::simd::tag::nan_   , 0xFFFFFFFFFFFFFFFFLL, 0xFFFFFFFF, boost::simd::Valmax<result_type>())

#undef BOOST_SIMD_LOCAL

#endif

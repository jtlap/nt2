//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_IEEE_SPEC_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_IEEE_SPEC_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

#define LOCAL_CONST(NAME, D, F, I)                                     \
namespace boost { namespace simd                                       \
{                                                                      \
  BOOST_SIMD_STD_CONSTANT_TAG(NAME)                                    \
  BOOST_SIMD_STD_CONSTANT_DEF(NAME)                                    \
                                                                       \
namespace ext                                                          \
{                                                                      \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::NAME,tag::cpu_,(A0) \
                          , (target_< scalar_< double_<A0> > > )       \
                          )                                            \
  {                                                                    \
    typedef typename dispatch::meta::as_integer < typename A0::type    \
      , signed                                                         \
      >::type result_type;                                             \
    BOOST_SIMD_FUNCTOR_CALL(1)                                         \
    {                                                                  \
      ignore_unused(a0);                                               \
      return boost::simd::splat<result_type>(D);                       \
    }                                                                  \
  };                                                                   \
                                                                       \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::NAME,tag::cpu_,(A0) \
                          , (target_< scalar_< float_<A0> > > )        \
                          )                                            \
  {                                                                    \
    typedef typename dispatch::meta::as_integer < typename A0::type    \
                              , signed                                 \
                              >::type result_type;                     \
    BOOST_SIMD_FUNCTOR_CALL(1)                                         \
    {                                                                  \
      ignore_unused(a0);                                               \
      return boost::simd::splat<result_type>(F);                       \
    }                                                                  \
  };                                                                   \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::NAME,tag::cpu_,(A0) \
                          , (target_< scalar_< integer_<A0> > > )      \
                          )                                            \
  {                                                                    \
    typedef typename dispatch::meta::as_integer < typename A0::type    \
                              , signed                                 \
                              >::type result_type;                     \
    BOOST_SIMD_FUNCTOR_CALL(1)                                         \
    {                                                                  \
      ignore_unused(a0);                                               \
      return boost::simd::splat<result_type>(I);                       \
    }                                                                  \
  };                                                                   \
} } }                                                                  \
/**/

LOCAL_CONST(Nbmantissabits ,                  52,         23, sizeof(A0));
LOCAL_CONST(Nbexponentbits ,                  11,          8, 0);
LOCAL_CONST(Maxexponent    ,                1023,        127, 0);
LOCAL_CONST(Minexponent    ,               -1022,       -126, 0);
LOCAL_CONST(Nbdigits       ,                  53,         24, 0);
LOCAL_CONST(Ldexpmask      ,0x7FF0000000000000ll, 0x7F800000, 0);


#undef LOCAL_CONST

#endif

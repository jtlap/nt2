//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_INFINITES_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_INFINITES_HPP_INCLUDED

#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/include/constants/real.hpp>

#define NT2_LOCAL(NAME,DOUBLE,FLOAT,ARITH)                            \
namespace nt2 { namespace meta                                        \
{                                                                     \
  NT2_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)                      \
                            , (target_< scalar_<double_<A0> > >)      \
                            )                                         \
  {                                                                   \
    typedef typename strip<A0>::type::type result_type;               \
                                                                      \
    NT2_FUNCTOR_CALL(1)                                               \
    {                                                                 \
      ignore_unused(a0);                                              \
      typename meta::from_bits<result_type>::type const               \
      that = {DOUBLE};                                                \
      return splat<result_type>(that.value);                          \
    }                                                                 \
  };                                                                  \
                                                                      \
  NT2_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)                      \
                            , (target_< scalar_<float_<A0> > >)       \
                            )                                         \
  {                                                                   \
    typedef typename strip<A0>::type::type result_type;               \
                                                                      \
    NT2_FUNCTOR_CALL(1)                                               \
    {                                                                 \
      ignore_unused(a0);                                              \
      typename meta::from_bits<result_type>::type const               \
      that = {FLOAT};                                                 \
      return splat<result_type>(that.value);                          \
    }                                                                 \
  };                                                                  \
                                                                      \
  NT2_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)                      \
                            , (target_< scalar_< arithmetic_<A0> > >) \
                            )                                         \
  {                                                                   \
    typedef typename strip<A0>::type::type result_type;               \
                                                                      \
    NT2_FUNCTOR_CALL(1)                                               \
    {                                                                 \
      ignore_unused(a0);                                              \
      return ARITH;                                                   \
    }                                                                 \
  };                                                                  \
} }                                                                   \
/**/

NT2_LOCAL(tag::inf_   , 0x7FF0000000000000LL, 0x7F800000, Valmax<result_type>())
NT2_LOCAL(tag::m_inf_ , 0xFFF0000000000000LL, 0xFF800000, Valmin<result_type>())
NT2_LOCAL(tag::nan_   , 0xFFFFFFFFFFFFFFFFLL, 0xFFFFFFFF, Valmax<result_type>())

#undef NT2_LOCAL

#endif

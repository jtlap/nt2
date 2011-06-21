//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_REAL_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_CONSTANTS_DETAILS_REAL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

//==============================================================================
// Custom local real functor
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_TPL( (tag::pattern<D,F>) , tag::cpu_
                                , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                                , (target_< scalar_<double_<A0> > >)
                                )
  {
    typedef typename strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const that = {D};
      return splat<result_type>(that.value);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION_TPL( (tag::pattern<D,F>) , tag::cpu_
                                , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                                , (target_< scalar_<float_<A0> > >)
                                )
  {
    typedef typename strip<A0>::type::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      typename meta::from_bits<result_type>::type const that = {F};
      return splat<result_type>(that.value);
    }
  };
} }

//==============================================================================
// Fill up the call needed for a real constant call
//==============================================================================
#define NT2_CONSTANT_MAKE_REAL(NAME,DOUBLE,FLOAT)                 \
namespace nt2 { namespace meta                                    \
{                                                                 \
  NT2_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)                  \
                            , (target_< scalar_<double_<A0> > >)  \
                            )                                     \
  {                                                               \
    typedef typename strip<A0>::type::type result_type;           \
                                                                  \
    NT2_FUNCTOR_CALL(1)                                           \
    {                                                             \
      ignore_unused(a0);                                          \
      typename meta::from_bits<result_type>::type const           \
      that = {DOUBLE};                                            \
      return splat<result_type>(that.value);                      \
    }                                                             \
  };                                                              \
                                                                  \
  NT2_FUNCTOR_IMPLEMENTATION(NAME,tag::cpu_,(A0)                  \
                            , (target_< scalar_<float_<A0> > >)   \
                            )                                     \
  {                                                               \
    typedef typename strip<A0>::type::type result_type;           \
                                                                  \
    NT2_FUNCTOR_CALL(1)                                           \
    {                                                             \
      ignore_unused(a0);                                          \
      typename meta::from_bits<result_type>::type const           \
      that = {FLOAT};                                             \
      return splat<result_type>(that.value);                      \
    }                                                             \
  };                                                              \
} }                                                               \
/**/

NT2_CONSTANT_MAKE_REAL(tag::m_half_      ,0xBFE0000000000000LL, 0xBF000000  )
NT2_CONSTANT_MAKE_REAL(tag::m_zero_      ,0x8000000000000000LL, 0x80000000  )
NT2_CONSTANT_MAKE_REAL(tag::half_        ,0x3FE0000000000000LL, 0x3F000000  )
NT2_CONSTANT_MAKE_REAL(tag::third_       ,0x3FD5555555555555LL, 0x3EAAAAAB  )
NT2_CONSTANT_MAKE_REAL(tag::quarter_     ,0x3FD0000000000000LL, 0x3E800000  )
NT2_CONSTANT_MAKE_REAL(tag::two_to_m10_  ,0x3F50000000000000LL, 0x3a800000  )
NT2_CONSTANT_MAKE_REAL(tag::two_to_nmb_  ,0x4330000000000000ll, 0x4b000000  )
NT2_CONSTANT_MAKE_REAL(tag::pi_          ,0x400921fb54442d18ll, 0x40490fdb  )
NT2_CONSTANT_MAKE_REAL(tag::split_factor_,0x41a0000000000000ll, 0x46000000  )
NT2_CONSTANT_MAKE_REAL(tag::sqrt_2_o_2_  ,0x3fe6a09e667f3bcdLL, 0x3f3504f3  )
NT2_CONSTANT_MAKE_REAL(tag::sqrt_2_      ,0x3ff6a09e667f3bccll, 0x3fb504f3  )
NT2_CONSTANT_MAKE_REAL(tag::gold_        ,0x3ff9e3779b97f4a8LL, 0x3fcf1bbd  )
NT2_CONSTANT_MAKE_REAL(tag::c_gold_      ,0x3fd8722191a02d61LL, 0x3ec3910d  )

#endif

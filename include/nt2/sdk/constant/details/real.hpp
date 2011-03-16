/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_REAL_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_REAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over pattern_<D,F>
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_TPL ( (tag::pattern<D,F>)
                          , tag::cpu_
                          , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                          , (target_< double_<A0> >)
                          )

NT2_REGISTER_DISPATCH_TPL ( (tag::pattern<D,F>)
                          , tag::cpu_
                          , (nt2::uint64_t D)(nt2::uint32_t F)(class A0)
                          , (target_< float_<A0> >)
                          )

////////////////////////////////////////////////////////////////////////////////
// Custom local real functor
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<nt2::uint64_t D, nt2::uint32_t F, class Dummy>
  struct  call< tag::pattern<D,F>(tag::target_<tag::double_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<double>::type const that = {D};
      return splat<typename A0::type>(that.value);
    }
  };

  template<nt2::uint64_t D, nt2::uint32_t F, class Dummy>
  struct  call< tag::pattern<D,F>(tag::target_<tag::float_>)
              , tag::cpu_
              , Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This, class Target>
    struct result<This(Target)> : meta::strip<Target>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<float>::type const that = {F};
      return splat<typename A0::type>(that.value);
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Fill up the call needed for a real constant call
////////////////////////////////////////////////////////////////////////////////
#define NT2_CONSTANT_MAKE_REAL(NAME,DOUBLE,FLOAT)                       \
NT2_REGISTER_DISPATCH(NAME,tag::cpu_,(A0), (target_< double_<A0> >) )   \
NT2_REGISTER_DISPATCH(NAME,tag::cpu_,(A0), (target_< float_<A0> >) )    \
namespace nt2 { namespace ext                                           \
{                                                                       \
  template<class Dummy>                                                 \
  struct call<NAME(tag::target_<tag::double_>),Dummy> : callable        \
  {                                                                     \
    template<class Sig> struct result;                                  \
    template<class This,class A0>                                       \
    struct  result<This(A0)> : meta::strip<A0>::type {};                \
                                                                        \
    NT2_FUNCTOR_CALL(1)                                                 \
    {                                                                   \
      meta::from_bits<double>::type const that = {DOUBLE};              \
      return splat<typename A0::type>(that.value);                      \
    }                                                                   \
  };                                                                    \
                                                                        \
  template<class Dummy>                                                 \
  struct call<NAME(tag::target_<tag::float_>),Dummy> : callable         \
  {                                                                     \
    template<class Sig> struct result;                                  \
    template<class This,class A0>                                       \
    struct  result<This(A0)> : meta::strip<A0>::type {};                \
                                                                        \
    NT2_FUNCTOR_CALL(1)                                                 \
    {                                                                   \
      meta::from_bits<float>::type const that = {FLOAT};                \
      return splat<typename A0::type>(that.value);                      \
    }                                                                   \
  };                                                                    \
} }                                                                     \
/**/

////////////////////////////////////////////////////////////////////////////////
// Real only constants
////////////////////////////////////////////////////////////////////////////////

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
//NT2_CONSTANT_MAKE_REAL(tag::nan_         ,0xFFFFFFFFFFFFFFFFLL, 0xFFFFFFFF  )

#endif

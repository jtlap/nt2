/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_REAL_HPP_INCLUDED
#define NT2_SDK_CONSTANT_REAL_HPP_INCLUDED
////////////////////////////////////////////////////////////////////////////////
// Make True and False
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/sdk/constant/details/real_constant.hpp>

namespace nt2 { namespace constants
{
  struct nan_         {};
  struct m_half_      {};
  struct m_zero_      {};
  struct half_        {};
  struct third_       {};
  struct quarter_     {};
  struct two_to_m10_  {};
  struct two_to_nmb_  {};
  struct pi_          {};
  struct split_factor_{};
  struct sqrt_2_o_2_  {};
  struct gold_        {};
  struct c_gold_      {};
}  }

namespace nt2
{
  NT2_CONSTANT_IMPLEMENTATION(constants::nan_         , Nan     )
  NT2_CONSTANT_IMPLEMENTATION(constants::m_half_      , Mhalf   )
  NT2_CONSTANT_IMPLEMENTATION(constants::m_zero_      , Mzero   )
  NT2_CONSTANT_IMPLEMENTATION(constants::half_        , Half    )
  NT2_CONSTANT_IMPLEMENTATION(constants::third_       , Third   )
  NT2_CONSTANT_IMPLEMENTATION(constants::quarter_     , Quarter )
  NT2_CONSTANT_IMPLEMENTATION(constants::two_to_m10_  , Twotom10)
  NT2_CONSTANT_IMPLEMENTATION(constants::two_to_nmb_  , Two2nmb )
  NT2_CONSTANT_IMPLEMENTATION(constants::pi_          , Pi      )
  NT2_CONSTANT_IMPLEMENTATION(constants::split_factor_, Splitfactor)
  NT2_CONSTANT_IMPLEMENTATION(constants::sqrt_2_o_2_  , Sqrt_2o_2)
  NT2_CONSTANT_IMPLEMENTATION(constants::gold_        , Gold    )
  NT2_CONSTANT_IMPLEMENTATION(constants::c_gold_      , Cgold   )
}

////////////////////////////////////////////////////////////////////////////////
// Custom local real functor
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class Tag,class Category,class Info>
  struct  dispatch<Tag,tag::constant_(Category),Info>
  {
    template<class T> struct apply : meta::scalar_of<T> {};
  };

  template< uint64_t Double, uint32_t Float, class Category,class Info>
  struct  call< details::pattern<Double,Float>
              , tag::constant_(Category),double,Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<double>::type const that = {Double};
      return splat<typename A0::type>(that.value);
    }
  };

  template< uint64_t Double, uint32_t Float, class Category,class Info>
  struct  call< details::pattern<Double,Float>
              , tag::constant_(Category),float,Info
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::strip<A0>::type {};

    NT2_FUNCTOR_CALL(1)
    {
      meta::from_bits<float>::type const that = {Float};
      return splat<typename A0::type>(that.value);
    }
  };
} }

namespace nt2
{
  template<class Target, uint64_t D, uint32_t F> inline
  typename meta::enable_call<details::pattern<D,F>(meta::as_<Target>)>::type
  real_constant()
  {
    nt2::functors::functor< details::pattern<D,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  template<class Target, uint32_t F> inline
  typename meta::enable_call<details::pattern<0,F>(meta::as_<Target>)>::type
  single_constant()
  {
    nt2::functors::functor< details::pattern<0,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  template<class Target, uint64_t D> inline
  typename meta::enable_call<details::pattern<D,0>(meta::as_<Target>)>::type
  double_constant()
  {
    nt2::functors::functor< details::pattern<D,0> > callee;
    return callee( nt2::meta::as_<Target>() );
  }
}
////////////////////////////////////////////////////////////////////////////////
// Fill up the call needed for a real constant call
////////////////////////////////////////////////////////////////////////////////
#define NT2_CONSTANT_MAKE_REAL(NAME,DOUBLE,FLOAT)                       \
namespace nt2 { namespace functors                                      \
{                                                                       \
  template<class Category,class Info>                                   \
  struct call<NAME,tag::constant_(Category),double,Info> : callable     \
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
  template<class Category,class Info>                                   \
  struct call<NAME,tag::constant_(Category),float,Info> : callable      \
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

NT2_CONSTANT_MAKE_REAL(constants::m_half_      ,0xBFE0000000000000LL, 0xBF000000  )
NT2_CONSTANT_MAKE_REAL(constants::m_zero_      ,0x8000000000000000LL, 0x80000000  )
NT2_CONSTANT_MAKE_REAL(constants::half_        ,0x3FE0000000000000LL, 0x3F000000  )
NT2_CONSTANT_MAKE_REAL(constants::third_       ,0x3FD5555555555555LL, 0x3EAAAAAB  )
NT2_CONSTANT_MAKE_REAL(constants::quarter_     ,0x3FD0000000000000LL, 0x3E800000  )
NT2_CONSTANT_MAKE_REAL(constants::two_to_m10_  ,0x3F50000000000000LL, 0x3a800000  )
NT2_CONSTANT_MAKE_REAL(constants::two_to_nmb_  ,0x4330000000000000ll, 0x4b000000  )
NT2_CONSTANT_MAKE_REAL(constants::pi_          ,0x400921fb54442d18ll, 0x40490fdb  )
NT2_CONSTANT_MAKE_REAL(constants::split_factor_,0x41a0000000000000ll, 0x46000000  )
NT2_CONSTANT_MAKE_REAL(constants::sqrt_2_o_2_  ,0x3fe6a09e667f3bcdLL, 0x3f3504f3  )
NT2_CONSTANT_MAKE_REAL(constants::gold_        ,0x3ff9e3779b97f4a8LL, 0x3fcf1bbd  )
NT2_CONSTANT_MAKE_REAL(constants::c_gold_      ,0x3fd8722191a02d61LL, 0x3ec3910d  )
NT2_CONSTANT_MAKE_REAL(constants::nan_         ,0xFFFFFFFFFFFFFFFFLL, 0xFFFFFFFF  )

#endif

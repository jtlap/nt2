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
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/constant/constant.hpp>
#include <nt2/sdk/constant/infinites.hpp>

namespace nt2 { namespace tag
{
  struct pi_          {};
  //  struct nan_         {};
  struct sqrt_2_o_2_  {}; struct sqrt_2_      {};
  struct gold_        {}; struct c_gold_      {};
  struct m_half_      {}; struct m_zero_      {};
  struct half_        {}; struct third_       {}; struct quarter_     {};
  struct two_to_m10_  {}; struct two_to_nmb_  {}; struct split_factor_{};

  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<nt2::uint64_t D, nt2::uint32_t F> struct pattern {};
} }

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns depending on target type
  //////////////////////////////////////////////////////////////////////////////
  template< class Target
          , nt2::uint64_t Value
          , class Select = typename meta::scalar_of<Target>::type
          >
  struct  pattern;

  template<class Target, nt2::uint64_t Value>
  struct pattern<Target, Value, float >
  {
    typedef tag::pattern<0,Value> type;
  };

  template<class Target, nt2::uint64_t Value>
  struct pattern<Target, Value, double >
  {
    typedef tag::pattern<Value,0> type;
  };
}}

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // Basic named constant
  //////////////////////////////////////////////////////////////////////////////
  //  NT2_CONSTANT_IMPLEMENTATION(tag::nan_         , Nan         )
  NT2_CONSTANT_IMPLEMENTATION(tag::m_half_      , Mhalf       )
  NT2_CONSTANT_IMPLEMENTATION(tag::m_zero_      , Mzero       )
  NT2_CONSTANT_IMPLEMENTATION(tag::half_        , Half        )
  NT2_CONSTANT_IMPLEMENTATION(tag::third_       , Third       )
  NT2_CONSTANT_IMPLEMENTATION(tag::quarter_     , Quarter     )
  NT2_CONSTANT_IMPLEMENTATION(tag::two_to_m10_  , Twotom10    )
  NT2_CONSTANT_IMPLEMENTATION(tag::two_to_nmb_  , Two2nmb     )
  NT2_CONSTANT_IMPLEMENTATION(tag::pi_          , Pi          )
  NT2_CONSTANT_IMPLEMENTATION(tag::split_factor_, Splitfactor )
  NT2_CONSTANT_IMPLEMENTATION(tag::sqrt_2_o_2_  , Sqrt_2o_2   )
  NT2_CONSTANT_IMPLEMENTATION(tag::sqrt_2_      , Sqrt_2      )
  NT2_CONSTANT_IMPLEMENTATION(tag::gold_        , Gold        )
  NT2_CONSTANT_IMPLEMENTATION(tag::c_gold_      , Cgold       )

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::uint64_t D, nt2::uint32_t F> inline
  typename meta::enable_call<tag::pattern<D,F>(meta::as_<Target>)>::type
  real_constant()
  {
    nt2::functor< tag::pattern<D,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of float
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::uint32_t F> inline
  typename meta::enable_call<tag::pattern<0,F>(meta::as_<Target>)>::type
  single_constant()
  {
    nt2::functor< tag::pattern<0,F> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of double
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, nt2::uint64_t D> inline
  typename meta::enable_call<tag::pattern<D,0>(meta::as_<Target>)>::type
  double_constant()
  {
    nt2::functor< tag::pattern<D,0> > callee;
    return callee( nt2::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns dependant on target type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, uint64_t V> inline
  typename  meta
          ::enable_call<typename details::pattern<T,V>::type(meta::as_<T>)>::type
  Const()
  {
    nt2::functor< typename details::pattern<T,V>::type > callee;
    return callee( nt2::meta::as_<T>() );
  }
}

#include <nt2/sdk/constant/details/real.hpp>

#endif

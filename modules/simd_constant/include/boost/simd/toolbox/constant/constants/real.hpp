//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_REAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_REAL_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Make some real based constants
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>
#include <boost/simd/sdk/constant/common.hpp>

namespace boost { namespace dispatch { namespace tag
{
  struct pi_          {};
  struct sqrt_2_o_2_  {}; struct sqrt_2_      {};
  struct gold_        {}; struct c_gold_      {};
  struct m_half_      {}; struct m_zero_      {};
  struct half_        {}; struct third_       {}; struct quarter_     {};
  struct two_to_m10_  {}; struct two_to_nmb_  {}; struct split_factor_{};

  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<boost::simd::uint64_t D, boost::simd::uint32_t F> struct pattern {};
} } }

namespace boost { namespace simd { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Small type to gather real value bit patterns depending on target type
  //////////////////////////////////////////////////////////////////////////////
  template< class Target
          , boost::simd::uint64_t Value
          , class Select = typename meta::scalar_of<Target>::type
          >
  struct  pattern;

  template<class Target, boost::simd::uint64_t Value>
  struct pattern<Target, Value, float >
  {
    typedef boost::dispatch::tag::pattern<0,Value> type;
  };

  template<class Target, boost::simd::uint64_t Value>
  struct pattern<Target, Value, double >
  {
    typedef boost::dispatch::tag::pattern<Value,0> type;
  };
} } }

namespace boost { namespace simd 
{
  //////////////////////////////////////////////////////////////////////////////
  // Basic named constant
  //////////////////////////////////////////////////////////////////////////////
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::m_half_      , Mhalf       )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::m_zero_      , Mzero       )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::half_        , Half        )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::third_       , Third       )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::quarter_     , Quarter     )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::two_to_m10_  , Twotom10    )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::two_to_nmb_  , Two2nmb     )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::pi_          , Pi          )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::split_factor_, Splitfactor )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::sqrt_2_o_2_  , Sqrt_2o_2   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::sqrt_2_      , Sqrt_2      )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::gold_        , Gold        )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::dispatch::tag::c_gold_      , Cgold       )

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D, boost::simd::uint32_t F> inline
  typename boost::dispatch::meta::call<boost::dispatch::tag::pattern<D,F >(boost::dispatch::meta::as_<Target>)>::type
  real_constant()
  {
    boost::dispatch::functor< tag::pattern<D,F> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of float
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint32_t F> inline
  typename boost::dispatch::meta::call<boost::dispatch::tag::pattern<0,F >(boost::dispatch::meta::as_<Target>)>::type
  single_constant()
  {
    boost::dispatch::functor< tag::pattern<0,F> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns of double
  //////////////////////////////////////////////////////////////////////////////
  template<class Target, boost::simd::uint64_t D> inline
  typename boost::dispatch::meta::call<boost::dispatch::tag::pattern<D,0 >(boost::dispatch::meta::as_<Target>)>::type
  double_constant()
  {
    boost::dispatch::functor< tag::pattern<D,0> > callee;
    return callee( boost::dispatch::meta::as_<Target>() );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Generic real value splatter from a bit patterns dependant on target type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, uint64_t V> inline
  typename boost::dispatch::meta::call<typename details::pattern<T,V>::type(boost::dispatch::meta::as_<T>)>::type
  Const()
  {
    boost::dispatch::functor< typename details::pattern<T,V>::type > callee;
    return callee( boost::dispatch::meta::as_<T>() );
  }
} }

#include <boost/simd/toolbox/constant/constants/scalar/real.hpp>
#include <boost/simd/toolbox/constant/constants/simd/all/real.hpp>

#endif

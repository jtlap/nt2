/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_TIMING_CTIC_HPP_INCLUDED
#define BOOST_SIMD_SDK_TIMING_CTIC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Coutn cycles
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/timing/now.hpp>
#include <boost/simd/sdk/timing/timer.hpp>

namespace boost { namespace simd {  namespace details
{
  struct cycle_based_timer
  {
    static void Print(const cycles_t& val);
    static inline cycles_t Time() { return read_cycles(); }
  };

  counter<cycles_t,cycle_based_timer>  const cycle_timer = {};
} } }

namespace boost { namespace simd { namespace time
{
  inline void ctic() { details::cycle_timer.tic(); }

  inline details::cycles_t  ctoc( bool display = true)
  {
    return details::cycle_timer.toc(display);
  }
} } }

namespace boost { namespace simd
{
  // Convenience namespace injection from time:: into boost::simd::
  using time::ctic;
  using time::ctoc;
} }

#endif

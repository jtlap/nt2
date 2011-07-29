/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_TIMING_CYCLE_TIMER_HPP_INCLUDED
#define BOOST_SIMD_SDK_TIMING_CYCLE_TIMER_HPP_INCLUDED

#include <boost/simd/sdk/timing/ctic.hpp>
#include <boost/simd/sdk/timing/impl/cycles.hpp>

namespace boost { namespace simd { namespace time
{
  struct cycle_timer
  {
     cycle_timer(boost::simd::details::cycles_t& e, bool d = true) : elapsed(e), display(d) { ctic(); }
    ~cycle_timer() { elapsed = ctoc(display); }

    boost::simd::details::cycles_t& elapsed;
    bool display;
  };
} } }

#endif

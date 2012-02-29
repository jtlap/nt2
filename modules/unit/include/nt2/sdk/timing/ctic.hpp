/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_TIMING_CTIC_HPP_INCLUDED
#define NT2_SDK_TIMING_CTIC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Coutn cycles
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/timing/timer.hpp>

namespace nt2 { namespace details
{
  struct cycle_based_timer
  {
    static void Print(const cycles_t& val);
    static inline cycles_t Time() { return read_cycles(); }
  };

  counter<cycles_t,cycle_based_timer>  const cycle_timer = {};
} }

namespace nt2 { namespace time
{
  inline void ctic() { details::cycle_timer.tic(); }

  inline details::cycles_t  ctoc( bool display = true)
  {
    return details::cycle_timer.toc(display);
  }
} }

namespace nt2
{
  // Convenience namespace injection from time:: into nt2::
  using time::ctic;
  using time::ctoc;
}

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_TIMING_TIC_HPP_INCLUDED
#define NT2_SDK_TIMING_TIC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/timing/timer.hpp>
#include <nt2/sdk/timing/now.hpp>

namespace nt2 { namespace details
{
  struct second_based_timer
  {
    static void Print(const double& val);
    static inline double  Time() { return details::now(); }
  };

  counter<double,second_based_timer> const sec_timer = {};
} }

namespace nt2 { namespace time
{
  inline void tic() { details::sec_timer.tic(); }

  inline double  toc( bool display = true)
  {
    return details::sec_timer.toc(display);
  }
} }

namespace nt2
{
  // Convenience namespace injection from time:: into nt2::
  using time::tic;
  using time::toc;
}

#endif

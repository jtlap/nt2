/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_TIMING_TIC_HPP_INCLUDED
#define BOOST_SIMD_SDK_TIMING_TIC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/timing/timer.hpp>
#include <boost/simd/sdk/timing/now.hpp>

namespace boost { namespace simd { namespace details
{
  struct second_based_timer
  {
    static void Print(const double& val);
    static inline double  Time() { return details::now(); }
  };

  counter<double,second_based_timer> const sec_timer = {};
} } }

namespace boost { namespace simd { namespace time
{
  inline void tic() { details::sec_timer.tic(); }

  inline double  toc( bool display = true)
  {
    return details::sec_timer.toc(display);
  }
} } }

namespace boost { namespace simd
{
  // Convenience namespace injection from time:: into boost::simd::
  using time::tic;
  using time::toc;
} }

#endif

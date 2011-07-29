/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_TIMING_IMPL_GETTIMEOFDAY_HPP_INCLUDED
#define BOOST_SIMD_SDK_TIMING_IMPL_GETTIMEOFDAY_HPP_INCLUDED

#if !defined(BOOST_SIMD_TIMING_DETECTED)

#if defined( BOOST_HAS_GETTIMEOFDAY )

#define BOOST_SIMD_TIMING_DETECTED
#include <sys/time.h>
#include <boost/cstdint.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    inline double now()
    {
      struct timeval tp;
      gettimeofday(&tp,NULL);
      return double(tp.tv_sec) + double(tp.tv_usec)*1e-6;
    }
  }
} }
#endif
#endif

#endif

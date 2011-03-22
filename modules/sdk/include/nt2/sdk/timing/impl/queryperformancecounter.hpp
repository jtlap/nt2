/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_TIMING_IMPL_QUERYPERFORMANCECOUNTER_HPP_INCLUDED
#define NT2_SDK_TIMING_IMPL_QUERYPERFORMANCECOUNTER_HPP_INCLUDED

#if !defined(NT2_TIMING_DETECTED)

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)

#define NT2_TIMING_DETECTED
#if !defined(VC_EXTRALEAN)
#define VC_EXTRALEAN
#endif

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <boost/cstdint.hpp>

namespace nt2
{
  namespace details
  {
    inline double now()
    {
      union pli { LARGE_INTEGER li; double d; };
      pli freq,t;
      QueryPerformanceFrequency( &freq.li );
      QueryPerformanceCounter( &t.li );
      return (((t.d*1000000000)/freq.d)/1000000000);
    }
  }
}
#endif
#endif

#endif

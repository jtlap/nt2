//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32))
//==============================================================================
// QueryPerformanceCounter systems
//==============================================================================
#include <windows.h>

namespace nt2
{
  static unsigned long long get_timer_resolution()
  {
    LARGE_INTEGER frequency;
    BOOST_VERIFY( ::QueryPerformanceFrequency( &frequency ) );

    return frequency.QuadPart;
  }

  static double const timer_ticks_per_microsecond( get_timer_resolution() / 1000000.0 );

  NT2_SDK_TIMING_DECL time_quantum_t time_quantum()
  {
    // http://support.microsoft.com/kb/172338
    BOOST_ASSERT_MSG
    (
      timer_ticks_per_microsecond == ( get_timer_resolution() / 1000000.0 ),
      "MSDN explicitly states for QueryPerformanceFrequency: "
      "'The frequency cannot change while the system is running.'"
    );
    /// \todo Also add http://msdn.microsoft.com/en-us/library/ms684208(VS.85).aspx.
    ///                                   (18.10.2012.) (Domagoj Saric)
    /// \todo Assert these no longer apply:
    /// http://support.microsoft.com/kb/274323 (http://bullet.googlecode.com/svn/tags/bullet-2.72-release/src/LinearMath/btQuickprof.h)
    /// http://www.virtualdub.org/blog/pivot/entry.php?id=106.
    ///                                   (18.10.2012.) (Domagoj Saric)
    #ifdef __GNUC__
    __asm__ ("" :::"memory" );
    #else
    ::_ReadWriteBarrier();
    #endif
    LARGE_INTEGER result;
    BOOST_VERIFY( ::QueryPerformanceCounter( &result ) );
    #ifdef __GNUC__
    __asm__ ("" :::"memory" );
    #else
    ::_ReadWriteBarrier();
    #endif
    return result.QuadPart;
  }
}

//==============================================================================
// gettimeofday systems
//==============================================================================
#elif defined( BOOST_HAS_GETTIMEOFDAY )
#include <sys/time.h>

namespace nt2
{
  static double const timer_ticks_per_microsecond( 1 );

  NT2_SDK_TIMING_DECL time_quantum_t time_quantum()
  {
    /// \todo Investigate:
    /// http://www.gamasutra.com/view/feature/171774/getting_high_precision_timing_on_.php
    /// http://pubs.opengroup.org/onlinepubs/009695399/functions/clock_gettime.html
    /// http://gruntthepeon.free.fr/blog/index.php/2011/05/30/56-clock_gettime-is-slow
    ///                                     (18.10.2012.) (Domagoj Saric)
    timeval tp;
    BOOST_VERIFY( ::gettimeofday( &tp, NULL ) == 0 );
    return static_cast<time_quantum_t>( tp.tv_sec ) * 1000000 + tp.tv_usec;
  }
}

//==============================================================================
// Other systems
//==============================================================================
#else
#include <ctime>

namespace nt2
{
    // TODO: Invesitgate boost/std::chrono. (18.10.2012.) (Domagoj Saric)
    static double const timer_ticks_per_microsecond( CLOCKS_PER_SEC / 1000000.0 );

    NT2_SDK_TIMING_DECL time_quantum_t time_quantum() { return std::clock(); }
}
#endif

namespace nt2
{
  NT2_SDK_TIMING_DECL double now()
  {
    return to_microseconds( time_quantum() ) / 1000000.;
  }

  static microseconds_t const
  inverse_timer_ticks_per_ms( static_cast<microseconds_t>(1)
                            / timer_ticks_per_microsecond
                            );

  NT2_SDK_TIMING_DECL microseconds_t to_microseconds( time_quantum_t const t )
  {
    return static_cast<microseconds_t>(t) * inverse_timer_ticks_per_ms;
  }

  NT2_SDK_TIMING_DECL time_quantum_t to_timequantums( microseconds_t const t )
  {
    return static_cast<time_quantum_t>( t * inverse_timer_ticks_per_ms);
  }
}

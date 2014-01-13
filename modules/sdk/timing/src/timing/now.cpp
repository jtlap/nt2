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
#include <nt2/sdk/timing/linux_perf_event.hpp>
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

  static unsigned long long const timer_resolution           ( get_timer_resolution()                                        );
  static double             const timer_ticks_per_microsecond( static_cast<signed long long>( timer_resolution ) / 1000000.0 );

  NT2_SDK_TIMING_DECL time_quantum_t time_quantum()
  {
    // http://support.microsoft.com/kb/172338
    BOOST_ASSERT_MSG
    (
      timer_resolution == get_timer_resolution(),
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

#ifdef BOOST_SIMD_OS_LINUX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
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
    return static_cast<time_quantum_t>( t * timer_ticks_per_microsecond );
  }

  NT2_SDK_TIMING_DECL unsigned long max_cpu_freq = 1000000000; // 1Ghz by default

  struct max_cpu_freq_scoped
  {
    max_cpu_freq_scoped()
    {
      #ifdef BOOST_SIMD_OS_LINUX
      int fd = ::open("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", O_RDONLY);
      if(fd < 0)
        return;

      char buffer[256];
      ssize_t sz = ::read(fd, buffer, sizeof buffer);
      ::close(fd);
      if(sz < 0)
        return;

      buffer[sz-1] = '\0';
      max_cpu_freq = ::strtoul(buffer, NULL, 10)*1000;
      #endif
    }
  };

  static max_cpu_freq_scoped max_cpu_freq_init;

  NT2_SDK_TIMING_DECL double get_cpu_freq ()
  {
    return((double)max_cpu_freq/1000000000);
  }
}

#ifdef BOOST_SIMD_OS_LINUX
#ifdef __ANDROID__
#include "perf_event.h"
#else
#include <linux/perf_event.h>
#endif
#include <linux/version.h>
#include <sys/syscall.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

namespace nt2
{
  namespace linux_
  {
    NT2_SDK_TIMING_DECL int perf_event_hw_cycles;

    struct perf_event_hw_cycles_scoped
    {
      perf_event_hw_cycles_scoped()
      {
        struct perf_event_attr attr;
        ::memset(&attr, 0, sizeof(attr));
        attr.type = PERF_TYPE_HARDWARE;
        attr.size = sizeof(attr);
        #if LINUX_VERSION_CODE >= KERNEL_VERSION(3,3,0)
        attr.config = PERF_COUNT_HW_REF_CPU_CYCLES;
        #else
        attr.config = PERF_COUNT_HW_CPU_CYCLES;
        #endif
        attr.exclude_kernel = 1;
        attr.exclude_hv = 1;
        //attr.exclude_idle = 1;
        perf_event_hw_cycles = ::syscall(__NR_perf_event_open, &attr, 0, -1, -1, 0);
        if(perf_event_hw_cycles == -1)
        {
          if(errno != ENOENT) // ENOENT occurs on some virtualization systems
            ::perror("perf_event_hw_cycles init failed");
        }
      }

      ~perf_event_hw_cycles_scoped()
      {
        ::close(perf_event_hw_cycles);
      }
    };

    static perf_event_hw_cycles_scoped perf_event_hw_cycles_init;
  }
}
#endif

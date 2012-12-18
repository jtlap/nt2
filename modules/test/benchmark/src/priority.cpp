//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/assert.hpp>
#include <boost/config.hpp>

#if defined( BOOST_HAS_GETTIMEOFDAY )
#include <sys/time.h>
#include <sys/resource.h>

namespace nt2 { namespace details
{
  struct priority_booster
  {
    priority_booster()
    {
      // This require sudo privilege under common linux to kicks in
      ::setpriority(PRIO_PROCESS      , 0, -20 );
      #ifdef __APPLE__
      ::setpriority(PRIO_DARWIN_THREAD, 0, -20 );
      #endif
    }
  };
} }
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#include <windows.h>

namespace nt2 { namespace details
{
  struct priority_booster
  {
    priority_booster()
    {
      // TODO: Try and disable SpeedStep/TurboBoost/<whatever> or at
      // least add some dummy form of initial burn-in to force the CPU
      // frequency to max out before measurements begin.
      //                               (23.10.2012.) (Domagoj Saric)

      BOOST_VERIFY(::SetProcessAffinityMask( ::GetCurrentProcess(), 1));

      BOOST_VERIFY( ::SetPriorityClass( ::GetCurrentProcess()
                                      , REALTIME_PRIORITY_CLASS
                                      )
                  );

      BOOST_VERIFY( ::SetThreadPriority ( ::GetCurrentThread ()
                                        , THREAD_PRIORITY_TIME_CRITICAL
                                        )
                  );
    }
  };
} }
#else
namespace nt2 { namespace details
{
  struct priority_booster {};
} }
#endif

namespace nt2 { namespace details
{
  static priority_booster const priority_booster;
} }

//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/config/types.hpp>

//==============================================================================
// gettimeofday systems
//==============================================================================
#if defined( BOOST_HAS_GETTIMEOFDAY )
#include <sys/time.h>

namespace nt2 { namespace details
{
  NT2_UNIT_DECL double now()
  {
    struct timeval tp;
    gettimeofday(&tp,NULL);
    return double(tp.tv_sec) + double(tp.tv_usec)*1e-6;
  }
} }

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
//==============================================================================
// QueryPerformanceCounter systems
//==============================================================================
#include <windows.h>

namespace nt2 { namespace details
{
  NT2_UNIT_DECL double now()
  {
    union pli { LARGE_INTEGER li; double d; };
    pli freq,t;
    QueryPerformanceFrequency( &freq.li );
    QueryPerformanceCounter( &t.li );
    return (((t.d*1000000000)/freq.d)/1000000000);
  }
} }

#else
//==============================================================================
// Other systems
//==============================================================================
#include <ctime>

namespace nt2 { namespace details
{
  NT2_UNIT_DECL double now() { return std::clock()/double(CLOCKS_PER_SEC); }
} }

#endif

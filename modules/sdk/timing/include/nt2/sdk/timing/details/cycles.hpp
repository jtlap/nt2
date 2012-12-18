//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TIMING_DETAILS_CYCLES_HPP_INCLUDED
#define NT2_SDK_TIMING_DETAILS_CYCLES_HPP_INCLUDED

#include <boost/config.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/simd/sdk/config/arch.hpp>

#if    (defined(__GNUC__)     || defined(__ICC)        )      \
    && defined(BOOST_SIMD_ARCH_X86)
namespace nt2
{
  // INTERNAL ONLY
  // Read cycles counter using rdtsc
  // X86 non-MSVC compiler have to use this asm block
  inline cycles_t read_cycles()
  {
    /// \todo Use __builtin_readcyclecounter with Clang.
    ///                                     (24.10.2012.) (Domagoj Saric)
    nt2::uint32_t hi = 0, lo = 0;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi) : : "memory" );
    cycles_t that =   static_cast<cycles_t>(lo)
                  | ( static_cast<cycles_t>(hi)<<32 );
    return that;
  }
}
#elif defined(BOOST_MSVC)
#include <intrin.h>

namespace nt2
{
  // INTERNAL ONLY
  // Read cycles counter using rdtsc
  // MSVC compiler has a proper intrinsic
  inline cycles_t read_cycles()
  {
      /// \todo Also add http://msdn.microsoft.com/en-us/library/ms684208(VS.85).aspx.
      ///                                     (18.10.2012.) (Domagoj Saric)
      // http://www.strchr.com/performance_measurements_with_rdtsc
      // http://www.ccsl.carleton.ca/~jamuir/rdtscpm1.pdf
    #if defined( _M_AMD64 )
        __faststorefence();
    #elif defined( _M_IX86 )
        long cpu_barrier; __asm xchg cpu_barrier, eax;
    #endif // _M_AMD64
      ::_ReadWriteBarrier();
      /// \todo Consider the rdtscp instruction/intrinsic.
      ///                                     (02.11.2012.) (Domagoj Saric)
      cycles_t const result( ::__rdtsc() );
      ::_ReadWriteBarrier();
      return result;
  }
}
#elif  (defined(__GNUC__)      && defined(BOOST_SIMD_ARCH_POWERPC)) \
    || (defined(__MWERKS__)    && defined(macintosh) )              \
    || (defined(__IBM_GCC_ASM) && defined(BOOST_SIMD_ARCH_POWERPC))
namespace nt2
{
  // INTERNAL ONLY
  // Read cycles counter using mftbu on PowerPC
  inline cycles_t read_cycles()
  {
    nt2::uint32_t tbl, tbu0, tbu1;

    do
    {
      __asm__ __volatile__ ("mftbu %0" : "=r"(tbu0));
      __asm__ __volatile__ ("mftb %0"  : "=r"(tbl));
      __asm__ __volatile__ ("mftbu %0" : "=r"(tbu1));
    } while (tbu0 != tbu1);

    return (cycles_t)((((boost::uint64_t)tbu0) << 32) | tbl);
  }
}

#elif !defined(_WIN32)
#include <nt2/sdk/timing/now.hpp>
#include <sys/times.h>

namespace nt2
{
  // INTERNAL ONLY
  // Read cycles counter using an approximation of the frequency
  inline cycles_t read_cycles()
  {
    details::now_in_seconds() * sysconf(_SC_CLK_TCK);
  }
}

#endif
#endif

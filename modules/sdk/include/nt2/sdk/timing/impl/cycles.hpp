/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_TIMING_IMPL_CYCLES_HPP_INCLUDED
#define NT2_SDK_TIMING_IMPL_CYCLES_HPP_INCLUDED

#include <nt2/sdk/config/arch.hpp>
#include <nt2/sdk/config/types.hpp>

namespace nt2
{
  namespace details
  {
  #if    (defined(__GNUC__)     || defined(__ICC)        ) \
      && (defined(NT2_ARCH_X86) || defined(NT2_ARCH_IA64))
    inline cycles_t read_cycles()
    {
      nt2::uint32_t hi = 0, lo = 0;
      __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
      cycles_t that =   static_cast<cycles_t>(lo)
                    | ( static_cast<cycles_t>(hi)<<32 );
      return that;
    }
  #elif defined(BOOST_MSVC) && (_MSC_VER >= 1200 && _M_IX86 >= 500)
  inline cycles_t read_cycles()
  {
    nt2::uint32_t hi = 0, lo = 0;

    __asm
    {
      __asm __emit 0fh __asm __emit 031h
      mov hi, edx
      mov lo, eax
    }

    cycles_t that =   static_cast<cycles_t>(lo)
                    | ( static_cast<cycles_t>(hi)<<32 );
    return that;
  }
  #elif (                                                       \
          (                                                     \
            (                                                   \
                    (defined(__GNUC__) && (defined(__powerpc__) \
                ||  defined(__ppc__)))                          \
            ||  (defined(__MWERKS__) && defined(macintosh))     \
            )                                                   \
          )                                                     \
          ||(   defined(__IBM_GCC_ASM) && (defined(__powerpc__) \
            ||  defined(__ppc__))                               \
            )                                                   \
        )
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

  #endif

  }
}

#endif

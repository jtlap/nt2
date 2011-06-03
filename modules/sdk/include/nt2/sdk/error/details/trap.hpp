//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_ERROR_DETAILS_TRAP_HPP_INCLUDED
#define NT2_SDK_ERROR_DETAILS_TRAP_HPP_INCLUDED

//==============================================================================
// Detects and define how to emit a TRAP signal
//==============================================================================
#if defined(__unix__)|| (defined(__APPLE__) && defined(__MACH__))
#include <csignal>
#endif

#if (   defined(_M_IX86) || defined(__i386__)   \
    ||  defined(_M_IA64) || defined(__ia64__)   \
    )                                           \
    &&  defined(__GNUC__)
#define NT2_DEBUG_TRAP()  __asm("int3")
#elif defined(_MSC_VER)
#define NT2_DEBUG_TRAP()  __debugbreak()
#elif defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define NT2_DEBUG_TRAP() ::raise(SIGTRAP)
#else
#define NT2_DEBUG_TRAP()
#endif

#endif

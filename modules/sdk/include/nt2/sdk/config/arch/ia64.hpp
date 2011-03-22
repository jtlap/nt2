/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_ARCH_IA64_HPP_INCLUDED
#define NT2_SDK_CONFIG_ARCH_IA64_HPP_INCLUDED

#if !defined(NT2_ARCH_DETECTED)
  #if defined(__ia64__)  || defined(_IA64)   || defined(__IA64__)   ||\
      defined(__amd64__) || defined(__amd64) || defined(__x86_64__) ||\
      defined(__x86_64)  || defined(DOXYGEN_ONLY)                     \

    #define NT2_ARCH_DETECTED
    #define NT2_ARCH_IA64
    #define NT2_ARCH_STRING "Intel 64"
    #define NT2_ARCH_ALIGNMENT 16

  #endif
#endif
#endif

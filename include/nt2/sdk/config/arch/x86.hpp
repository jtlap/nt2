/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_ARCH_X86_HPP_INCLUDED
#define NT2_SDK_CONFIG_ARCH_X86_HPP_INCLUDED

#if !defined(NT2_ARCH_DETECTED)
  #if     defined(__i386__)       || defined(_M_IX86)     \
      ||  defined(__THW_INTEL__)  || defined(DOXYGEN_ONLY)\

    #define NT2_ARCH_DETECTED
    #define NT2_ARCH_X86
    #define NT2_ARCH_STRING "Intel x86"
    #define NT2_ARCH_ALIGNMENT 16

  #endif
#endif
#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_OS_MACOS_HPP_INCLUDED
#define NT2_SDK_CONFIG_OS_MACOS_HPP_INCLUDED

#if !defined(NT2_OS_DETECTED)
  #if     defined(macintosh)    || defined(__APPLE__)     \
      ||  defined(__APPLE_CC__) || defined(DOXYGEN_ONLY)  \

    #define NT2_OS_DETECTED
    #define NT2_OS_MAC_OS
    #define NT2_OS_STRING BOOST_PLATFORM

  #endif
#endif

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_OS_WINDOWS_HPP_INCLUDED
#define NT2_SDK_CONFIG_OS_WINDOWS_HPP_INCLUDED

#if !defined(NT2_OS_DETECTED)
  #if     defined(_WIN32) || defined(__WIN32__)     \
      ||  defined(WIN32)  || defined(DOXYGEN_ONLY)  \

    #if !defined(VC_EXTRALEAN)
    #define VC_EXTRALEAN
    #endif

    #if !defined(WIN32_LEAN_AND_MEAN)
    #define WIN32_LEAN_AND_MEAN
    #endif

    #define NT2_OS_DETECTED
    #define NT2_OS_WINDOWS
    #define NT2_OS_STRING BOOST_PLATFORM

  #endif
#endif

#endif

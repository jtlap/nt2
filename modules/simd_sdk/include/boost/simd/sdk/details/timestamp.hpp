//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_DETAILS_TIMESTAMP_HPP_INCLUDED
#define BOOST_SIMD_SDK_DETAILS_TIMESTAMP_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the \ref boost::simd::timestamp utility function
 */

#include <string>

namespace boost { namespace simd
{
  //==============================================================================
  /*!
   * \ingroup sdk
   * timestamp returns a string containing current system time in a readable
   * format.
   *
   * \return Current system time as a \c std::string
   *
   * \par Example Usage:
   *
   * \include timestamp.cpp
   *
   * This code will output a locale dependant string featuring current date and
   * time information.
   */
  //==============================================================================
  std::string timestamp();
} }

#endif

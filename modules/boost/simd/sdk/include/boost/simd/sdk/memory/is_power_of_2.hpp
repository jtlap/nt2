/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_IS_POWER_OF_2_HPP_INCLUDED

/*!
  @file
  @brief Defines the boost::simd::is_power_of_2 function
**/

#include <boost/config.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Checks if a given value is a power of 2

    @param value Value to test
    @return @c true if value is a non-zero power of 2, @c false otherwise.
  **/
  template<class T> BOOST_FORCEINLINE bool is_power_of_2(T value)
  {
    return (!(value & (value - 1)) && value);
  }
} }

#endif

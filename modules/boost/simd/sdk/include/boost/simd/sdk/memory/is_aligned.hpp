/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_IS_ALIGNED_HPP_INCLUDED

#include <cstddef>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/is_power_of_2.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Check a value or address is aligned on an arbitrary alignment boundary

    @param value Value to check
    @param align Alignment boundary to check for.
  **/
  BOOST_FORCEINLINE bool is_aligned(std::size_t value, std::size_t align)
  {
    BOOST_ASSERT_MSG
    ( boost::simd::is_power_of_2(align)
    , "Invalid alignment boundary. You tried to check if "
      "an address or a value is aligned on a non-power of 2 boundary."
    );

    return !(value & (align-1) );
  }

  /*! @overload **/
  template<class T> BOOST_FORCEINLINE bool is_aligned(T* ptr, std::size_t align)
  {
    return boost::simd::is_aligned(reinterpret_cast<std::size_t>(ptr),align);
  }

  /*!
    @brief Check a value or address is aligned on default alignment boundary

    @param value Value to check
  **/
  template<class T> BOOST_FORCEINLINE bool is_aligned(T value)
  {
    return boost::simd::is_aligned(value,BOOST_SIMD_CONFIG_ALIGNMENT);
  }
} }

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED

#include <cstddef>
#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/simd/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/is_power_of_2.hpp>

namespace boost { namespace simd
{
  /*!
    @brief Align value and address on an arbitrary alignment boundary

    @param value Value to align
    @param alignment Alignment boundary
  **/
  BOOST_FORCEINLINE std::size_t align_on(std::size_t value, std::size_t align)
  {
    BOOST_ASSERT_MSG( boost::simd::is_power_of_2(align)
                    , "Invalid alignment boundary. You tried to align an "
                      "address or a value on a non-power of 2 boundary."
                    );

    return (value+align-1) & ~(align-1);
  }

  /*! @overload **/
  template<class T> BOOST_FORCEINLINE T* align_on(T* ptr, std::size_t align)
  {
    std::size_t v = reinterpret_cast<std::size_t>(ptr);
    return reinterpret_cast<T*>(boost::simd::align_on(v,align));
  }

  /*!
    @brief Align value and address on default alignment boundary

    @param value Value to align
  **/
  template<class T> BOOST_FORCEINLINE T align_on(T value)
  {
    return boost::simd::align_on(value,BOOST_SIMD_CONFIG_ALIGNMENT);
  }
} }

#endif

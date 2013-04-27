//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALIGN_ON_HPP_INCLUDED

/*!
  @file
  @brief Defines and implement the align_on function
**/

#include <boost/simd/meta/align_ptr.hpp>
#include <boost/simd/memory/align_ptr.hpp>
#include <boost/simd/memory/parameters.hpp>
#include <boost/simd/memory/is_power_of_2.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>
#include <cstddef>

namespace boost { namespace simd
{
  /*!
    @brief Align value or pointer on an arbitrary alignment boundary

    For any integral value or pointer @c value and any power of 2 @c align,
    computes a value or a pointer @c N so that:

    @code
    N >= value && N % align = 0
    @endcode

    @pre @c align is a power of 2

    @param value Value or pointer to align
    @param align Integral alignment boundary.

    @return The aligned integral value or pointer

    @par Usage:

    @include align_on.cpp

  **/
  BOOST_FORCEINLINE std::size_t align_on(std::size_t value, std::size_t align)
  {
    BOOST_ASSERT_MSG( ::boost::simd::is_power_of_2(align)
                    , "Invalid alignment boundary. You tried to align an "
                      "address or a value on a non-power of 2 boundary."
                    );

    return (value+align-1) & ~(align-1);
  }

  /*! @overload **/
  template<class T> BOOST_FORCEINLINE T* align_on(T* ptr, std::size_t align)
  {
    std::size_t v = reinterpret_cast<std::size_t>(ptr);
    return reinterpret_cast<T*>(::boost::simd::align_on(v,align));
  }

  /*!
    @brief Align value or pointer on the current SIMD compatible alignment

    For any integral value or pointer @c value, computes a value or a pointer
    @c N so that:

    @code
    N >= value && N % BOOST_SIMD_CONFIG_ALIGNMENT = 0
    @endcode

    @param value Value or pointer to align

    @return The aligned integral value or pointer

    @post For optimization purpose, if @c value is a pointer, the return value
    is flagged with a compiler specific attribute stating said pointer is
    statically known to be aligned.

    @par Usage:

    @include align_on_default.cpp

    @see boost::simd::memory::align_ptr
    @see boost::simd::meta::align_ptr
  **/
  BOOST_FORCEINLINE std::size_t align_on(std::size_t value)
  {
    return ::boost::simd::align_on(value,BOOST_SIMD_CONFIG_ALIGNMENT);
  }

  /*! @overload **/
  template<class T> BOOST_FORCEINLINE
  typename ::boost::simd::meta::align_ptr<T,BOOST_SIMD_CONFIG_ALIGNMENT>::type
  align_on(T* ptr)
  {
    return ::boost::simd::memory
            ::align_ptr < BOOST_SIMD_CONFIG_ALIGNMENT >
                        ( ::boost::simd::align_on ( ptr
                                                  , BOOST_SIMD_CONFIG_ALIGNMENT
                                                  )
                        );
  }
} }

#endif

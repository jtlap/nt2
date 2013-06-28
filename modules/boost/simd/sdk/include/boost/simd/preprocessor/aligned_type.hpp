//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_ALIGNED_TYPE_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_ALIGNED_TYPE_HPP_INCLUDED

#include <boost/simd/preprocessor/parameters.hpp>
#include <boost/simd/preprocessor/align_on.hpp>

/*!
  @brief Macro wrapper for SIMD aligned type

  Wraps a type @c T so that it is aligned on an arbitrary alignment constraint.

  @usage{preprocessor/aligned_type_on.cpp}

  @param T      Type to align on current SIMD alignment
  @param ALIGN  Alignment constraint to respect
**/
#define BOOST_SIMD_ALIGNED_TYPE_ON(T,ALIGN) T BOOST_SIMD_ALIGN_ON(ALIGN)

/*!
  @brief Macro wrapper for SIMD aligned type

  Wraps a type @c T so that it is aligned on current SIMD alignment constraint.

  @usage{preprocessor/aligned_type.cpp}

  @param T Type to align on current SIMD alignment
**/
#define BOOST_SIMD_ALIGNED_TYPE(T)                                             \
BOOST_SIMD_ALIGNED_TYPE_ON(T,BOOST_SIMD_CONFIG_ALIGNMENT)                      \
/**/

#endif

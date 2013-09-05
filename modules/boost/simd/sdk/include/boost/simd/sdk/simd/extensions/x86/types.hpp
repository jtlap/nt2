//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_TYPES_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_X86_TYPES_HPP_INCLUDED

#include <boost/simd/sdk/config/type_lists.hpp>

#define BOOST_SIMD_SIMD_REAL_TYPES (double)(float)
/**/

#define BOOST_SIMD_SIMD_INTEGRAL_UNSIGNED_TYPES  (boost::simd::uint64_t)(boost::simd::uint32_t)  \
                                          (boost::simd::uint16_t)(boost::simd::uint8_t)   \
/**/

#define BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES  (boost::simd::int64_t)(boost::simd::int32_t)  \
                                        (boost::simd::int16_t)(boost::simd::int8_t)   \
/**/

#define BOOST_SIMD_SIMD_INT_CONVERT_TYPES  (boost::simd::int32_t)(boost::simd::int64_t) \
/**/

#define BOOST_SIMD_SIMD_UINT_CONVERT_TYPES  (boost::simd::uint32_t)(boost::simd::uint64_t) \
/**/

#define BOOST_SIMD_SIMD_GROUPABLE_TYPES  (boost::simd::int16_t)(boost::simd::uint16_t)(boost::simd::int32_t)(boost::simd::uint32_t)(boost::simd::int64_t)(boost::simd::uint64_t)(double)\
/**/

#define BOOST_SIMD_SIMD_SPLITABLE_TYPES  (boost::simd::int8_t)(boost::simd::uint8_t)(boost::simd::int16_t)(boost::simd::uint16_t)(boost::simd::int32_t)(boost::simd::uint32_t)(float) \
/**/

#define BOOST_SIMD_SIMD_REAL_GROUPABLE_TYPES (double)
#define BOOST_SIMD_SIMD_REAL_SPLITABLE_TYPES  (float)

#endif

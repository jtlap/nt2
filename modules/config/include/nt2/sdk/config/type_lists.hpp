/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/


#ifndef NT2_SDK_CONFIG_TYPE_LISTS_HPP_INCLUDED
#define NT2_SDK_CONFIG_TYPE_LISTS_HPP_INCLUDED


#if !defined(NT2_TYPES)
#define NT2_TYPES  (nt2::uint64_t)     \
    (nt2::int64_t)(double)		     \
    (nt2::uint32_t)(nt2::int32_t)(float)     \
    (nt2::uint16_t)(nt2::int16_t)	     \
    (nt2::uint8_t) (nt2::int8_t)	     \
/**/
#endif

#if !defined(NT2_REAL_TYPES)
#define NT2_REAL_TYPES	     \
  (double)			     \
  (float)			     \
/**/
#define NT2_REAL NT2_REAL_TYPES
#endif

#if !defined(NT2_REAL_CONVERTIBLE_TYPES)
#define NT2_REAL_CONVERTIBLE_TYPES	     \
  (nt2::uint64_t)(nt2::int64_t)(double)	     \
    (nt2::uint32_t)(nt2::int32_t)(float)     \
/**/
#endif

#if !defined(NT2_INTEGRAL_SIGNED_TYPES)
#define NT2_INTEGRAL_SIGNED_TYPES  (nt2::int64_t)	\
    (nt2::int32_t)					\
    (nt2::int16_t)					\
    (nt2::int8_t)					\
/**/
#endif

#if !defined(NT2_UNSIGNED_TYPES)
#define NT2_UNSIGNED_TYPES  (nt2::uint64_t)\
    (nt2::uint32_t)			   \
    (nt2::uint16_t)			   \
    (nt2::uint8_t)			   \
/**/
#endif

#if !defined(NT2_INTEGRAL_TYPES)
#define NT2_INTEGRAL_TYPES  (nt2::uint64_t)		\
    (nt2::int64_t)(nt2::uint32_t)			\
    (nt2::int32_t)(nt2::uint16_t)(nt2::int16_t)		\
    (nt2::int8_t)(nt2::uint8_t)				\
				 /**/
#endif

#if !defined(NT2_SIGNED_TYPES)
#define NT2_SIGNED_TYPES (nt2::int64_t)(double)	\
    (nt2::int32_t)(float)			\
    (nt2::int16_t)				\
    (nt2::int8_t)				\
/**/
#endif

#define NT2__INT_CONVERT_TYPES  (nt2::int32_t)(nt2::int64_t) \
/**/

#define NT2__UINT_CONVERT_TYPES  (nt2::uint32_t)(nt2::uint64_t) \
/**/

#define NT2_SIGNED_INT_GT_8  (nt2::int16_t)(nt2::int32_t)(nt2::int64_t) \
/**/

#define NT2_UNSIGNED_INT_GT_8  (nt2::int16_t)(nt2::int32_t)(nt2::int64_t) \
/**/

#define NT2_INT_64_TYPES (nt2::int64_t)(nt2::uint64_t) \
/**/

#define NT2_INT_32_TYPES  (nt2::int32_t)(nt2::uint32_t) \
/**/

#define NT2_INT_16_TYPES  (nt2::int16_t)(nt2::uint16_t) \
/**/

#define NT2_INT_8_TYPES  (nt2::int8_t)(nt2::uint8_t) \
/**/

#define NT2_GROUPABLE_TYPES  (nt2::int16_t)(nt2::uint16_t)(nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)(double)\
/**/

#define NT2_SPLITABLE_TYPES  (nt2::int8_t)(nt2::uint8_t)(nt2::int16_t)(nt2::uint16_t)(nt2::int32_t)(nt2::uint32_t)(float) \
/**/

#define NT2_INT_GT8_TYPES  (nt2::int16_t)(nt2::uint16_t)(nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)\
/**/

#define NT2_SIGNED_INT_GT_8_TYPES  (nt2::int16_t)(nt2::int32_t)(nt2::int64_t) \
/**/

#define NT2_UNSIGNED_INT_GT_8_TYPES  (nt2::uint16_t)(nt2::uint32_t)(nt2::uint64_t) \
/**/

#define NT2_LT64_TYPES  (nt2::int16_t)(nt2::uint16_t)(nt2::int32_t)(nt2::uint32_t)(nt2::int8_t)(nt2::uint8_t)(float) \
/**/

#define NT2_GT16_TYPES  (nt2::int32_t)(nt2::uint32_t)(nt2::int64_t)(nt2::uint64_t)(float)(double) \
/**/

#define NT2_SIGNED_INT_GT_16_TYPES  (nt2::int32_t)(nt2::int64_t) \
/**/

#define NT2_UNSIGNED_INT_GT_16_TYPES  (nt2::uint32_t)(nt2::uint64_t) \
/**/


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of type_lists.hpp
// /////////////////////////////////////////////////////////////////////////////

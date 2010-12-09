/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_SUPPORTED_TYPES_HPP_INCLUDED
#define NT2_SDK_META_SUPPORTED_TYPES_HPP_INCLUDED

#include <nt2/sdk/config/types.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some predefined macros containing a PP sequence of supported types
////////////////////////////////////////////////////////////////////////////////
#define NT2_TYPES (double)(nt2::uint64_t)(nt2::int64_t) \
                  (float)(nt2::uint32_t)(nt2::int32_t)  \
                  (nt2::uint16_t)(nt2::int16_t)         \
                  (nt2::uint8_t)(nt2::int8_t)           \
                  /**/

#define NT2_REAL (double)(float)

#define NT2_UNSIGNED_TYPES  (nt2::uint64_t)(nt2::uint32_t)  \
                            (nt2::uint16_t)(nt2::uint8_t)   \
                            /**/

#define NT2_SIGNED_TYPES  (double)(nt2::int64_t)(nt2::int32_t)  \
                          (float)(nt2::int16_t)(nt2::int8_t)    \
                          /**/

#define NT2_INTEGRAL_SIGNED_TYPES (nt2::int64_t)(nt2::int32_t)  \
                                  (nt2::int16_t)(nt2::int8_t)   \
                                  /**/

#define NT2_INTEGRAL_UNSIGNED_TYPES (nt2::uint64_t)(nt2::uint32_t)  \
                                    (nt2::uint16_t)(nt2::uint8_t)   \
                                    /**/


#define NT2_INTEGRAL_TYPES NT2_INTEGRAL_SIGNED_TYPES NT2_INTEGRAL_UNSIGNED_TYPES

#endif


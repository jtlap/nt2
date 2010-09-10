/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_UNIT_SDK_META_TYPES_HPP_INCLUDED
#define NT2_UNIT_SDK_META_TYPES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Generates sequence of supported types
////////////////////////////////////////////////////////////////////////////////
#define NT2_TYPES (double)(nt2::uint64_t)(nt2::int64_t) \
                  (float)(nt2::uint32_t)(nt2::int32_t)  \
                  (nt2::uint16_t)(nt2::int16_t)         \
                  (nt2::uint8_t)(nt2::int8_t)(bool)     \
/**/

#endif

/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_TEMPLATIZE_HPP_INCLUDED
#define NT2_SDK_META_TEMPLATIZE_HPP_INCLUDED

// These tautologies to avoid early compilation in some functors
// definitions

namespace nt2 { namespace meta
{
  template <class T> struct double__   { typedef double   type; };
  template <class T> struct float__    { typedef float    type; };
  template <class T> struct int64_t_  { typedef int64_t  type; };
  template <class T> struct int32_t_  { typedef int32_t  type; };
  template <class T> struct int16_t_  { typedef int16_t  type; };
  template <class T> struct int8_t_   { typedef int8_t   type; };
  template <class T> struct uint64_t_ { typedef uint64_t type; };
  template <class T> struct uint32_t_ { typedef uint32_t type; };
  template <class T> struct uint16_t_ { typedef uint16_t type; };
  template <class T> struct uint8_t_  { typedef uint8_t  type; };
} }


#endif

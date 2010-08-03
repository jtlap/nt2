/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_META_MMX_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_META_MMX_HPP_INCLUDED

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for MMX extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct mmx_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// MMX extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_simd_specific<T,tag::mmx_> : has_key < set < __m64>, T > {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct  as_simd<T,tag::mmx_>
  {
    template<class Key, class Dummy=void> struct entry;

    template<class Dummy> struct entry<uint32_t ,Dummy> { typedef __m64 type; };
    template<class Dummy> struct entry<uint16_t ,Dummy> { typedef __m64 type; };
    template<class Dummy> struct entry<uint8_t  ,Dummy> { typedef __m64 type; };
    template<class Dummy> struct entry<int32_t  ,Dummy> { typedef __m64 type; };
    template<class Dummy> struct entry<int16_t  ,Dummy> { typedef __m64 type; };
    template<class Dummy> struct entry<int8_t   ,Dummy> { typedef __m64 type; };
    typedef typename entry<T>::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m64,X>  { typedef tag::mmx_ type; };
} }

#endif

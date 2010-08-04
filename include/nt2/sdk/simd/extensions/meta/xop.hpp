/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_META_XOP_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_META_XOP_HPP_INCLUDED

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for XOP extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct xop_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// XOP extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_simd_specific<T,tag::xop_>
        : has_key < set <__m256d, __m256, __m256i>, T > {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct  as_simd<T,tag::xop_>
  {
    template<class Key, class Dummy=void> struct entry  { typedef na_     type; };
    template<class Dummy> struct entry<float    ,Dummy> { typedef __m256  type; };
    template<class Dummy> struct entry<double   ,Dummy> { typedef __m256d type; };
    template<class Dummy> struct entry<uint64_t ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<uint32_t ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<uint16_t ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<uint8_t  ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<int64_t  ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<int32_t  ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<int16_t  ,Dummy> { typedef __m256i type; };
    template<class Dummy> struct entry<int8_t   ,Dummy> { typedef __m256i type; };
    typedef typename entry<T>::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m256 ,X>  { typedef tag::xop_ type; };
  template<class X> struct extension_of<__m256d,X>  { typedef tag::xop_ type; };
  template<class X> struct extension_of<__m256i,X>  { typedef tag::xop_ type; };
} }

#endif

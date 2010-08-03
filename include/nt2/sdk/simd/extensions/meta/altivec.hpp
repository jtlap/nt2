/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSOINS_META_ALTIVEC_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSOINS_META_ALTIVEC_HPP_INCLUDED

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for Altivec PPC extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct vmx_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// Altivec PPC extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Extension>
  struct  is_simd_specific<T,tag::vmx_>
        : nt2::meta::has_key < nt2::meta::set < __vector float
                                              , __vector unsigned int
                                              , __vector unsigned short
                                              , __vector unsigned char
                                              , __vector signed   int
                                              , __vector signed   short
                                              , __vector signed   char
                                              >
                              , T
                              >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct  as_simd<T,tag::vmx_>
  {
    template<class Key, class Dummy=void> struct entry;

    template<class Dummy>
    struct entry<float,Dummy>     { typedef __vector float          type; };
    template<class Dummy>
    struct entry<uint32_t,Dummy>  { typedef __vector unsigned int   type; };
    template<class Dummy>
    struct entry<uint16_t,Dummy>  { typedef __vector unsigned short type; };
    template<class Dummy>
    struct entry<uint8_t,Dummy>   { typedef __vector unsigned char  type; };
    template<class Dummy>
    struct entry<int32_t,Dummy>   { typedef __vector signed int     type; };
    template<class Dummy>
    struct entry<int16_t,Dummy>   { typedef __vector signed short   type; };
    template<class Dummy>
    struct entry<int8_t,Dummy>    { typedef __vector signed char    type; };

    typedef typename entry<T>::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X>
  struct extension_of<__vector float          ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector unsigned int   ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector unsigned short ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector unsigned char  ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector signed int     ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector signed short   ,X> { typedef tag::vmx_ type; };
  template<class X>
  struct extension_of<__vector signed char    ,X> { typedef tag::vmx_ type; };
} }

#endif

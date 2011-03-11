
//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_EXTENSIONS_META_ALTIVEC_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_META_ALTIVEC_HPP_INCLUDED

#include <climits>
#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for Altivec PPC extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct altivec_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// Altivec PPC extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_simd_specific<T,tag::altivec_>
        : nt2::meta::has_key < nt2::meta::set < __vector float
                                              , __vector unsigned int
                                              , __vector unsigned short
                                              , __vector unsigned char
                                              , __vector signed   int
                                              , __vector signed   short
                                              , __vector signed   char
                                              , __vector __bool int
                                              , __vector __bool short
                                              , __vector __bool char
                                              >
                              , T
                              >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct  as_simd<T,tag::altivec_>
  {
    template< class Type
            , std::size_t Sz = sizeof(Type)*CHAR_BIT
            , bool Integral = boost::is_integral<T>::value
            , class Dummy=void
            >
    struct entry { typedef na_ type; };

    template<class Dummy>
    struct entry<float, 32, false ,Dummy> { typedef __vector float  type;         };
    template<class Type, class Dummy>
    struct entry<Type , 32, false ,Dummy> { typedef __vector unsigned int   type; };
    template<class Type, class Dummy>
    struct entry<Type , 16, false ,Dummy> { typedef __vector unsigned short type; };
    template<class Type, class Dummy>
    struct entry<Type , 8 , false ,Dummy> { typedef __vector unsigned char  type; };
    template<class Type, class Dummy>
    struct entry<Type , 32, true  ,Dummy> { typedef __vector signed int   type;   };
    template<class Type, class Dummy>
    struct entry<Type , 16, true  ,Dummy> { typedef __vector signed short type;   };
    template<class Type, class Dummy>
    struct entry<Type , 8 , true  ,Dummy> { typedef __vector signed char  type;   };

    typedef typename entry<T>::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X>
  struct extension_of<__vector float          ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector unsigned int   ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector unsigned short ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector unsigned char  ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector signed int     ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector signed short   ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector signed char    ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector __bool int     ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector __bool short   ,X> { typedef tag::altivec_ type; };
  template<class X>
  struct extension_of<__vector __bool char    ,X> { typedef tag::altivec_ type; };
} }

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_META_SSE_HPP_INCLUDED

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/details/bitwise_cast.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for SSE extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct sse_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// SSE extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<> struct is_simd_specific<__m128 , tag::sse_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m128d, tag::sse_> : boost::mpl::true_ {};
  template<> struct is_simd_specific<__m128i, tag::sse_> : boost::mpl::true_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  as_simd<T,tag::sse_>
        : boost::mpl::if_ < boost::is_integral<T>
                          , __m128i
                          , typename  boost::mpl
                            ::if_ < boost::is_same<T,float>
                                  , __m128
                                  , typename  boost::mpl
                                    ::if_ < boost::is_same<T,double>
                                        , __m128d
                                        , na_
                                        >::type
                                  >::type
                          >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m128 ,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128d,X>  { typedef tag::sse_ type; };
  template<class X> struct extension_of<__m128i,X>  { typedef tag::sse_ type; };
}}

////////////////////////////////////////////////////////////////////////////////
// Conversion between vector types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
    #if defined BOOST_MSVC || defined BOOST_INTEL
        #define NT2_SSE_CONVERT union_cast
    #else
        #define NT2_SSE_CONVERT convert_cast
    #endif

    template<> struct bitwise_cast<__m128 , __m128d> : NT2_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128 , __m128i> : NT2_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128d, __m128 > : NT2_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128d, __m128i> : NT2_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128i, __m128 > : NT2_SSE_CONVERT {};
    template<> struct bitwise_cast<__m128i, __m128d> : NT2_SSE_CONVERT {};

    #undef NT2_SSE_CONVERT
}}

#endif

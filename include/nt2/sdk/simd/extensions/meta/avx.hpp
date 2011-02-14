/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_EXTENSIONS_META_AVX_HPP_INCLUDED
#define NT2_SDK_SIMD_EXTENSIONS_META_AVX_HPP_INCLUDED

#include <nt2/sdk/meta/set.hpp>
#include <nt2/sdk/meta/has_key.hpp>
#include <nt2/sdk/config/types.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_integral.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for AVX extensions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct avx_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// AVX extensions overload
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_simd_specific<T,tag::avx_>
        : has_key < set <__m256d, __m256, __m256i>, T > {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  as_simd<T,tag::avx_>
        : boost::mpl::if_ < boost::is_integral<T>
                          , __m256i
                          , typename  boost::mpl
                            ::if_ < boost::is_same<T,float>
                                  , __m256
                                  , typename  boost::mpl
                                    ::if_ < boost::is_same<T,double>
                                        , __m256d
                                        , na_
                                        >::type
                                  >::type
                          >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class X> struct extension_of<__m256 ,X>  { typedef tag::avx_ type; };
  template<class X> struct extension_of<__m256d,X>  { typedef tag::avx_ type; };
  template<class X> struct extension_of<__m256i,X>  { typedef tag::avx_ type; };
} }

#endif

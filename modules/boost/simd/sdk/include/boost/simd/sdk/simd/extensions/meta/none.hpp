//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_NONE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_META_NONE_HPP_INCLUDED


#include <boost/simd/sdk/config/types.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>
#include <boost/simd/sdk/simd/meta/is_simd_specific.hpp>
#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>

// Forward-declare logical
namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

// Forward-declare memory::aligned_array
namespace boost { namespace simd { namespace memory
{
  template<class T, std::size_t N, std::size_t Align>
  struct aligned_array;
} } }

////////////////////////////////////////////////////////////////////////////////
// None extensions overload - Emulated mode handling
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, check if it's a SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t N, std::size_t Align> 
  struct is_simd_specific< boost::simd::memory::aligned_array<T,N,Align> 
                         , tag::simd_emulation_<N> 
                         > : boost::mpl::false_ {};

  //////////////////////////////////////////////////////////////////////////////
  // For a given type and extension, return the associated SIMD register type
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N, class T>
  struct as_simd<T, tag::simd_emulation_<N>, typename enable_if< is_fundamental<T> >::type>
  {
    typedef boost::simd::memory::
    aligned_array<T, (N/sizeof(T))> type;
  };

  template<std::size_t N, class T>
  struct as_simd<logical<T>, tag::simd_emulation_<N> >
  {
    typedef boost::simd::memory::
    aligned_array<T, (N/sizeof(T))> type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // For a given SIMD register type, return the associated SIMD extension tag
  //////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t N, std::size_t Align>
  struct extension_of< typename boost::simd::memory::aligned_array<T,N,Align> >
  {
    typedef tag::simd_emulation_< (N*sizeof(T)) > type;
  };

} } }

#endif

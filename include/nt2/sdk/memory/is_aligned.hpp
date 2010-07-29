/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_IS_ALIGNED_HPP_INCLUDED
#define NT2_SDK_MEMORY_IS_ALIGNED_HPP_INCLUDED

#include <cstddef>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/config/bootstrap.hpp>
#include <nt2/sdk/memory/meta/is_power_of_2.hpp>

namespace nt2 {  namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Checks if a given value is aligned on a given power of 2 boundary
  // Documentation: reference/sdk/aligned/function/is_aligned.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N> inline
  typename boost::enable_if_c < meta::is_power_of_2_c<N>::value
                              , bool
                              >::type
                              is_aligned( std::size_t v )
  {
    return !(v & (N-1) );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Checks if a given pointer is aligned on a given power of 2 boundary
  // Documentation: reference/sdk/aligned/function/is_aligned.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N,class T> inline
  typename boost::enable_if_c < meta::is_power_of_2_c<N>::value
                              , bool
                              >::type
  is_aligned( T* v )
  {
    return is_aligned<N>( reinterpret_cast<std::size_t>(v) );
  }

  //////////////////////////////////////////////////////////////////////////////
  // Checks if a given value is aligned on current alignment value
  //////////////////////////////////////////////////////////////////////////////
  static inline bool is_aligned( std::size_t v )
  {
    return is_aligned<NT2_CONFIG_ALIGNMENT>(v);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Checks if a given pointer is aligned on current alignment value
  //////////////////////////////////////////////////////////////////////////////
  template<class T> static inline bool is_aligned( T* v )
  {
    return is_aligned<NT2_CONFIG_ALIGNMENT>(v);
  }
} }

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED
#define NT2_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED

#include <cstddef>
#include <boost/utility/enable_if.hpp>
#include <nt2/sdk/config/bootstrap.hpp>
#include <nt2/sdk/memory/meta/is_power_of_2.hpp>

namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // Align a runtime value onto a static power of 2 boundary.
  // If N is not a power of 2, the function is disabled by SFINAE
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N> inline
  typename boost::enable_if_c < meta::is_power_of_2_c<N>::value
                              , std::size_t
                              >::type
  align_on( std::size_t value )
  {
    return (value+N-1) & ~(N-1);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Align a pointer onto a static power of 2 boundary.
  // If N is not a power of 2, the function is disabled by SFINAE
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N, class T>
  typename boost::enable_if_c < meta::is_power_of_2_c<N>::value
                              , T*
                              >::type
  align_on( T* ptr )
  {
    return reinterpret_cast<T*>(align_on<N>(reinterpret_cast<std::size_t>(ptr)));
  }

  //////////////////////////////////////////////////////////////////////////////
  // Align a runtime value onto current alignment value
  //////////////////////////////////////////////////////////////////////////////
  static inline std::size_t align_on( std::size_t value )
  {
    return align_on<NT2_CONFIG_ALIGNMENT>(value);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Align a pointer onto current alignment value
  //////////////////////////////////////////////////////////////////////////////
  template<class T> static inline T* align_on( T* ptr )
  {
    return align_on<NT2_CONFIG_ALIGNMENT>(ptr);
  }
} }

#endif

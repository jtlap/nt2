/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_STRIP_HPP_INCLUDED
#define NT2_SDK_META_STRIP_HPP_INCLUDED

#include <cstddef>

////////////////////////////////////////////////////////////////////////////////
// Remove all type qualifier from a type
// TODO: Documentation: http://nt2.lri.fr/sdk/meta/strip.html
////////////////////////////////////////////////////////////////////////////////

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // strip removes const, ref and volatile -- better than Mr Proper
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct strip                      { typedef T type; };
  template<class T> struct strip<T const            > { typedef T type; };
  template<class T> struct strip<T &                > { typedef T type; };
  template<class T> struct strip<T const &          > { typedef T type; };
  template<class T> struct strip<volatile T         > { typedef T type; };
  template<class T> struct strip<volatile T const   > { typedef T type; };
  template<class T> struct strip<volatile T &       > { typedef T type; };
  template<class T> struct strip<volatile T const & > { typedef T type; };

  //////////////////////////////////////////////////////////////////////////////
  // strip on C-style array
  //////////////////////////////////////////////////////////////////////////////
  template<class T, std::size_t N>
  struct strip<T const[N]     > { typedef T type[N];  };

  template<class T, std::size_t N>
  struct strip<T (&)[N]       > { typedef T type[N];  };

  template<class T, std::size_t N>
  struct strip<T const (&)[N] > { typedef T type[N];  };
} }

#endif

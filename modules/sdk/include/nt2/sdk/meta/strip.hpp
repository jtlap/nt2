//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_STRIP_HPP_INCLUDED
#define NT2_SDK_META_STRIP_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the nt2::meta::strip \metafunction
 */

#include <cstddef>

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * Removes all reference and cv-qualifier from a given type \c T.
   *
   * \tparam T Type to strip from reference and cv-qualifier.
   *
   * \par Semantic:
   *
   * For any given type \c T,
   *
   * \code
   * typedef nt2::meta::strip<T>::type r;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef remove_cv< remove_reference<T>::type >::type r;
   * \endcode
   *
   * \usage
   *
   * \include strip.cpp
   */
  //============================================================================
  template<class T> struct strip                      { typedef T type; };
  template<class T> struct strip<T const            > { typedef T type; };
  template<class T> struct strip<T &                > { typedef T type; };
  template<class T> struct strip<T const &          > { typedef T type; };
  template<class T> struct strip<volatile T         > { typedef T type; };
  template<class T> struct strip<volatile T const   > { typedef T type; };
  template<class T> struct strip<volatile T &       > { typedef T type; };
  template<class T> struct strip<volatile T const & > { typedef T type; };

  //============================================================================
  // strip on C-style array
  //============================================================================
  template<class T, std::size_t N>
  struct strip<T const[N]     > { typedef T type[N];  };

  template<class T, std::size_t N>
  struct strip<T (&)[N]       > { typedef T type[N];  };

  template<class T, std::size_t N>
  struct strip<T const (&)[N] > { typedef T type[N];  };
} }

#endif

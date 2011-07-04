//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_PRIMITIVE_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_PRIMITIVE_OF_HPP_INCLUDED
/*!
 * \file
 * \brief Defines the boost::simd::meta::primitive_of \metafunction
 */
#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/error/static_assert.hpp>

namespace boost { namespace simd {  namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * For a given \ref Hierarchizable type T, returns the undelying type used to
   * define T
   *
   * \tparam Hierarchizable Type to extract a primitive from.
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantic:
   * For a given \ref Hierarchizable type T,
   *
   * \code
   * typedef primitive_of<T>::type r;
   * \endcode
   *
   * is defined so that
   *
   * \code
   * is_same<T, apply<factory_of<T>,r>::type>::value == true
   * \endcode
   *
   * \usage
   *
   * \include primitive_of.cpp
   */
  //============================================================================
  template<class Hierarchizable>
  struct primitive_of
  {
    typedef Hierarchizable type;
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_SCALAR_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_SCALAR_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::is_scalar \metafunction
 */

#include <boost/mpl/bool.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/details/is_scalar.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * Checks if a given Hierarchizable type is a scalar type.
   *
   * \model
   *
   * \metafunction
   *
   * \semantic
   *
   * For any given Hierarchizable \c T,
   *
   * \code
   * typedef boost::dispatch::meta::is_scalar<T>::type r;
   * \endcode
   *
   * evaluates to \true_ is T has a hierarchy tied to \c scalar_
   *
   * \usage
   *
   * \include is_scalar.cpp
   */
  //============================================================================
  template<class T>
  struct  is_scalar
        : details::is_scalar<typename hierarchy_of<T>::type>
  {};
} } }

#endif

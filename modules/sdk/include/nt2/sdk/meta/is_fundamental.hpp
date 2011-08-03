//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_FUNDAMENTAL_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_FUNDAMENTAL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::is_fundamental \metafunction
 */

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //==============================================================================
  /*!
   * Checks if a given type is a fundamental type (i.e any scalar type natively
   * supported by C++).
   *
   * \par Model:
   *
   * \metafunction
   *
   * \semantic
   *
   * For any type \c T
   *
   * \code
   * typedef is_fundamental<T>::type r;
   * \endcode
   *
   * evaluates to \true_ if \c T hierarchy inherits from \c fundamental_<T>
   * and to \false_ otherwise
   *
   * \usage
   *
   * \include is_fundamental.cpp
   */
  //==============================================================================
  template<class T>
  struct  is_fundamental
        : boost::is_base_of < meta::scalar_< meta::fundamental_<T> >
                            , typename meta::hierarchy_of<T>::type
                            >
  {};
} } }

#endif


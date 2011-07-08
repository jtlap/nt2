//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_HAS_KEY_HPP_INCLUDED
#define BOOST_DISPATCH_META_HAS_KEY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::has_key meta-function
 */

#include <boost/dispatch/details/decltype.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * For a given \c Key type and a given boost::dispatch::meta::set \c Set, returns a
   * boolean \metaint equals to \true_ if said \c Key belongs to \c Set.
   *
   * \tparam Set boost::dispatch::meta::set to look into
   * \tparam Key Type to look for in \c Set
   *
   * \semantic
   *
   * For any set \c S and any key type \c K,
   *
   * \code
   * typedef boost::dispatch::meta::has_key<S,K>::type v;
   * \endcode
   *
   * evalautes to \true_ is \c K is a member of \c S, otherwise evaluates to
   * \false_
   *
   * \usage
   *
   * \include has_key.cpp
   *
   * \see boost::dispatch::meta::set
   * \see boost::dispatch::meta::join
   */
  //============================================================================
  template<class Set,class Key> struct has_key
  {
    static Key* keyptr;
    BOOST_DISPATCH_DECLTYPE(Set::key(keyptr), type);
    BOOST_STATIC_CONSTANT( bool, value = type::value );
  };
} } }

#endif

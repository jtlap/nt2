//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_HAS_KEY_HPP_INCLUDED
#define NT2_SDK_META_HAS_KEY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::meta::has_key meta-function
 */

#include <boost/typeof/typeof.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * For a given \c Key type and a given nt2::meta::set \c Set, returns a
   * boolean \metaint equals to \true_ if said \c Key belongs to \c Set.
   *
   * \tparam Set nt2::meta::set to look into
   * \tparam Key Type to look for in \c Set
   *
   * \semantic
   *
   * For any set \c S and any key type \c K,
   *
   * \code
   * typedef nt2::meta::has_key<S,K>::type v;
   * \endcode
   *
   * evalautes to \true_ is \c K is a member of \c S, otherwise evaluates to
   * \false_
   *
   * \usage
   *
   * \include has_key.cpp
   *
   * \see nt2::meta::set
   * \see nt2::meta::join
   */
  //============================================================================
  template<class Set,class Key> struct has_key
  {
    static Key* keyptr;
    BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested, Set::key(keyptr) )
    typedef typename nested::type type;
    BOOST_STATIC_CONSTANT( bool, value = type::value );
  };
} }

#endif

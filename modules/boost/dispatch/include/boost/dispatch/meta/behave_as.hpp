//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_BEHAVE_AS_HPP_INCLUDED
#define BOOST_DISPATCH_META_BEHAVE_AS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the \ref boost::dispatch::meta::behave_as \metafunction
 */

#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * Forward the application of a given \metalambda \c Lambda onto the primitive
   * type of a given Hierarchizable.
   *
   * \tparam Lambda \metalambda to apply.
   * \tparam Hierarchizable Type to introspect.
   *
   * \semantic
   *
   * For any Hierarchizable type \c T and any Lambda \c L:
   *
   * \code
   * typedef boost::dispatch::meta::behave_as<L,T>::type r;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef apply1 < L
   *                , boost::dispatch::meta::primitive_of< boost::dispatch::meta::strip< T >::type >::type
   *                >::type     r;
   * \endcode
   *
   * For any other types, a \c BOOST_DISPATCH_BEHAVIOR_OF_NON_FUNDAMENTAL_PRIMITIVE_IS_UNDEFINED
   * static assertion is raised.
   *
   * \usage
   *
   * \include behave_as.cpp
   */
  //============================================================================
  template<class Lambda,class Hierarchizable>
  struct  behave_as
        : boost::mpl::
          apply1< Lambda
                , typename primitive_of < typename
                                          strip<Hierarchizable>::type
                                        >::type
                >::type
  {};
} } }

#endif

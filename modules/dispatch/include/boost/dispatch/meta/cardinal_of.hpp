//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_CARDINAL_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the \ref boost::dispatch::meta::cardinal_of \metafunction
 */

#include <boost/mpl/size_t.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace ext
{
  //============================================================================
  /*!
   * \ingroup extensions
   * Extension point for \ref boost::dispatch::meta::cardinal specialized upon a \c Type
   * and its \c Hierarchy.
   *
   * \tparam Type Hierarchizable type to specialize for.
   * \tparam Hierarchy Hierarchy of type
   *
   * \usage
   *
   * For any type modeling a multi-valued register, this extension can be
   * specialized to provide a compile-time integral constant equals to this
   * type valuation.
   *
   * \see boost::dispatch::simd::native
   *
   */
  //============================================================================
  template<class Type,class Hierarchy>
  struct cardinal_of_impl : boost::mpl::size_t<1> {};
} } }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * \metafunction computing the number of values of type \c T to fit in a
   * register.
   *
   * \tparam T Hierarchizable type
   *
   * \par Model:
   *
   * \metafunction
   *
   * \semantic
   *
   * \usage
   *
   * \include cardinal_of.cpp
   */
  //============================================================================
  template<class T>
  struct  cardinal_of
        : ext::cardinal_of_impl < typename meta::strip<T>::type
                                , typename hierarchy_of<T>::type
                                > {};
} } }

#endif

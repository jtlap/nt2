//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implement the \ref boost::dispatch::meta::as_ generic type wrapper
 */

#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * \ingroup hierarchy
   * Type wrapper hierarchy.
   *
   * \tparam T Wrapped type hierarchy
   */
  //============================================================================
  template<class T> struct target_ {};
} } }
#endif

BOOST_DISPATCH_REGISTER_HIERARCHY(target_)

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * Lightweight type wrapper. Some implementation details of \nt2 require types
   * to be wrapped into an empty structure so the type can be passed as an
   * "ghostly" instance. \ref as_ performs such a wrapping and tag itself as
   * belonging to the \ref target_ hierarchy.
   *
   * \par Models:
   *
   * - Hierarchizable
   * - \metafunction
   */
  //============================================================================
  template<class T> struct as_
  {
    typedef T                                               type;
  };

  //============================================================================
  // Requirements for Hierarchizable
  //============================================================================
  template<class T, class Origin>
  struct hierarchy_of< as_<T>, Origin>
  {
    typedef typename hierarchy_of<T, Origin>::base           base;
    typedef target_<typename hierarchy_of<T, Origin>::type>  type;
  };

  //============================================================================
  // Requirements for Buildable
  //============================================================================
  template<class T>
  struct primitive_of< as_<T> > : primitive_of<T> {};

  template<class T>
  struct factory_of< as_<T> > { typedef as_<boost::mpl::_1> type; };
} } }

#endif

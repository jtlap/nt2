//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_AS_HPP_INCLUDED
#define NT2_SDK_META_AS_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implement the \ref nt2::meta::as_ generic type wrapper
 */

#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/meta/primitive_of.hpp>

#if defined(DOXYGEN_ONLY)
namespace nt2 { namespace meta
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
} }
#endif

NT2_REGISTER_HIERARCHY(target_)

namespace nt2 { namespace meta
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
    //==========================================================================
    // Required for Hierarchizable
    //==========================================================================
    typedef target_<typename hierarchy_of<T>::type >  nt2_hierarchy_tag;

    typedef T                                         type;
  };

  //============================================================================
  // Requirements for Buildable
  //============================================================================
  template<class T>
  struct primitive_of< as_<T> > : primitive_of<T> {};

  template<class T>
  struct factory_of< as_<T> > { typedef as_<boost::mpl::_1> type; };
} }

#endif

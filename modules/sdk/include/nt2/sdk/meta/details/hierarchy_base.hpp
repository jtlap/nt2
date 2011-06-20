//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DETAILS_HIERARCHY_BASE_HPP_INCLUDED
#define NT2_SDK_META_DETAILS_HIERARCHY_BASE_HPP_INCLUDED

/*!
 * \file
 */

#include <nt2/sdk/meta/details/hierarchy_pp.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * The unknown_ hierarchy is the upper bound in the hierarchy lattice.
   * When a dispatch resovles on unknown_, it means no suitable overload has
   * been found.
   */
  //============================================================================
  template<class T> struct unknown_
  {
    typedef unknown_  parent;
    typedef unknown_  origin;
  };

  //============================================================================
  /*! The unspecified_ hierarchy is used for non-categorized type that can
   *  be caught silently
   */
  //============================================================================
  NT2_HIERARCHY_CLASS_TPL(unspecified_, unknown_<T> );
} }

#endif

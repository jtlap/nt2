//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONSTANT_CATEGORY_HPP_INCLUDED
#define NT2_SDK_CONSTANT_CATEGORY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the constant_ hierarchy and EDSL generators
 */

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace meta
{
  //============================================================================
  /*!
   * Defines the category class for all constants identifiers
   */
  //============================================================================
  template<class T> struct constant_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };
} }

namespace nt2
{
  //============================================================================
  /*!
   * This class wraps a constant identifier usable by Boost.Proto to build
   * named consatnt value terminal.
   */
  //============================================================================
  template<class ID>
  struct constant_
  {
    typedef ID type;
    typedef meta::constant_< constant_<ID> > nt2_hierarchy_tag;
  };
}

#endif

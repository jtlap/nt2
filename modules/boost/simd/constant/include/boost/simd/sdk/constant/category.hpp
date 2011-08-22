//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONSTANT_CATEGORY_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONSTANT_CATEGORY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the constant_ hierarchy and EDSL generators
 */

#include <boost/dispatch/meta/as.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
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
} } }

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::constant_;
} } }

namespace boost { namespace dispatch
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
    typedef meta::constant_< constant_<ID> > dispatch_hierarchy_tag;
  };
} }

#endif

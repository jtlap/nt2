/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_CATEGORY_HPP_INCLUDED
#define NT2_SDK_CONSTANT_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Category for constants
//* TODO:  Documentation: http://nt2.lri.fr/sdk/constant/meta/category.html
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// constant_ wraps a constant type into a EDSL element
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  template<class ConstantID> struct constant_ { typedef ConstantID type; };
} }

#endif

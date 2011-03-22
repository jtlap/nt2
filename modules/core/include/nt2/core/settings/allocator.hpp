/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_ALLOCATOR_HPP_INCLUDED
#define NT2_CORE_SETTINGS_ALLOCATOR_HPP_INCLUDED

#include <boost/mpl/placeholders.hpp>
#include <nt2/core/settings/meta/option.hpp>

////////////////////////////////////////////////////////////////////////////////
// Defines allocator options
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace options
{
  struct allocator_ { typedef void nt2_is_option_type; };
} }

////////////////////////////////////////////////////////////////////////////////
// allocator_<A> defines a custom allocator to be used by the container.
// A is a MPL unary Placeholder Meta-Function which parameters will be
// substitued by the container's value type.
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { template<class Allocator> struct allocator_ {}; }

////////////////////////////////////////////////////////////////////////////////
// Register allocator_ has a valid options::allocator_ type
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Allocator, class Default>
  struct option<allocator_<Allocator>, options::allocator_, Default, void>
  {
    typedef Allocator type;
  };
} }

#endif

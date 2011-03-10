/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_META_COMPOSITE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_COMPOSITE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Defines the composite type macro and type selector
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check if a given type is composite or not
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Type> struct  is_composite : boost::mpl::false_ {};
} }

////////////////////////////////////////////////////////////////////////////////
// Adapt a structure to be a NT2 composite type
////////////////////////////////////////////////////////////////////////////////
#define NT2_ADAPT_COMPOSITE(Name,Fields)  \
BOOST_FUSION_ADAPT_STRUCT(Name,Fields);   \
namespace nt2 { namespace meta            \
{                                         \
  template<>                              \
  struct  is_composite<Name>              \
        : boost::mpl::true_ {};           \
} }                                       \
/**/

#endif

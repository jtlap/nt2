//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_HIERARCHY_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the hierarchy building classes and \metafunction
 */

//////////////////////////////////////////////////////////////////////////////
// Types hierarchy defines a partially order lattice of type familly
// which helps categorizing a given type into all its potential enclosing type
// sets. Hierarchies are template so they can use their root type to
// select at each lattice node which ancestor to use.
//////////////////////////////////////////////////////////////////////////////

#include <climits>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/dispatch/meta/details/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // hierarchy_of computes the entry point of a given type inside the type
  // hierarchy lattice.
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Origin = T, class Enable = void>
  struct  hierarchy_of
        : details::hierarchy_of < typename meta::strip<T>::type
                                , typename meta::strip<Origin>::type
                                >
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Overload for types with inner hierarchy tag
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename
                        enable_if_type<typename meta::strip<T>::type
                                                    ::dispatch_hierarchy_tag
                                      >::type
                      >
  {
    typedef typename meta::strip<T>::type::dispatch_hierarchy_tag type;
  };
} } }

#endif

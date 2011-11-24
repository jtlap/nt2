//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_TABLE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_TABLE_HPP_INCLUDED

#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/core/container/table/table_container.hpp>
#include <nt2/core/container/table/adapted/table.hpp>

namespace nt2 { namespace container
{
  template<class Type, class Settings>
  struct table
       : boost::dispatch::
         meta::terminal_of< table_container<Type,Settings> >::type
  {
    typedef typename
    boost::dispatch::meta::
    terminal_of< table_container<Type,Settings> >::type parent;

    typedef typename parent::extent_type extent_type;

    //==========================================================================
    //  table default constructor
    //==========================================================================
    table() {}

    //==========================================================================
    //  table constructor from an of_size_ like element
    //==========================================================================
    template<class Sz>
    table ( Sz const& sz
          , typename boost::
            disable_if< boost::proto::matches < typename boost::proto::
                                                result_of::as_expr<Sz>::type
                                              , grammar
                                              >
                      >::type* = 0
          )
    {
      boost::proto::value(*this).resize(extent_type(sz));
    }
/*
    //==========================================================================
    //  table constructor from an of_size_ like element and a Range
    //==========================================================================
    template<class Sz, class Iterator>
    table ( Sz const& sz, Iterator const& b, Iterator const& e)
    {
      boost::proto::value(*this).resize(extent_type(sz));

    }
*/

    //==========================================================================
    // table constructor from an expression
    //==========================================================================
    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    table ( Xpr const& xpr
          , typename boost::
            enable_if < boost::proto::matches < typename boost::proto::
                                                result_of::as_expr<Xpr>::type
                                              , grammar
                                              >
                      >::type* = 0
          )
    {
      static_cast<parent&>(*this) = xpr;
    }

    //==========================================================================
    // table copy constructor
    //==========================================================================
    table( table const& src ) { static_cast<parent&>(*this) = src; }

    //==========================================================================
    // Enable base expression handlign of assignment
    //==========================================================================
    using parent::operator=;
  };

} }

#endif

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
#include <nt2/core/container/category.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/core/container/table/table_container.hpp>

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
    //  table default constructor
    //==========================================================================
    template<class Sz>
    table( Sz const& sz ) { boost::proto::value(*this).resize(extent_type(sz)); }

    template<class Xpr,class Result>
    BOOST_DISPATCH_FORCE_INLINE table(expression<Xpr,Result> const& xpr)
    {
      static_cast<parent&>(*this) = xpr;
    }

    using parent::operator=;
  };

} }

#endif

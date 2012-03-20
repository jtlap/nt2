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
#include <nt2/include/functions/construct.hpp>
#include <nt2/core/container/table/category.hpp>
#include <nt2/core/container/dsl/expression.hpp>
#include <nt2/core/container/table/adapted/table.hpp>

namespace nt2 { namespace meta
{
  template<class Tag, class T, class S>
  struct make_container
  {
    typedef typename meta::option<S, tag::id_, id_<0> >::type   id_t;
    typedef memory::container<Tag,id_t,T,S>                     type;
  };

  template<class Tag, class T, class S>
  struct make_terminal
  {
    typedef typename make_container<Tag,T,S>::type                    cont_t;
    typedef typename boost::dispatch::meta::terminal_of<cont_t>::type type;
  };
} }

namespace nt2 { namespace container
{
  template<class T, class S>
  struct  table
        : meta::make_terminal<tag::table_,T,S>::type
  {
    typedef typename meta::make_container<tag::table_,T,S>::type  container_type;
    typedef typename meta::make_terminal<tag::table_,T,S>::type   parent;
    typedef typename container_type::extent_type                  extent_type;
    typedef typename container_type::index_type                   index_type;
    typedef typename container_type::allocator_type               allocator_type;
    typedef typename container_type::pointer                      pointer;
    typedef typename container_type::const_pointer                const_pointer;

    //==========================================================================
    //  table default constructor
    //==========================================================================
    table() {}

    //==========================================================================
    //  table constructor from its allocator
    //==========================================================================
    table( allocator_type const& a ) : parent(container_type(a)) {}

    //==========================================================================
    // table constructor from a single initializer.
    // This version handles initializing from of_size or expression.
    //==========================================================================
    template<class A0> table( A0 const& a0 )
    {
      nt2::construct(*this,a0);
    }

    //==========================================================================
    // table constructor from a pair of initializer.
    //==========================================================================
    template<class A0, class A1> table( A0 const& a0, A1 const& a1 )
    {
      nt2::construct(*this,a0,a1);
    }

    //==========================================================================
    // table constructor from a triplet of initializer.
    // This version handles initializing from : { size, Iterator, Iterator }
    //==========================================================================
    template<class A0, class A1, class A2>
    table( A0 const& a0, A1 const& a1, A2 const& a2 )
    {
      nt2::construct(*this,a0,a1,a2);
    }

    //==========================================================================
    // Enable base expression handling of assignment
    //==========================================================================
    using parent::operator=;

    //==========================================================================
    // Access to raw data
    //==========================================================================
    pointer       raw()       { return boost::proto::value(*this).raw(); }
    const_pointer raw() const { return boost::proto::value(*this).raw(); }
  };
} }

#endif


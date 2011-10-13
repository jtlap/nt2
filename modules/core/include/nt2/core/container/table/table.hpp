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

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class S>
  struct terminal_of< nt2::container::table_container<T, S> >
  {
    typedef typename nt2::container::table_container<T, S>::settings_type settings_type;

    typedef nt2::container::expression< typename boost::proto::terminal< nt2::container::table_container<T, settings_type> >::type
            , nt2::container::table_container<T, settings_type>&
            > type;
  };

  template<class T, class S>
  struct semantic_of<nt2::container::table<T, S> >
  {
    typedef nt2::container::table_container<T, S>& type;
  };

} } }

namespace nt2 { namespace container
{

template<class T, class S>
struct table
 : boost::dispatch::meta::terminal_of< table_container<T, S> >::type
{
  typedef typename
  boost::dispatch::meta::terminal_of< table_container<T, S> >::type parent;

  table() {}

  template<class Xpr,class Result>
  BOOST_DISPATCH_FORCE_INLINE
  table(expression<Xpr,Result> const& xpr) { static_cast<parent&>(*this) = xpr; }

  using parent::operator=;
};

} }

#endif

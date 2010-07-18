/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_PROCESS_NODE_HPP_INCLUDED
#define NT2_SDK_DSL_PROCESS_NODE_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/make_expr.hpp>
#include <nt2/sdk/dsl/push_front.hpp>
#include <nt2/sdk/dsl/recursive_process.hpp>

namespace nt2 { namespace dsl
{
  template<class Visitor,class Tag> struct process_node;
} }

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto primitive transform that handle node evaluation for the generic
  // recursive tree compilation grammar by a given Visitor
  //////////////////////////////////////////////////////////////////////////////
  template<class Visitor>
  struct traversal : boost::proto::transform< traversal<Visitor> >
  {
    template<class X, class S, class D>
    struct impl : boost::proto::transform_impl<X,S,D>
    {
      typedef typename boost::proto::tag_of<X>::type    tag;
      typedef typename
      boost::result_of< dsl::process_node<Visitor,tag>  ( typename impl::expr
                                                        , typename impl::state
                                                        , typename impl::data
                                                        )
                      >::type                           result_type;

      inline result_type  operator()( typename impl::expr_param   x
                                    , typename impl::state_param  s
                                    , typename impl::data_param   d
                                    ) const
      {
        return dsl::process_node<Visitor,tag>()(x,s,d);
      }
    };
  };
} }

namespace nt2 { namespace dsl
{
  //////////////////////////////////////////////////////////////////////////////
  // Implementation of process_node to be overloaded by users for specific
  // Tag and specific Visitor use-cases. By default, we just use the recursive
  // processing transform to aggregate result as we crawl over the A.S.T.
  //////////////////////////////////////////////////////////////////////////////
  template<class Visitor,class Tag>
  struct process_node : meta::recursive_process<Visitor,Tag> {};
} }

////////////////////////////////////////////////////////////////////////////////
// Register process_node<Visitor> as a proto callable transform
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace proto
{
  template<class Visitor>
  struct is_callable<nt2::details::traversal<Visitor> > : mpl::true_ {};
} }

#endif

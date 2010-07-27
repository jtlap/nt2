/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_PROCESS_LEAF_HPP_INCLUDED
#define NT2_SDK_DSL_PROCESS_LEAF_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/proto/traits.hpp>
#include <boost/proto/make_expr.hpp>
#include <nt2/sdk/dsl/process_node.hpp>
#include <nt2/sdk/functor/details/tags.hpp>

namespace nt2 { namespace dsl
{
  //////////////////////////////////////////////////////////////////////////////
  // Implementation of process_node for terminals
  //////////////////////////////////////////////////////////////////////////////
  template<class Visitor> struct process_node<Visitor,functors::terminal_>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Get the Visitor specialization to handle terminal from here
    ////////////////////////////////////////////////////////////////////////////
    typedef typename boost::mpl::apply< Visitor
                                      , functors::terminal_
                                      >::type               call;

    ////////////////////////////////////////////////////////////////////////////
    // Transform result
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class X, class S, class D>
    struct  result<This(X,S,D)>
    {
      typedef typename boost::result_of<boost::proto::_value(X)>::type  base;
      typedef typename boost::result_of<call(base,S,D)>::type           type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Transform operator call
    ////////////////////////////////////////////////////////////////////////////
    template<class X, class S, class D>
    typename result<process_node(X,S,D)>::type
    operator()( X& x, S& s, D& d) const
    {
      call callee;
      return callee(boost::proto::value(x),s,d);
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  // Implementation of process_node for comma to enforce order of evaluation
  //////////////////////////////////////////////////////////////////////////////
  template<class Visitor> struct process_node<Visitor,functors::comma_>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Get the Visitor specialization to handle terminal from here
    ////////////////////////////////////////////////////////////////////////////
    typedef dsl::compile<Visitor>               call;

    ////////////////////////////////////////////////////////////////////////////
    // Transform result
    ////////////////////////////////////////////////////////////////////////////
    template<class Sig> struct result;

    template<class This,class X, class S, class D>
    struct  result<This(X,S,D)>
    {
      typedef typename boost::result_of<boost::proto::_right(X)>::type  base;
      typedef typename boost::result_of<call(base,S,D)>::type           type;
    };

    ////////////////////////////////////////////////////////////////////////////
    // Transform operator call
    ////////////////////////////////////////////////////////////////////////////
    template<class X, class S, class D>
    typename result<process_node(X,S,D)>::type
    operator()( X& x, S& s, D& d) const
    {
      dsl::compile<Visitor> callee;
      callee(boost::proto::left(x),s,d);
      return callee(boost::proto::right(x),s,d);
    }
  };
} }

#endif

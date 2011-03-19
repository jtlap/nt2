/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/is_assignment_expression.hpp>

namespace nt2 { namespace container
{
  ////////////////////////////////////////////////////////////////////////////
  // Here is the domain-specific expression wrapper for table_ expression
  ////////////////////////////////////////////////////////////////////////////
  template<class Expr, class Dims>
  struct  expression<Expr,tag::table_,Dims>
        : boost::proto::extends < Expr
                                , expression<Expr,tag::table_,Dims>
                                , container::domain<tag::table_,Dims>
                                >
  {
    ////////////////////////////////////////////////////////////////////////////
    // Internal proto related types
    ////////////////////////////////////////////////////////////////////////////
    typedef boost::proto::extends < Expr
                                  , expression<Expr,tag::table_,Dims>
                                  , container::domain<tag::table_,Dims>
                                  >                                     parent;

    ////////////////////////////////////////////////////////////////////////////
    // expression hierarchy and semantic of container:::expression
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    details::hierarchy_of_expr<expression>::type nt2_hierarchy_tag;

    ////////////////////////////////////////////////////////////////////////////
    // Default explicit constructor
    ////////////////////////////////////////////////////////////////////////////
    explicit  expression( Expr const& xpr = Expr() )
            : parent(xpr), is_silent(false)
    {
      // If Expr is an assignment node, set xpr.is_evaluable to false
      //if(meta::is_assignment_expression<Expr>::value)
      //  boost::proto::right(*this).silence();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Destructor performs evaluation if required
    ////////////////////////////////////////////////////////////////////////////
    ~expression()
    {
      // If *this is not silent, evaluates it
      if(!is_silent) (*this)();
    }

    ////////////////////////////////////////////////////////////////////////////
    // table expression are read-only Ranges
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // table expression have a n-ary operator()
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // table expression have a nullary operator() that evaluates itself
    ////////////////////////////////////////////////////////////////////////////
    void operator()()
    {
      // current_target::evaluate(*this);
    }

    ////////////////////////////////////////////////////////////////////////////
    // table expression have an operator[] that adds specific settings
    ////////////////////////////////////////////////////////////////////////////
    template<class Settings>
    expression& operator[](Settings const& )
    {
      // ????
      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // External accessor for evaluation trigger
    ////////////////////////////////////////////////////////////////////////////
    void silence() const { is_silent = true; }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Trigger for non-evaluation at destruction-time.
    ////////////////////////////////////////////////////////////////////////////
    mutable bool is_silent;
  };
} }

#endif

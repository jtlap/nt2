//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_EXPRESSION_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_EXPRESSION_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/proto/extends.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/core/container/dsl/fusion.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

// Semantic of NT2 expression lies in its ResultType template parameter
namespace boost { namespace dispatch { namespace meta
{
  template<class Expr, class ResultType>
  struct semantic_of< nt2::container::expression<Expr, ResultType> >
  {
    typedef ResultType type;
  };
} } }

namespace nt2 { namespace container
{
  template<class Expr, class ResultType>
  struct  expression
        : boost::proto::extends < Expr
                                , expression<Expr, ResultType>
                                , container::domain
                                >
  {
    //==========================================================================
    /*! Type of the parent expression                                         */
    //==========================================================================
    typedef boost::proto::extends < Expr
                                  , expression<Expr, ResultType>
                                  , container::domain
                                  >                                parent;

    //==========================================================================
    // expression initialization called from generator    
    //==========================================================================
    BOOST_DISPATCH_FORCE_INLINE 
    expression(Expr const& x = Expr()) : parent(x) {}
    
    //==========================================================================
    // Assignment operator force evaluation - LHS non-terminal version
    //==========================================================================
    template<class Xpr,class Result> BOOST_DISPATCH_FORCE_INLINE
    expression const& operator=(expression<Xpr,Result> const& xpr) const
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }
    
    //==========================================================================
    // Assignment operator force evaluation - regular version
    //==========================================================================
    template<class Xpr,class Result> BOOST_DISPATCH_FORCE_INLINE 
    expression& operator=(expression<Xpr,Result> const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }

    //==========================================================================
    // Assignment operator from same expression type
    //==========================================================================
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(expression const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }
    
    //==========================================================================
    // Op-Assignment operators generate proper tree then evaluates
    //==========================================================================
    #define NT2_MAKE_ASSIGN_OP(OP)                                             \
    template<class Xpr,class Result>                                           \
    BOOST_DISPATCH_FORCE_INLINE expression&                                    \
    operator BOOST_PP_CAT(OP,=)(expression<Xpr,Result> const& xpr)             \
    {                                                                          \
      return *this = *this OP xpr;                                             \
    }                                                                          \
    template<class Xpr,class Result>                                           \
    BOOST_DISPATCH_FORCE_INLINE expression const&                              \
    operator BOOST_PP_CAT(OP,=)(expression<Xpr,Result> const& xpr) const       \
    {                                                                          \
      return *this = *this OP xpr;                                             \
    }                                                                          \
    /**/

    NT2_MAKE_ASSIGN_OP(+)
    NT2_MAKE_ASSIGN_OP(-)
    NT2_MAKE_ASSIGN_OP(*)
    NT2_MAKE_ASSIGN_OP(/)
    NT2_MAKE_ASSIGN_OP(%)
    NT2_MAKE_ASSIGN_OP(^)
    NT2_MAKE_ASSIGN_OP(&)
    NT2_MAKE_ASSIGN_OP(|)
    NT2_MAKE_ASSIGN_OP(>>)
    NT2_MAKE_ASSIGN_OP(<<)

    #undef NT2_MAKE_ASSIGN_OP

    //==========================================================================
    // Conversion operator forces evaluation - used for reduction operator
    //==========================================================================
    BOOST_DISPATCH_FORCE_INLINE operator 
    typename boost::dispatch::meta::terminal_of<ResultType>::type() const 
    { 
      return nt2::evaluate(*this); 
    }    
  };
} }

#endif

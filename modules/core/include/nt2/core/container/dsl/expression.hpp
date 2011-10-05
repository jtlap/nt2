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

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <nt2/include/functions/assign.hpp>
#include <boost/proto/extends.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/assert.hpp>

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
    typedef boost::proto::extends < Expr
                                , expression<Expr, ResultType>
                                , container::domain
                                >                                parent;

    // expression initialization called from generator
    BOOST_DISPATCH_FORCE_INLINE
    expression(Expr const& xpr = Expr()) : parent(xpr)
    {
      #if 0
      BOOST_ASSERT_MSG( check_size(xpr)
                      , "Dynamic size mismatch in container expression"
                      );
      #endif
    }
    
    // Assignment operators force evaluation
    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(Xpr const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }
    
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(expression const& xpr)
    {
      nt2::evaluate( nt2::assign(*this, xpr) );
      return *this;
    }
    
    #define NT2_MAKE_ASSIGN_OP(OP)                                      \
    template<class X>                                                   \
    BOOST_DISPATCH_FORCE_INLINE                                         \
    expression& operator BOOST_PP_CAT(OP,=)(X const& xpr)               \
    {                                                                   \
      return *this = *this OP xpr;                                      \
    }                                                                   \
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

    // Conversion operator forces evaluation
    BOOST_DISPATCH_FORCE_INLINE
    operator ResultType() const { return nt2::evaluate(*this); }    
  };
} }

#endif

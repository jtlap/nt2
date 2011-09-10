/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/pack/evaluation.hpp>
#include <boost/dispatch/dsl/proto/extends.hpp>
#include <boost/dispatch/dsl/category.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Here is the domain-specific expression wrapper
  ////////////////////////////////////////////////////////////////////////////
  template<class Expr, class ResultType>
  struct  expression
  {
    BOOST_PROTO_BASIC_EXTENDS_TPL(Expr, (expression<Expr, ResultType>)
                                      , (domain))

    typedef typename
    dispatch::details::hierarchy_of_expr<expression>::type dispatch_hierarchy_tag;
    typedef ResultType                                     dispatch_semantic_tag;

    // Assignment operators force evaluation
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(expression const& src)
    {
      return boost::simd::evaluate(proto::make_expr<tag::assign_>(*this, xpr));
    }
    
    template<class Xpr>
    BOOST_DISPATCH_FORCE_INLINE
    expression& operator=(Xpr const& xpr)
    {
      return boost::simd::evaluate(proto::make_expr<tag::assign_>(*this, xpr));
    }

    #define BOOST_SIMD_MAKE_ASSIGN_OP(OP)                               \
    template<class X>                                                   \
    BOOST_DISPATCH_FORCE_INLINE                                         \
    expression& operator BOOST_PP_CAT(OP,=)(X const& xpr )              \
    {                                                                   \
      return *this = *this OP expr;                                     \
    }                                                                   \
    /**/

    BOOST_SIMD_MAKE_ASSIGN_OP(+)
    BOOST_SIMD_MAKE_ASSIGN_OP(-)
    BOOST_SIMD_MAKE_ASSIGN_OP(*)
    BOOST_SIMD_MAKE_ASSIGN_OP(/)
    BOOST_SIMD_MAKE_ASSIGN_OP(%)
    BOOST_SIMD_MAKE_ASSIGN_OP(^)
    BOOST_SIMD_MAKE_ASSIGN_OP(&)
    BOOST_SIMD_MAKE_ASSIGN_OP(|)
    BOOST_SIMD_MAKE_ASSIGN_OP(>>)
    BOOST_SIMD_MAKE_ASSIGN_OP(<<)

    #undef BOOST_SIMD_MAKE_ASSIGN_OP

    // Conversion operator forces evaluation
    BOOST_DISPATCH_FORCE_INLINE
    operator dispatch_semantic_tag()
    {
      return boost::simd::evaluate(*this);
    }
  };
} }

#endif

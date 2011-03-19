/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_FROM_DOMAIN_HPP_INCLUDED
#define NT2_SDK_DSL_FROM_DOMAIN_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

////////////////////////////////////////////////////////////////////////////////
// from_domain is a function that wraps an expression from domain X in domain Y
// This is used throughout nt2 to allow cross-domain acceptance in various
// grammars and transforms
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  namespace tag { struct from_domain_ {}; }
  NT2_FUNCTION_IMPLEMENTATION(tag::from_domain_ , from_domain  , 1 )
}

NT2_REGISTER_DISPATCH ( tag::from_domain_ , tag::cpu_, (A0)(Dom)(Tag)(Sema)
                      , ((expr_<A0,Dom,Tag,Sema>))
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Tag,class Semantic,class Dummy>
  struct call < tag::from_domain_(tag::expr_<Domain,Tag,Semantic>)
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
          : boost::proto::result_of::
            make_expr < tag::from_domain_
                      , typename meta::strip<A0>::type const&
                      >
    {};

    NT2_FUNCTOR_CALL(1)
    {
      return  boost::proto::
              make_expr<tag::from_domain_>( boost::cref(a0) );
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// from_domain also exists as proto grammar to be used in other EDSL gammars
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace dsl
{
  template<class Expr>
  struct from_domain : boost::proto::unary_expr<tag::from_domain_,Expr> {};
} }

#endif

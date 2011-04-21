/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_PREDICATES_RECOGNITION_IS_NOT_LESS_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_RECOGNITION_IS_NOT_LESS_EQUAL_HPP_INCLUDED

#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/recognition.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/toolbox/predicates/function/is_not_less_equal.hpp>

NT2_REGISTER_DISPATCH ( tag::logical_not_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , ((expr_<A1,Dom,tag::is_less_equal_,Sema>))
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::logical_not_(tag::expr_<Domain,tag::is_less_equal_,Semantic>)
              , tag::recognition_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::is_not_less_equal_(
          typename boost::proto::result_of::child_c<A0, 0>::type
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return is_not_less_equal(boost::proto::child_c<0>(a0));
    }
  };
} }

#endif

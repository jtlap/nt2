/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_ARITHMETIC_RECOGNITION_FMA_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_RECOGNITION_FMA_HPP_INCLUDED

#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/recognition.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/toolbox/arithmetic/function/fma.hpp>

NT2_REGISTER_DISPATCH ( tag::plus_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , ((expr_<A0,Dom,tag::multiplies_,Sema>))(unspecified_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::plus_(tag::expr_<Domain,tag::multiplies_,Semantic>, tag::unspecified_)
              , tag::recognition_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::fma_(
          typename boost::proto::result_of::child_c<A0, 0>::type,
          typename boost::proto::result_of::child_c<A0, 1>::type,
          A1
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), a1);
    }
  };
} }

NT2_REGISTER_DISPATCH ( tag::plus_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , (unspecified_<A0>)((expr_<A1,Dom,tag::multiplies_,Sema>))
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::plus_(tag::unspecified_, tag::expr_<Domain,tag::multiplies_,Semantic>)
              , tag::recognition_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::fma_(
          typename boost::proto::result_of::child_c<A1, 0>::type,
          typename boost::proto::result_of::child_c<A1, 1>::type,
          A0
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), a0);
    }
  };
} }

#endif

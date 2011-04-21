/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_BITWISE_RECOGNITION_BITWISE_ANDNOT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_RECOGNITION_BITWISE_ANDNOT_HPP_INCLUDED

#include <nt2/sdk/dsl/category.hpp>
#include <nt2/sdk/dsl/recognition.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/toolbox/bitwise/function/bitwise_andnot.hpp>

NT2_REGISTER_DISPATCH ( tag::bitwise_and_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , (unspecified_<A0>)((expr_<A1,Dom,tag::complement_,Sema>))
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::bitwise_and_(tag::unspecified_, tag::expr_<Domain,tag::complement_,Semantic>)
              , tag::recognition_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::bitwise_andnot_(
          A0,
          typename boost::proto::result_of::child_c<A1, 0>::type
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_andnot(a0, boost::proto::child_c<0>(a1));
    }
  };
} }

NT2_REGISTER_DISPATCH ( tag::bitwise_and_ , tag::recognition_, (A0)(A1)(Dom)(Sema)
                      , ((expr_<A0,Dom,tag::complement_,Sema>))(unspecified_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Domain,class Semantic,class Dummy>
  struct call < tag::bitwise_and_(tag::expr_<Domain,tag::complement_,Semantic>, tag::unspecified_)
              , tag::recognition_, Dummy
              >
        : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)>
      : meta::call< tag::bitwise_andnot_(
          A1,
          typename boost::proto::result_of::child_c<A0, 0>::type
        ) >
    {};


    NT2_FUNCTOR_CALL(2)
    {
      return bitwise_andnot(a1, boost::proto::child_c<0>(a0));
    }
  };
} }

#endif

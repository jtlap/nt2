/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_STORE_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_STORE_HPP_INCLUDED

namespace nt2 { namespace functors
{
  template<class X, class Info>
  struct call<store_,tag::simd_(tag::ast_,X), Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1, class A2>
    struct  result<This(A0,A1,A2)> : boost::remove_reference<A0> {};

    NT2_FUNCTOR_CALL_DISPATCH ( 3
                              , typename
                                meta::is_native<typename A0::base_type>::type
                              , ( 2, (boost::mpl::true_, boost::mpl::false_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(3,boost::mpl::true_)
    {
      A0 that = store(boost::proto::value(a0).value(),a1,a2);
      return that;
    }

    NT2_FUNCTOR_CALL_EVAL_IF(3,boost::mpl::false_)
    {
      for(typename A0::size_type i=0;i<A0::static_size;++i)
        a1[A0::static_size*a2+i] = a0[i];
      return a0;
    }
  };
} }

#endif

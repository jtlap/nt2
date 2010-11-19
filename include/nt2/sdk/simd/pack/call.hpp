/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_CALL_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_CALL_HPP_INCLUDED

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // When in SIMD, dispatch on the scalar of argument A0
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag, class X, class Info>
  struct  dispatch<Tag,tag::simd_(tag::ast_,X),Info>
        : boost::mpl::always< fundamental_ >
  {};

  template<class Tag, class X, class Info>
  struct  call<Tag,tag::simd_(tag::ast_,X),fundamental_, Info>
        : callable
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct  result<This(A0)>
    {
      typedef typename meta::strip<A0>::type arg0;
      typedef typename boost::proto::result_of
                                    ::make_expr < Tag
                                                , arg0 const&
                                                >::type  type;
    };

    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
    {
      typedef typename meta::strip<A0>::type arg0;
      typedef typename meta::strip<A1>::type arg1;
      typedef typename boost::proto::result_of
                                    ::make_expr < Tag
                                                , arg0 const&
                                                , arg1 const&
                                                >::type  type;
    };

    template<class This,class A0,class A1,class A2>
    struct  result<This(A0,A1,A2)>
    {
      typedef typename meta::strip<A0>::type arg0;
      typedef typename meta::strip<A1>::type arg1;
      typedef typename meta::strip<A2>::type arg2;
      typedef typename boost::proto::result_of
                                    ::make_expr < Tag
                                                , arg0 const&
                                                , arg1 const&
                                                , arg2 const&
                                                >::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return boost::proto::make_expr<Tag>( boost::cref(a0) );
    }

    NT2_FUNCTOR_CALL(2)
    {
      return boost::proto::make_expr<Tag>( boost::cref(a0), boost::cref(a1) );
    }

    NT2_FUNCTOR_CALL(3)
    {
      return boost::proto::make_expr<Tag> ( boost::cref(a0)
                                          , boost::cref(a1)
                                          , boost::cref(a2)
                                          );
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_GENERATIVE_PREPROCESSOR_HPP_INCLUDED
#define NT2_CORE_UTILITY_GENERATIVE_PREPROCESSOR_HPP_INCLUDED

#include <nt2/sdk/parameters.hpp>
#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <iterator>

#define NT2_PP_GENERATIVE_ARGS(z,n,t) \
(BOOST_PP_CAT(A,n))                   \
/**/

#define NT2_PP_GENERATIVE_HIERARCHY(z,n,t)  \
(scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >) \
/**/

//==============================================================================
// Construct a generative node from a Constant node and an ast
//==============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_AST(Name,Tag)                             \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (A0)                                              \
                          , (ast_<A0>)                                        \
                          )                                                   \
{                                                                             \
  typedef meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)                             \
                                        (meta::as_<double>)                   \
                    >::type               res_t;                              \
  typedef typename  boost::proto::result_of                                   \
          ::make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      , box<of_size_max>                                      \
                      , box< meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >  \
                      , meta::as_<res_t>                                      \
                      >::type             result_type;                        \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(A0 const& a0) const                \
  {                                                                           \
    BOOST_ASSERT_MSG                                                          \
    ( nt2::isrow(a0)                                                          \
    , "Error using " #Name ": Size vector must be a row vector."              \
    );                                                                        \
                                                                              \
    of_size_max sizee;                                                        \
    std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));           \
    nt2::memory::copy(a0.raw(), a0.raw()+sz, &sizee[0]);                      \
                                                                              \
    return  boost::proto::                                                    \
            make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(sizee)                                                   \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
};                                                                            \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (A0)(T)                                           \
                          , (ast_<A0>)                                        \
                            (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef typename meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)(T)>::type res_t;   \
  typedef typename  boost::proto::result_of                                   \
          ::make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      , box<of_size_max>                                      \
                      , box<meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >   \
                      , meta::as_<res_t>                                      \
                      >::type             result_type;                        \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const      \
  {                                                                           \
    BOOST_ASSERT_MSG                                                          \
    ( nt2::isrow(a0)                                                          \
    , "Error using " #Name ": Size vector must be a row vector."              \
    );                                                                        \
                                                                              \
    of_size_max sizee;                                                        \
    std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));           \
    nt2::memory::copy(a0.raw(), a0.raw()+sz, &sizee[0]);                      \
                                                                              \
    return  boost::proto::                                                    \
            make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(sizee)                                                   \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
}                                                                             \
/**/

//============================================================================
// Construct a generative node from a Constant node and a fusion sequence
//============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_FUSION(Tag)                               \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (Seq)                                             \
                          , (fusion_sequence_<Seq>)                           \
                          )                                                   \
{                                                                             \
  typedef meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)                             \
                                        (meta::as_<double>)                   \
                    >::type               res_t;                              \
  typedef typename meta::strip<Seq>::type seq_t;                              \
  typedef typename  boost::proto::result_of                                   \
          ::make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      , box<seq_t>                                            \
                      , box<meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >   \
                      , meta::as_<res_t>                                      \
                      >::type             result_type;                        \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(Seq const& seq) const              \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(seq)                                                     \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
};                                                                            \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (Seq)(T)                                          \
                          , (fusion_sequence_<Seq>)                           \
                            (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef typename meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)(T)>::type res_t;   \
  typedef typename meta::strip<Seq>::type seq_t;                              \
  typedef typename  boost::proto::result_of                                   \
          ::make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      , box<seq_t>                                            \
                      , box<meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >   \
                      , meta::as_<res_t>                                      \
                      >::type             result_type;                        \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(Seq const& seq, T const&) const    \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr                                                         \
            < BOOST_PP_TUPLE_ELEM(2,0,Tag)                                    \
            , container::domain                                               \
            >                                                                 \
            ( boxify(seq)                                                     \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
}                                                                             \
/**/

//============================================================================
// Construct a generative node from a Constant node and n scalars
//============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_SIZE(z,n,Tag)                             \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_ARGS,~)       \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_HIERARCHY,~)  \
                          )                                                   \
{                                                                             \
  typedef meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)                             \
                                        (meta::as_<double>)                   \
                    >::type res_t;                                            \
  typedef boost::proto::result_of::                                           \
          make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                            \
                    , container::domain                                       \
                    , box<BOOST_PP_CAT(_,BOOST_PP_CAT(n,D))>                  \
                    , box< meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >    \
                    , meta::as_<res_t>                                        \
                    >::type             result_type;                          \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a) ) const               \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr<  BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(of_size(BOOST_PP_ENUM_PARAMS(n,a)))                      \
            , boxify( meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>() )       \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
};                                                                            \
                                                                              \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_ARGS,~)(T)    \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_HIERARCHY,~)  \
                            (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef typename meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)(T)>::type res_t;   \
  typedef typename boost::proto::result_of::                                  \
          make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                            \
                    , container::domain                                       \
                    , box<BOOST_PP_CAT(_,BOOST_PP_CAT(n,D))>                  \
                    , box< meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >    \
                    , meta::as_<res_t>                                        \
                    >::type             result_type;                          \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a), T const& ) const     \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr<  BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(of_size(BOOST_PP_ENUM_PARAMS(n,a)))                      \
            , boxify( meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>() )       \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
};                                                                            \
/**/

//============================================================================
// Construct a 2D generative node from a single scalar
//============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_SINGLE(Tag)                               \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (A0), (scalar_< arithmetic_<A0> >)                \
                          )                                                   \
{                                                                             \
  typedef meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)                             \
                                        (meta::as_<double>)                   \
                    >::type res_t;                                            \
  typedef boost::proto::result_of::                                           \
          make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                            \
                    , container::domain                                       \
                    , box<_2D>                                                \
                    , box< meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >    \
                    , meta::as_<res_t>                                        \
                                        >::type             result_type;      \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(A0 const& a0) const                \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(of_size(a0,a0))                                          \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
};                                                                            \
                                                                              \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (A0)(T)                                           \
                          , (scalar_< arithmetic_<A0> >)                      \
                            (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef typename meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)(T)>::type res_t;   \
  typedef typename  boost::proto::result_of::                                 \
          make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                            \
                    , container::domain                                       \
                    , box<_2D>                                                \
                    , box< meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >    \
                    , meta::as_<res_t>                                        \
                    >::type             result_type;                          \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(A0 const& a0, T const&) const      \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr<  BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(of_size(a0,a0))                                          \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
}                                                                             \
/**/

//============================================================================
// Construct a 0D generative node from target argument
//============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_TARGET(Tag)                               \
NT2_FUNCTOR_IMPLEMENTATION( BOOST_PP_TUPLE_ELEM(2,0,Tag), tag::cpu_           \
                          , (T)                                               \
                          , (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef typename meta::call<BOOST_PP_TUPLE_ELEM(2,1,Tag)(T)>::type res_t;   \
  typedef typename  boost::proto::result_of::                                 \
          make_expr < BOOST_PP_TUPLE_ELEM(2,0,Tag)                            \
                    , container::domain                                       \
                    , box<_0D>                                                \
                    , box< meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)> >    \
                    , meta::as_<res_t>                                        \
                    >::type             result_type;                          \
                                                                              \
  BOOST_FORCEINLINE result_type operator()(T const&) const                    \
  {                                                                           \
    return  boost::proto::                                                    \
            make_expr<  BOOST_PP_TUPLE_ELEM(2,0,Tag)                          \
                      , container::domain                                     \
                      >                                                       \
            ( boxify(of_size())                                               \
            , boxify(meta::constant_<BOOST_PP_TUPLE_ELEM(2,1,Tag)>())         \
            , meta::as_<res_t>()                                              \
            );                                                                \
  }                                                                           \
}                                                                             \
/**/

//==============================================================================
// Build all variants of a constant generator expression
//==============================================================================
#define NT2_PP_MAKE_GENERATIVE(Name,Tag)                    \
NT2_PP_GENERATIVE_MAKE_FROM_AST(Name,Tag);                  \
NT2_PP_GENERATIVE_MAKE_FROM_FUSION(Tag);                    \
NT2_PP_GENERATIVE_MAKE_FROM_SINGLE(Tag);                    \
NT2_PP_GENERATIVE_MAKE_FROM_TARGET(Tag);                    \
BOOST_PP_REPEAT_FROM_TO ( 2                                 \
                        , BOOST_PP_INC(NT2_MAX_DIMENSIONS)  \
                        , NT2_PP_GENERATIVE_MAKE_FROM_SIZE  \
                        , Tag                               \
                        )                                   \
/**/

#endif

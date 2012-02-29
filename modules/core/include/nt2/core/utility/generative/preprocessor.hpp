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

#define NT2_PP_GENERATIVE_ARGS(z,n,t) \
(BOOST_PP_CAT(A,n))                   \
/**/

#define NT2_PP_GENERATIVE_HIERARCHY(z,n,t)  \
(scalar_< arithmetic_<BOOST_PP_CAT(A,n)> >) \
/**/

//============================================================================
// Construct a generative node from a Constant node
//============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_SIZE(z,n,Tag)                             \
NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_                                    \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_ARGS,~)       \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_HIERARCHY,~)  \
                          )                                                   \
{                                                                             \
  typedef nt2::details::                                                      \
          generative< nt2::tag::table_                                        \
                    , nt2::details::constant_generator<Tag>                   \
                    , double                                                  \
                    , settings(BOOST_PP_CAT(_,BOOST_PP_CAT(n,D)))             \
                    > base;                                                   \
                                                                              \
  typedef typename  boost::proto::                                            \
                    result_of::as_expr< base                                  \
                                      , container::domain                     \
                                      >::type             result_type;        \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a) ) const               \
  {                                                                           \
    nt2::details::constant_generator<Tag> callee;                             \
    base that(of_size(BOOST_PP_ENUM_PARAMS(n,a)),callee);                     \
    return boost::proto::as_expr<container::domain>(that);                    \
  }                                                                           \
};                                                                            \
                                                                              \
NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_                                    \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_ARGS,~)(T)    \
                          , BOOST_PP_REPEAT(n,NT2_PP_GENERATIVE_HIERARCHY,~)  \
                            (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef nt2::details::                                                      \
          generative< nt2::tag::table_                                        \
                    , nt2::details::constant_generator<Tag>                   \
                    , typename T::type                                        \
                    , settings(BOOST_PP_CAT(_,BOOST_PP_CAT(n,D)))             \
                    > base;                                                   \
                                                                              \
  typedef typename  boost::proto::                                            \
                    result_of::as_expr< base                                  \
                                      , container::domain                     \
                                      >::type             result_type;        \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(n,const A,& a), T const& ) const     \
  {                                                                           \
    nt2::details::constant_generator<Tag> callee;                             \
    base that(of_size(BOOST_PP_ENUM_PARAMS(n,a)),callee);                     \
    return boost::proto::as_expr<container::domain>(that);                    \
  }                                                                           \
};                                                                            \
/**/

//============================================================================
// Construct a 2D (n, n) generative node from a 1D Constant node (n).
//============================================================================
#define NT2_PP_GENERATIVE_MAKE_FROM_SINGLE(Tag)                               \
NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (A0)                              \
                          , (scalar_< arithmetic_<A0> >)                      \
                          )                                                   \
{                                                                             \
  typedef nt2::details::                                                      \
          generative< nt2::tag::table_                                        \
                    , nt2::details::constant_generator<Tag>                   \
                    , double                                                  \
                    , settings(_2D)                                           \
                    > base;                                                   \
                                                                              \
  typedef typename  boost::proto::                                            \
                    result_of::as_expr< base                                  \
                                      , container::domain                     \
                                      >::type             result_type;        \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(A0 const& a0) const                                              \
  {                                                                           \
    nt2::details::constant_generator<Tag> callee;                             \
    base that(of_size(a0,a0),callee);                                         \
    return boost::proto::as_expr<container::domain>(that);                    \
  }                                                                           \
};                                                                            \
                                                                              \
NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_ , (A0)(T)                          \
                          , (scalar_< arithmetic_<A0> >)                      \
                            (target_< scalar_< unspecified_<T> > >)           \
                          )                                                   \
{                                                                             \
  typedef nt2::details::                                                      \
          generative< nt2::tag::table_                                        \
                    , nt2::details::constant_generator<Tag>                   \
                    , typename T::type                                        \
                    , settings(_2D)                                           \
                    > base;                                                   \
                                                                              \
  typedef typename  boost::proto::                                            \
                    result_of::as_expr< base                                  \
                                      , container::domain                     \
                                      >::type             result_type;        \
                                                                              \
  BOOST_FORCEINLINE result_type                                               \
  operator()(A0 const & a0, T const& ) const                                  \
  {                                                                           \
    nt2::details::constant_generator<Tag> callee;                             \
    base that(of_size(a0,a0),callee);                                         \
    return boost::proto::as_expr<container::domain>(that);                    \
  }                                                                           \
};                                                                            \
/**/

#endif

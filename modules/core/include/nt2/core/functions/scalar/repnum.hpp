//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_REPNUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_REPNUM_HPP_INCLUDED

#include <nt2/core/functions/repnum.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/functions/details/generative_preprocessor.hpp>
#include <nt2/core/functions/details/repnum.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates repnum from scalar + N size value
  //============================================================================
  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                           \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repnum_, tag::cpu_                    \
                            , (A0)                                            \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M2,~) \
                            , (scalar_<unspecified_<A0> > )                   \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M1,~) \
                            )                                                 \
  {                                                                           \
    typedef BOOST_PP_CAT(_,BOOST_PP_CAT(n,D)) sizes_t;                        \
    typedef typename  boost::proto::                                          \
             result_of::make_expr< nt2::tag::repnum_                          \
                                          , container::domain                 \
                                          , box<sizes_t>                      \
                                          , box<nt2::details::repnum<A0> >    \
                                          , meta::as_<A0>                     \
             >::type   result_type;                                           \
                                                                              \
    BOOST_FORCEINLINE result_type                                             \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n),A,const& a)) const \
    {                                                                         \
      sizes_t sizee(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n),a));         \
      return  boost::proto::                                                  \
        make_expr < nt2::tag::repnum_                                         \
        , container::domain                                                   \
        > (  boxify(sizee),                                                   \
             boxify(nt2::details::repnum<A0>(a0)),                            \
             meta::as_<A0>() );                                               \
    }                                                                         \
  };                                                                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M2
  #undef M1
  #undef M0

  //============================================================================
  // Generates repnum from the value and one integer
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repnum_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<unspecified_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::repnum_,
      container::domain,
      box<_2D>,
      box<nt2::details::repnum<A0> >,
      meta::as_<A0>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, A1 const& a1) const
    {
      return  boost::proto::
        make_expr < nt2::tag::repnum_
        , container::domain
        > (
           boxify(_2D(a1, a1)),
           boxify(nt2::details::repnum<A0>(a0)),
           meta::as_<A0>()
           );
    }
  };

  //============================================================================
  // Generates repnum from fusion sequence (support of_size calls)
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repnum_, tag::cpu_,
                              (A0)(Seq),
                              (scalar_<unspecified_<A0> >)
                              (fusion_sequence_<Seq>)
                            )
  {
    typedef typename meta::strip<Seq>::type seq_t;
    typedef typename  boost::proto::
      result_of::make_expr< nt2::tag::repnum_,
      container::domain,
      box<seq_t>,
      box<nt2::details::repnum<A0> >,
      meta::as_<A0>
      >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(const A0& a0, Seq const& seq) const
    {
      return  boost::proto::
        make_expr < nt2::tag::repnum_
        , container::domain
        > (
           boxify(seq),
           boxify(nt2::details::repnum<A0>(a0)),
           meta::as_<A0>()
           );
    }
  };


} }

#endif

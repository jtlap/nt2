//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_RESHAPE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_RESHAPE_HPP_INCLUDED

#include <nt2/core/functions/reshape.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>

#include <nt2/sdk/parameters.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + N size value
  //============================================================================
  #define M3(z,n,t) A##n const& a##n
  #define M2(z,n,t) (A##n)
  #define M1(z,n,t) (scalar_< integer_<A##n> >)

  #define M0(z,n,t)                                                           \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reshape_, tag::cpu_                   \
                            , (A0)                                            \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M2,~) \
                            , ((ast_<A0, nt2::container::domain>))                                      \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M1,~) \
                            )                                                 \
  {                                                                           \
    typedef _##n##D sizes_t;                                                  \
    typedef typename  boost::proto::                                          \
                      result_of::make_expr< nt2::tag::reshape_                \
                                          , container::domain                 \
                                          , A0&                               \
                                          , box<sizes_t>                      \
                                          >::type   result_type;              \
                                                                              \
    BOOST_FORCEINLINE result_type                                             \
    operator()(A0& a0, BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(BOOST_PP_INC(n),A,const& a)) const \
    {                                                                         \
      sizes_t sizee(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n),a));         \
      BOOST_ASSERT_MSG                                                        \
      ( nt2::numel(a0) == nt2::numel(sizee)                                   \
      , "To RESHAPE the number of elements must not change."                  \
      );                                                                      \
      return boost::proto::                                                   \
             make_expr< nt2::tag::reshape_                                    \
                      , container::domain                                     \
                      > ( boost::reference_wrapper<A0>(a0), boxify(sizee) );  \
    }                                                                         \
  };                                                                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M3
  #undef M2
  #undef M1
  #undef M0
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_FILL_PATTERN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_FILL_PATTERN_HPP_INCLUDED

#include <nt2/core/functions/fill_pattern.hpp>
#include <nt2/core/functions/common/fill_pattern.hpp>

#include <nt2/sdk/memory/copy.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/repnum.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + N size value
  //============================================================================
  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(A,n)> >)

  #define M0(z,n,t)                                                           \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fill_pattern_, tag::cpu_                    \
                            , (A0)                                            \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M2,~) \
                            , (ast_<A0>)                                      \
                              BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(n),M1,~) \
                            )                                                 \
  {                                                                           \
    typedef BOOST_PP_CAT(_,BOOST_PP_CAT(n,D)) sizes_t;                        \
    typedef typename  boost::proto::                                          \
                      result_of::make_expr< nt2::tag::fill_pattern_             \
                                          , container::domain                 \
                                          , A0 const&                         \
                                          , box<sizes_t>                      \
                                          >::type   result_type;              \
                                                                              \
    BOOST_FORCEINLINE result_type                                             \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n),A,const& a)) const \
    {                                                                         \
      typedef typename A0::value_type value_type; 
      typedef typename meta::as_integer < value_type>::type              i_t;
      nt2::size_t n = meta::cardinal_of<i_t>:value; 
      sizes_t sizee(BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n),a));         \
      return  boost::proto::                                                  \
              make_expr < nt2::tag::fill_pattern_                               \
                        , container::domain                                   \
                        > ( boost::cref(nt2::repnum(a0, 1, n)), boxify(sizee) );                 \
    }                                                                         \
  };                                                                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M2
  #undef M1
  #undef M0
} }

#endif

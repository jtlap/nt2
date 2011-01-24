/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_FLOATING_HPP_INCLUDED
#define NT2_SDK_META_FLOATING_HPP_INCLUDED

#include <nt2/sdk/meta/make_real.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2  { namespace meta
{
  struct floating
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)>
    {
      typedef float base_real;
      BOOST_STATIC_CONSTANT ( std::size_t
                            , value = (sizeof(A0) > sizeof(base_real))
                                    ?  sizeof(A0) : sizeof(base_real)
                            );
      typedef typename meta::make_real<value>::type type;
    };

    #define M1(z,n,t)                                               \
    BOOST_STATIC_CONSTANT ( std::size_t                             \
                          , BOOST_PP_CAT(value,BOOST_PP_INC(n)) =   \
                            (   BOOST_PP_CAT(value,n)               \
                              > sizeof(BOOST_PP_CAT(A,n))           \
                            ) ? BOOST_PP_CAT(value,n)               \
                              : sizeof(BOOST_PP_CAT(A,n))           \
                          );                                        \
    /**/
    #define M0(z,n,t)                                                     \
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>                  \
    struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))>                       \
    {                                                                     \
      typedef float base_real;                                            \
      BOOST_STATIC_CONSTANT ( std::size_t, value0 =  sizeof(base_real) ); \
      BOOST_PP_REPEAT(n,M1,~)                                             \
      typedef typename                                                    \
      meta::make_real<BOOST_PP_CAT(value,n)>::type type;                  \
    };                                                                    \
     /**/

    BOOST_PP_REPEAT_FROM_TO(2,NT2_MAX_ARITY,M0,~)
    #undef M1
    #undef M0
  };
} }

#endif

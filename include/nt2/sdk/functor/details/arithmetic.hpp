/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_ARITHMETIC_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_ARITHMETIC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// boolean operators implementation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <boost/preprocessor/enum.hpp>
#include <boost/preprocessor/enum_params.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define NT2_LOCAL_VARS(Z,N,T)               \
static BOOST_PP_CAT(A,N) BOOST_PP_CAT(a,N); \
/**/

#define M0(z,n,t) (BOOST_PP_CAT(A,n)) \
/**/

#define M1(z,n,t) (arithmetic_<BOOST_PP_CAT(A,n)>) \
/**/

#define NT2_MAKE_ARITHMETIC(TAG,N,IMPL)                           \
NT2_REGISTER_DISPATCH ( TAG, tag::cpu_                            \
                      , BOOST_PP_REPEAT(N,M0,~)                   \
                      , BOOST_PP_REPEAT(N,M1,~)                   \
                      );                                          \
namespace nt2 { namespace ext                                     \
{                                                                 \
  template<class Dummy>                                           \
  struct call < TAG(BOOST_PP_ENUM_PARAMS( N                       \
                                        , tag::arithmetic_        \
                                          BOOST_PP_INTERCEPT  )   \
                   )                                              \
              , tag::cpu_                                         \
              , Dummy                                             \
              > : callable                                        \
  {                                                               \
    template<class Sig> struct result;                            \
    template<class This,BOOST_PP_ENUM_PARAMS(N,class A)>  struct  \
    result<This(BOOST_PP_ENUM_PARAMS(N,A))>                       \
    {                                                             \
      BOOST_PP_REPEAT(N,NT2_LOCAL_VARS,~)                         \
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested,IMPL)                \
      typedef typename nested::type type;                         \
    };                                                            \
    NT2_FUNCTOR_CALL(N) { return IMPL; }                          \
  };                                                              \
} }                                                               \
/**/

//////////////////////////////////////////////////////////////////////////////
// Generating implementation for operators
//////////////////////////////////////////////////////////////////////////////
NT2_MAKE_ARITHMETIC(tag::neg_             , 1 , (-a0)     )
NT2_MAKE_ARITHMETIC(tag::plus_            , 2 , (a0 +  a1))
NT2_MAKE_ARITHMETIC(tag::minus_           , 2 , (a0 -  a1))
NT2_MAKE_ARITHMETIC(tag::multiplies_      , 2 , (a0 *  a1))
NT2_MAKE_ARITHMETIC(tag::divides_         , 2 , (a0 /  a1))
NT2_MAKE_ARITHMETIC(tag::modulo_          , 2 , (a0 %  a1)) // special case
NT2_MAKE_ARITHMETIC(tag::unary_plus_      , 1 , (+a0)     ) // special case
NT2_MAKE_ARITHMETIC(tag::shift_left_      , 2 , (a0 << a1)) // special case
NT2_MAKE_ARITHMETIC(tag::shift_right_     , 2 , (a0 >> a1)) // special case

#undef M1
#undef M0
#undef NT2_LOCAL_VARS
#undef NT2_MAKE_ARITHMETIC

#endif

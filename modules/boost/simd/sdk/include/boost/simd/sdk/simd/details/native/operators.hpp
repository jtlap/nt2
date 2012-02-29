/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED

#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>
#include <boost/proto/tags.hpp>

#define BOOST_SIMD_OVERLOAD_UNARY_OP(Tag, Op)                                  \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
lazy_enable_if< meta::is_native<A0>                                            \
              , dispatch::meta::                                               \
                call< Tag(A0 const&) >                                         \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 const & a0                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0);                 \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_UNARY_OP_INC(Tag, Op)                              \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< meta::is_native<A0>                                                 \
         , A0&                                                                 \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0                                                                      \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0);                 \
}                                                                              \
template<class A0>                                                             \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< meta::is_native<A0>                                                 \
         , A0                                                                  \
         >::type                                                               \
operator Op                                                                    \
(                                                                              \
  A0 & a0,                                                                     \
  int                                                                          \
)                                                                              \
{                                                                              \
  A0 const that = a0;                                                          \
  operator Op(a0);                                                             \
  return that;                                                                 \
}                                                                              \
/**/


#define BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS(Tag, Op)                            \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
lazy_enable_if< mpl::                                                          \
                or_< mpl::and_< meta::is_native<A0>, meta::is_native<A1> >     \
                   , mpl::                                                     \
                     or_< mpl::and_< meta::is_native<A0>, is_fundamental<A1> > \
                        , mpl::and_< is_fundamental<A0>, meta::is_native<A1> > \
                        >                                                      \
                   >                                                           \
              , dispatch::meta::                                               \
                call< Tag(A0 const&, A1 const&) >                              \
              >::type                                                          \
operator Op                                                                    \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0, a1);             \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN(Tag, Op)                     \
BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS(Tag, Op)                                    \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
enable_if< mpl::and_< meta::is_native<A0>, meta::is_native<A1> >               \
         , A0&                                                                 \
         >::type                                                               \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  A0       & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  return a0 = operator Op(a0, a1);                                             \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                 \
template<class A0, class A1>                                                   \
BOOST_FORCEINLINE                                                              \
typename                                                                       \
lazy_enable_if< mpl::and_< meta::is_native<A0>, meta::is_native<A1> >          \
              , dispatch::meta::                                               \
                call<Tag(A0 const&, A1 const&)>                                \
              >::type                                                          \
operator Op                                                                    \
(                                                                              \
  A0 const & a0,                                                               \
  A1 const & a1                                                                \
)                                                                              \
{                                                                              \
  return typename dispatch::make_functor<Tag, A0>::type()(a0, a1);             \
}                                                                              \
/**/

namespace boost { namespace simd
{
  // unary operators
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::unary_plus  ,  + )
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::negate      ,  - )
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::complement  ,  ~ )
  BOOST_SIMD_OVERLOAD_UNARY_OP( boost::proto::tag::logical_not ,  ! )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( boost::proto::tag::pre_inc , ++ )
  BOOST_SIMD_OVERLOAD_UNARY_OP_INC( boost::proto::tag::pre_dec , -- )
  
  // binary operators
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::bitwise_and , &  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::bitwise_or  , |  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::bitwise_xor , ^  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::plus        , +  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::minus       , -  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::divides     , /  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::multiplies  , *  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::modulus     , %  )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::shift_left  , << )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN( boost::proto::tag::shift_right , >> )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS( boost::proto::tag::logical_and        , && )
  BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS( boost::proto::tag::logical_or         , || )
  
  // comparison operators
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::equal_to        , == )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::not_equal_to    , != )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::less            , <  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::greater         , >  )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::less_equal      , <= )
  BOOST_SIMD_OVERLOAD_BINARY_OP( boost::proto::tag::greater_equal   , >= )
} }

#undef BOOST_SIMD_OVERLOAD_UNARY_OP
#undef BOOST_SIMD_OVERLOAD_UNARY_OP_INC
#undef BOOST_SIMD_OVERLOAD_BINARY_OP
#undef BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS
#undef BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN

#endif

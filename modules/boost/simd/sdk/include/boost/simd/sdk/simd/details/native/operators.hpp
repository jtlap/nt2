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

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/utility/enable_if.hpp>

#define BOOST_SIMD_OVERLOAD_UNARY_OP(Tag, Op)                                  \
template<class T, class X>                                                     \
BOOST_DISPATCH_FORCE_INLINE                                                    \
typename boost::dispatch::meta::call< Tag(native<T, X>) >::type                \
operator Op                                                                    \
(                                                                              \
  native<T, X> const & a0                                                      \
)                                                                              \
{                                                                              \
  return typename boost::dispatch::make_functor<Tag, T>::type()(a0);           \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_UNARY_OP_INC(Tag, Op)                              \
template<class T, class X>                                                     \
BOOST_DISPATCH_FORCE_INLINE                                                    \
native<T, X>&                                                                  \
operator Op                                                                    \
(                                                                              \
  native<T, X> & a0                                                            \
)                                                                              \
{                                                                              \
  return typename boost::dispatch::make_functor<Tag, T>::type()(a0);           \
}                                                                              \
template<class T, class X>                                                     \
BOOST_DISPATCH_FORCE_INLINE                                                    \
native<T, X>                                                                   \
operator Op                                                                    \
(                                                                              \
  native<T, X> & a0,                                                           \
  int                                                                          \
)                                                                              \
{                                                                              \
  native<T, X> const that = { a0() };                                          \
  operator Op(a0);                                                             \
  return that;                                                                 \
}                                                                              \
/**/


#define BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS(Tag, Op)                            \
template<class T0, class T1, class X>                                          \
BOOST_DISPATCH_FORCE_INLINE                                                    \
typename boost::dispatch::meta::call<Tag(native<T0, X>, native<T1, X>)>::type  \
operator Op                                                                    \
(                                                                              \
  native<T0, X> const & a0,                                                    \
  native<T1, X> const & a1                                                     \
)                                                                              \
{                                                                              \
  return typename boost::dispatch::make_functor<Tag, T0>::type()(a0, a1);      \
}                                                                              \
template<class T, class X, class U>                                            \
BOOST_DISPATCH_FORCE_INLINE                                                    \
typename boost::enable_if<                                                     \
  boost::is_fundamental<U>,                                                    \
  native<T, X>                                                                 \
>::type                                                                        \
operator Op                                                                    \
(                                                                              \
  native<T, X> const & a0,                                                     \
  U            const & a1                                                      \
)                                                                              \
{                                                                              \
  return typename boost::dispatch::make_functor<Tag, T>::type()(a0, a1);       \
}                                                                              \
template<class T, class X, class U>                                            \
BOOST_DISPATCH_FORCE_INLINE                                                    \
typename boost::enable_if<                                                     \
  boost::is_fundamental<U>,                                                    \
  native<T, X>                                                                 \
>::type                                                                        \
operator Op                                                                    \
(                                                                              \
  U            const & a0,                                                     \
  native<T, X> const & a1                                                      \
)                                                                              \
{                                                                              \
  return typename boost::dispatch::make_functor<Tag, T>::type()(a0, a1);       \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS_ASSIGN(Tag, Op)                     \
BOOST_SIMD_OVERLOAD_BINARY_OP_ELWS(Tag, Op)                                    \
template<class T, class X, class U>                                            \
BOOST_DISPATCH_FORCE_INLINE                                                    \
native<T, X>&                                                                  \
operator BOOST_PP_CAT(Op, =)                                                   \
(                                                                              \
  native<T, X>       & a0,                                                     \
  U            const & a1                                                      \
)                                                                              \
{                                                                              \
  return a0 = operator Op(a0, a1);                                             \
}                                                                              \
/**/

#define BOOST_SIMD_OVERLOAD_BINARY_OP(Tag, Op)                                 \
template<class T0, class T1, class X>                                          \
BOOST_DISPATCH_FORCE_INLINE                                                    \
typename boost::dispatch::meta::call<Tag(native<T0, X>, native<T1, X>)>::type  \
operator Op                                                                    \
(                                                                              \
  native<T0, X> const & a0,                                                    \
  native<T1, X> const & a1                                                     \
)                                                                              \
{                                                                              \
  return typename boost::dispatch::make_functor<Tag, T0>::type()(a0, a1);      \
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

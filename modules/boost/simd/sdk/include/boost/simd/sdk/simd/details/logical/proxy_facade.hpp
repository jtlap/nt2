//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_LOGICAL_PROXY_FACADE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_LOGICAL_PROXY_FACADE_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>
#include <boost/proto/detail/decltype.hpp>
#include <boost/preprocessor/cat.hpp>

/* Generic proxy forwarder (experiment)
 * -----------------------
 * Getting SFINAE to kick in when using BOOST_PROTO_DECLTYPE_
 * (which internally uses Boost.Typeof) is kinda tricky, and might
 * require BOOST_NO_SFINAE_EXPR to not be set (i.e. GCC 4.3+ or C++0x compiler)
 */

namespace boost { namespace simd { namespace details
{
  template<class T>
  T& make();
  
  template<int>
  struct dummy;
  
  struct two
  {
    char d[2];
  };

  template<class Derived, class T>
  struct proxy_facade
  {
    T operator()() const
    {
      return T(static_cast<Derived const&>(*this));
    }
  };

#define BOOST_SIMD_PROXY_FACADE_UNARY_OP(Name, Op)                             \
template<bool B, class A0>                                                     \
struct BOOST_PP_CAT(Name, _impl)                                               \
{                                                                              \
};                                                                             \
                                                                               \
template<class A0>                                                             \
struct BOOST_PP_CAT(Name, _impl)<true, A0>                                     \
{                                                                              \
  BOOST_PROTO_DECLTYPE_(Op make<A0>(), type);                                  \
};                                                                             \
                                                                               \
template<class A0>                                                             \
struct Name                                                                    \
{                                                                              \
  template<class A0_>                                                          \
  static char test(...);                                                       \
                                                                               \
  template<class A0_>                                                          \
  static two test(dummy<sizeof(Op make<A0_>(), 0)>*);                          \
                                                                               \
  struct impl                                                                  \
    : BOOST_PP_CAT(Name, _impl)<sizeof(test<A0>(0))-1, A0>                     \
  {                                                                            \
  };                                                                           \
};                                                                             \
                                                                               \
template<class Derived, class T>                                               \
BOOST_FORCEINLINE typename Name<T const>::impl::type                           \
operator Op(proxy_facade<Derived, T> const& a0)                                \
{                                                                              \
   return Op a0();                                                             \
}                                                                              \
/**/

#define BOOST_SIMD_PROXY_FACADE_BINARY_OP(Name, Op)                            \
template<bool B, class A0, class A1>                                           \
struct BOOST_PP_CAT(Name, _impl)                                               \
{                                                                              \
};                                                                             \
                                                                               \
template<class A0, class A1>                                                   \
struct BOOST_PP_CAT(Name, _impl)<true, A0, A1>                                 \
{                                                                              \
  BOOST_PROTO_DECLTYPE_(make<A0>() Op make<A1>(), type);                       \
};                                                                             \
                                                                               \
template<class A0, class A1>                                                   \
struct Name                                                                    \
{                                                                              \
  template<class A0_, class A1_>                                               \
  static char test(...);                                                       \
                                                                               \
  template<class A0_, class A1_>                                               \
  static two test(dummy<sizeof(make<A0_>() Op make<A1_>(), 0)>*);              \
                                                                               \
  struct impl                                                                  \
    : BOOST_PP_CAT(Name, _impl)<sizeof(test<A0, A1>(0))-1, A0, A1>             \
  {                                                                            \
  };                                                                           \
};                                                                             \
                                                                               \
template<class Derived, class T, class U>                                      \
BOOST_FORCEINLINE typename Name<T const, U const>::impl::type                  \
operator Op(proxy_facade<Derived, T> const& a0, U const& a1)                   \
{                                                                              \
  return a0() Op a1;                                                           \
}                                                                              \
template<class Derived, class T, class U>                                      \
BOOST_FORCEINLINE typename Name<T const, U>::impl::type                        \
operator Op(proxy_facade<Derived, T> const& a0, U& a1)                         \
{                                                                              \
  return a0() Op a1;                                                           \
}                                                                              \
template<class Derived, class T, class U>                                      \
BOOST_FORCEINLINE typename Name<U const, T const>::impl::type                  \
operator Op(U const& a0, proxy_facade<Derived, T> const& a1)                   \
{                                                                              \
  return a0 Op a1();                                                           \
}                                                                              \
template<class Derived, class T, class U>                                      \
BOOST_FORCEINLINE typename Name<U, T const>::impl::type                        \
operator Op(U& a0, proxy_facade<Derived, T> const& a1)                         \
{                                                                              \
  return a0 Op a1();                                                           \
}                                                                              \
/**/

// TODO do all of them
BOOST_SIMD_PROXY_FACADE_UNARY_OP(logical_not,  !)

BOOST_SIMD_PROXY_FACADE_BINARY_OP(equal,      ==)
BOOST_SIMD_PROXY_FACADE_BINARY_OP(not_equal,  !=)
BOOST_SIMD_PROXY_FACADE_BINARY_OP(shift_left, <<)

#undef BOOST_SIMD_PROXY_FACADE_BINARY_OP
#undef BOOST_SIMD_PROXY_FACADE_UNARY_OP

} } }

#endif

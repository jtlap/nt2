/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/constant/boolean.hpp>

#include <boost/type_traits/is_same.hpp>

namespace nt2 { namespace details
{
  template<typename F, typename R, typename A0, typename Enable = void>
  struct as_native
  {
    typedef R type;
  };
   
  template<typename F, typename R, typename A0>
  struct as_native<F, R, A0, typename boost::enable_if_c<sizeof(R)!=sizeof(A0) || boost::is_same<R, bool>::value>::type>
  {
    typedef A0 type;
  };
  
  template<class T>
  typename boost::disable_if<
    boost::is_same<T, bool>,
    T
  >::type
  maybe_genmask(T const& t)
  {
    return t;
  }
  
  template<class T, class A>
  typename boost::enable_if<
    boost::is_same<A, bool>,
    T
  >::type
  maybe_genmask(A const& t)
  {
    return t ? True<T>() : False<T>();
  }
  
} }

#define M0(z,n,t) ((simd_< unspecified_<A0>, X >))
#define M1(z,n,t) tag::simd_<tag::unspecified_, X>                                  
#define M2(z,n,t) typename meta::scalar_of<A##n>::type
#define M3(z,n,t) a##n[i]

#define M4(z,n,t)                                                            \
NT2_REGISTER_DISPATCH ( tag::map_, tag::cpu_, (Func)(A0)(X)                  \
                      , (unspecified_<Func>)BOOST_PP_REPEAT(n,M0,~)          \
                      )                                                      \
namespace nt2 { namespace ext                                                \
{                                                                            \
  template<class X, class Dummy>                                             \
  struct  call<tag::map_( tag::unspecified_                                  \
                        , BOOST_PP_ENUM(n,M1,~)                              \
                        )                                                    \
              , tag::cpu_, Dummy                                             \
              >                                                              \
    : callable                                                               \
  {                                                                          \
                                                                             \
    template<class Sig> struct result;                                       \
    template<class This,class Func,BOOST_PP_ENUM_PARAMS(n,class A)>          \
    struct result<This(Func, BOOST_PP_ENUM_PARAMS(n,A))>                     \
    {                                                                        \
      typedef typename std::tr1::                                            \
      result_of< typename meta::                                             \
                 strip<Func>::type const( BOOST_PP_ENUM(n,M2,~) )            \
               >::type                                                       \
      rtype;                                                                 \
      typedef typename details::                                             \
      as_native< Func                                                        \
               , rtype                                                       \
               , typename meta::scalar_of<A0>::type                          \
               >::type                                                       \
      stype;                                                                 \
      typedef simd::native<stype, X> type;                                   \
    };                                                                       \
                                                                             \
    template<class Func, BOOST_PP_ENUM_PARAMS(n,class A)>                    \
    typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::type            \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))   \
    {                                                                        \
      typedef typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::type ntype;\
      typedef typename result<call(Func, BOOST_PP_ENUM_PARAMS(n, A))>::stype stype;\
                                                                             \
      NT2_ALIGNED_TYPE(stype) tmp[meta::cardinal_of<A0>::value];             \
                                                                             \
      for(int i = 0; i != meta::cardinal_of<A0>::value; ++i)                 \
        tmp[i] = details::maybe_genmask<stype>(f(BOOST_PP_ENUM(n, M3, ~)));  \
                                                                             \
      return load<ntype>(&tmp[0], 0);                                        \
    }                                                                        \
  };                                                                         \
} }                                                                          \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M4,~)

#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#endif

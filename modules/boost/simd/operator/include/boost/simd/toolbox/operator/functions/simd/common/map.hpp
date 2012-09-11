//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_MAP_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/map.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/functions/simd/common/preprocessed/map.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#undef BOOST_FORCEINLINE
#endif

#define M1(z,n,t) (generic_< unspecified_<A##n> >)
#define M2(z,n,t) typename meta::scalar_of<_A##n>::type
#define M3(z,n,t) extract(a##n, i)
#define M4(z,n,t) (A##n)
#define M5(z,n,t) typename dispatch::meta::as_ref<_A##n>::type a##n

#define M0(z,n,t)                                                              \
namespace boost { namespace simd { namespace ext                               \
{                                                                              \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_, tag::cpu_         \
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)                  \
                            , (unspecified_<Func>)BOOST_PP_REPEAT(n,M1,~)      \
                            )                                                  \
  {                                                                            \
    template<class Sig>                                                        \
    struct result;                                                             \
                                                                               \
    template<class This, class _Func, BOOST_PP_ENUM_PARAMS(n, class _A)>       \
    struct result<This(_Func, BOOST_PP_ENUM_PARAMS(n, _A))>                    \
    {                                                                          \
      typedef typename dispatch::meta::                                        \
      result_of< Func const( BOOST_PP_ENUM(n,M2,~) )                           \
               >::type                                                         \
      rtype;                                                                   \
                                                                               \
      template<class rtype, class Dummy = void>                                \
      struct impl                                                              \
      {                                                                        \
        typedef typename meta::                                                \
                vector_of< rtype, meta::cardinal_of<A0>::value >::type type;   \
        static type call( Func const& f                                        \
                        , BOOST_PP_ENUM(n, M5, ~)                              \
                        )                                                      \
        {                                                                      \
          type that;                                                           \
                                                                               \
          for(size_t i = 0; i != meta::cardinal_of<A0>::value; ++i)            \
            insert(f(BOOST_PP_ENUM(n, M3, ~)), that, i);                       \
                                                                               \
          return that;                                                         \
        }                                                                      \
      };                                                                       \
                                                                               \
      template<class Dummy>                                                    \
      struct impl<void, Dummy>                                                 \
      {                                                                        \
        typedef void type;                                                     \
        static type call( Func const& f                                        \
                        , BOOST_PP_ENUM(n, M5, ~)                              \
                        )                                                      \
        {                                                                      \
          for(size_t i = 0; i != meta::cardinal_of<A0>::value; ++i)            \
            f(BOOST_PP_ENUM(n, M3, ~));                                        \
        }                                                                      \
                                                                               \
      };                                                                       \
                                                                               \
      typedef impl<rtype> impl_;                                               \
      typedef typename impl_::type type;                                       \
    };                                                                         \
                                                                               \
    template<BOOST_PP_ENUM_PARAMS(n, class _A)>                                \
    BOOST_FORCEINLINE                                                          \
    typename result< implement( Func const&                                    \
                              , BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & a)        \
                              )                                                \
                   >::type                                                     \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & a))         \
    {                                                                          \
      return result< implement( Func const&                                    \
                              , BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & a)        \
                              )                                                \
                   >::impl_::call(f, BOOST_PP_ENUM_PARAMS(n, a));              \
                                                                               \
                                                                               \
    }                                                                          \
  };                                                                           \
} } }                                                                          \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M0,~)

#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif

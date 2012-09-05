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
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace details
{
  template<class X, class Y>
  struct best_ext
  {
    typedef X type;
  };

  template<std::size_t N, class Y>
  struct best_ext< tag::simd_emulation_<N>, Y >
  {
    typedef Y type;
  };
} } }

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

#define BINARY_TREE(n, f, name) BOOST_PP_CAT(BINARY_TREE_, n)(f, name)
#define BINARY_TREE_0(f, name)
#define BINARY_TREE_1(f, name) BOOST_PP_CAT(name, 0)
#define BINARY_TREE_2(f, name) typename f<  BOOST_PP_CAT(name, 0), BOOST_PP_CAT(name, 1) >::type
#define BINARY_TREE_3(f, name) typename f< BINARY_TREE_2(f, name), BOOST_PP_CAT(name, 2) >::type
#define BINARY_TREE_4(f, name) typename f< BINARY_TREE_3(f, name), BOOST_PP_CAT(name, 3) >::type
#define BINARY_TREE_5(f, name) typename f< BINARY_TREE_4(f, name), BOOST_PP_CAT(name, 4) >::type
#define BINARY_TREE_6(f, name) typename f< BINARY_TREE_5(f, name), BOOST_PP_CAT(name, 5) >::type
#define BINARY_TREE_7(f, name) typename f< BINARY_TREE_6(f, name), BOOST_PP_CAT(name, 6) >::type
#define BINARY_TREE_8(f, name) typename f< BINARY_TREE_7(f, name), BOOST_PP_CAT(name, 7) >::type

#define M0(z,n,t) ((simd_< unspecified_<A##n>, X##n >))
#define M2(z,n,t) typename meta::scalar_of<_A##n>::type
#define M3(z,n,t) a##n[i]
#define M4(z,n,t) (A##n)(X##n)

#define M5(z,n,t)                                                              \
namespace boost { namespace simd { namespace ext                               \
{                                                                              \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_, tag::cpu_         \
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)                  \
                            , (unspecified_<Func>)BOOST_PP_REPEAT(n,M0,~)      \
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
        typedef simd::native<rtype, BINARY_TREE(n, details::best_ext, X)> type; \
        static type call( Func const& f                                        \
                        , BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & a)              \
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
                        , BOOST_PP_ENUM_BINARY_PARAMS(n, _A, & a)              \
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

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M5,~)

#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#undef BINARY_TREE
#undef BINARY_TREE_0
#undef BINARY_TREE_1
#undef BINARY_TREE_2
#undef BINARY_TREE_3
#undef BINARY_TREE_4
#undef BINARY_TREE_5
#undef BINARY_TREE_6
#undef BINARY_TREE_7
#undef BINARY_TREE_8

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif

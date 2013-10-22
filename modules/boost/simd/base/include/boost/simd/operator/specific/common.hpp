#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_SPECIFIC_COMMON_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_SPECIFIC_COMMON_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// By default, any SIMD implementation falls down to scalar map application if
// nothing is implemented for doing otherwise.
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/include/functions/simd/map.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/print.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/proto/traits.hpp>

#include <boost/simd/operator/specific/utils.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>

#ifdef BOOST_SIMD_LOG_MAP
namespace boost { namespace simd { namespace details
{
  template<class Sig>
  struct MAP_FALLBACK;
} } }
#define BOOST_SIMD_MAP_LOG(Sig) typedef typename boost::dispatch::meta::print< boost::simd::details::MAP_FALLBACK<Sig> >::type _;
#else
#define BOOST_SIMD_MAP_LOG(Sig)
#endif

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/operator/specific/preprocessed/common.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/common.hpp")
#undef BOOST_SIMD_MAP_LOG
#undef BOOST_FORCEINLINE
#endif

////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  #define M0(z,n,t) (A##n)
  #define M1(z,n,t) (unspecified_<A##n>)
  #define M2(z,n,t) unspecified_<A##n>
  #define M3(z,n,t) typename meta::extension_of<BOOST_PP_CAT(A,n)>::type
  #define M4(z,n,t) meta::cardinal_of<BOOST_PP_CAT(A,n)>::value
  #define M5(z,n,t) typename vector_on_ext< typename meta::scalar_of<A##n>::type, N, X >::type
  #define M6(z,n,t) splat<M5(z,n,t)>(a##n)
  #define M7(z,n,t) BOOST_PP_EXPR_IF(n, ||) (meta::cardinal_of<A##n>::value == 1u)

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_DISPATCH_MAX_ARITY, "boost/simd/operator/specific/common.hpp"))
  #include BOOST_PP_ITERATE()

  #undef M7
  #undef M6
  #undef M5
  #undef M4
  #undef M3
  #undef M2
  #undef M1
  #undef M0
} } }

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
#endif

#else
#define n BOOST_PP_ITERATION()

  BOOST_SIMD_REGISTER_DISPATCH_IF( elementwise_<Tag> , tag::formal_
                             , (Tag)BOOST_PP_REPEAT(n,M0,~)
                             , (mpl::not_< any <  mpl::or_
                                                  < boost::proto::
                                                    is_expr<mpl::_>
                                                  , boost::dispatch::
                                                    meta::is_proxy<mpl::_>
                                                  >
                                               , BOOST_PP_ENUM_PARAMS(n,A)
                                               >
                                          >
                                )
                             , BOOST_PP_REPEAT(n,M1,~)
                             )

  template<BOOST_PP_ENUM_PARAMS(n,class A),class Tag, class Dummy>
  struct implement< elementwise_<Tag>( BOOST_PP_ENUM(n,M2,~) )
                  , tag::formal_, Dummy
                  >
  {
    typedef BOOST_DISPATCH_FOLD(n, typename ext_common<, >::type, M3, ~) X;
    static const std::size_t N = BOOST_DISPATCH_FOLD(n, cardinal_common<, >::value, M4, ~);
    static const bool is_splat_case =    N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && (BOOST_PP_REPEAT(n, M7, ~));

    template<bool B, class Dummy2 = void>
    struct splat_or_map
    {
      typedef typename boost::dispatch::meta::
      dispatch_call<Tag(BOOST_PP_ENUM(n, M5, ~))>::type Callee;

      typedef typename boost::dispatch::meta::
      result_of<Callee(BOOST_PP_ENUM(n, M5, ~))>::type type;

      BOOST_FORCEINLINE static type
      call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a))
      {
        return Callee()(BOOST_PP_ENUM(n, M6, ~));
      }
    };

    template<class Dummy2>
    struct splat_or_map<false, Dummy2>
    {
      BOOST_SIMD_MAP_LOG(Tag)

      typedef typename boost::dispatch::meta::
         call<tag::map_ ( dispatch::functor<Tag>
                        , BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & BOOST_PP_INTERCEPT)
                        )
             >::type
      type;

      BOOST_FORCEINLINE static type
      call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a))
      {
        return boost::simd::
               map( dispatch::functor<Tag>(), BOOST_PP_ENUM_PARAMS(n, a) );
      }
    };

    typedef splat_or_map<is_splat_case> impl;
    typedef typename impl::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a)) const
    {
      return impl::call(BOOST_PP_ENUM_PARAMS(n, a));
    }
  };

#undef n
#endif

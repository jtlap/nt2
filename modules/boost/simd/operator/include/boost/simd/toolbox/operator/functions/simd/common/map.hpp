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
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/toolbox/operator/functions/simd/common/preprocessed/map.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#undef BOOST_SIMD_ALIGNED_TYPE
#endif

#define M0(z,n,t) ((simd_< unspecified_<A##n>, X >))
#define M2(z,n,t) typename meta::scalar_of<A##n>::type
#define M3(z,n,t) a##n[i]
#define M4(z,n,t) (A##n)

#define M5(z,n,t)                                                            \
namespace boost { namespace simd { namespace ext                             \
{                                                                            \
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_, tag::cpu_       \
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)(X)             \
                            , (unspecified_<Func>)BOOST_PP_REPEAT(n,M0,~)    \
                            )                                                \
  {                                                                          \
    typedef typename dispatch::meta::                                        \
    result_of< Func const( BOOST_PP_ENUM(n,M2,~) )                           \
             >::type                                                         \
    rtype;                                                                   \
    typedef simd::native<rtype, X> result_type;                              \
                                                                             \
    inline result_type                                                       \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))   \
    {                                                                        \
      BOOST_SIMD_ALIGNED_TYPE(rtype) tmp[meta::cardinal_of<A0>::value];      \
                                                                             \
      for(size_t i = 0; i != boost::simd::meta::cardinal_of<A0>::value; ++i) \
        tmp[i] = f(BOOST_PP_ENUM(n, M3, ~));                                 \
                                                                             \
      return load<result_type>(&tmp[0], 0);                                  \
    }                                                                        \
  };                                                                         \
} } }                                                                        \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY),M5,~)

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

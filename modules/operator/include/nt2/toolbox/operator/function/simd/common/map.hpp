//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAP_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/toolbox/operator/specific/details/maybe_genmask.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/toolbox/operator/function/simd/common/preprocessed/map.hpp>
#else
#include <nt2/extension/parameters.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp") && __INCLUDE_LEVEL__ == 0
#endif

#define M0(z,n,t) ((simd_< unspecified_<A##n>, X >))
#define M2(z,n,t) typename meta::scalar_of<A##n>::type
#define M3(z,n,t) a##n[i]
#define M4(z,n,t) (A##n)

#define M5(z,n,t)                                                            \
namespace nt2 { namespace meta                                               \
{                                                                            \
  NT2_FUNCTOR_IMPLEMENTATION( tag::map_, tag::cpu_                           \
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)(X)             \
                            , (unspecified_<Func>)BOOST_PP_REPEAT(n,M0,~)    \
                            )                                                \
  {                                                                          \
    typedef typename meta::                                                  \
    result_of< typename meta::                                               \
               strip<Func>::type const( BOOST_PP_ENUM(n,M2,~) )              \
             >::type                                                         \
    rtype;                                                                   \
    typedef typename details::                                               \
    as_native< Func                                                          \
             , rtype                                                         \
             , typename meta::scalar_of<A0>::type                            \
             >::type                                                         \
    stype;                                                                   \
    typedef simd::native<stype, X> result_type;                              \
                                                                             \
    inline result_type                                                       \
    operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))   \
    {                                                                        \
      NT2_ALIGNED_TYPE(stype) tmp[meta::cardinal_of<A0>::value];             \
                                                                             \
      for(int i = 0; i != meta::cardinal_of<A0>::value; ++i)                 \
        tmp[i] = details::maybe_genmask<stype>(f(BOOST_PP_ENUM(n, M3, ~)));  \
                                                                             \
      return load<result_type>(&tmp[0], 0);                                  \
    }                                                                        \
  };                                                                         \
} }                                                                          \
/**/

BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M5,~)

#undef M5
#undef M4
#undef M3
#undef M2
#undef M1
#undef M0

#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

#endif

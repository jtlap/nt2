#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_MAP_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_MAP_HPP_INCLUDED

#include <boost/simd/operator/functions/map.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_ref.hpp>

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/operator/functions/simd/common/preprocessed/map.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#undef BOOST_FORCEINLINE
#endif

namespace boost { namespace simd { namespace ext
{
  template<BOOST_PP_ENUM_BINARY_PARAMS(BOOST_DISPATCH_MAX_ARITY, class A, = int BOOST_PP_INTERCEPT)>
  struct map_cardinal_size
  {
    #define M0(z,n,t) meta::cardinal_of<A##n>::value != 1u ? meta::cardinal_of<A##n>::value :
    static const std::size_t value = BOOST_PP_REPEAT(BOOST_DISPATCH_MAX_ARITY, M0, ~) 1u;
    #undef M0
  };

  #define M1(z,n,t) (generic_< unspecified_<A##n> >)
  #define M2(z,n,t) typename meta::scalar_of<A##n>::type
  #define M3(z,n,t) extract(a##n, i)
  #define M4(z,n,t) (A##n)

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_DISPATCH_MAX_ARITY, "boost/simd/operator/functions/simd/common/map.hpp"))
  #include BOOST_PP_ITERATE()

  #undef M4
  #undef M3
  #undef M2
  #undef M1
} } }

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
#endif

#else
#define n BOOST_PP_ITERATION()

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_, tag::cpu_
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)
                            , (unspecified_<Func>)BOOST_PP_REPEAT(n,M1,~)
                            )
  {
    typedef typename dispatch::meta::
    result_of< Func const( BOOST_PP_ENUM(n,M2,~) )
             >::type
    rtype;

    typedef typename meta::
            vector_of< rtype
                     , map_cardinal_size<BOOST_PP_ENUM_PARAMS(n, A)>::value
                     >::type result_type;

    result_type operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a)) const
    {
      result_type that;

      for(size_t i = 0; i != map_cardinal_size<BOOST_PP_ENUM_PARAMS(n, A)>::value; ++i)
        insert(f(BOOST_PP_ENUM(n, M3, ~)), that, i);

      return that;
    }
  };

#endif

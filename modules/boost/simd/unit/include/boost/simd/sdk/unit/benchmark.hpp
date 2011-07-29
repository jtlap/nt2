/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_UNIT_BENCHMARK_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_BENCHMARK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Timing test function macros
// Documentation: http://nt2.lri.fr/sdk/unit/benchmark.html
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_TEST_SILENT
#include <boost/simd/include/timing.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>

#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

////////////////////////////////////////////////////////////////////////////////
// Benchmark parameters
////////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TEST_DURATION
#define BOOST_SIMD_TEST_DURATION 2.5
#endif

#ifndef BOOST_SIMD_TEST_SAMPLES
#define BOOST_SIMD_TEST_SAMPLES 100000
#endif

#if !defined(BOOST_SIMD_TEST_RANDOM_SEED)
#define BOOST_SIMD_TEST_RANDOM_SEED (boost::simd::details::read_cycles())
#endif

////////////////////////////////////////////////////////////////////////////////
// Benchmark entry point
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TEST_CASE( benchmark )
{
  int seed = static_cast<int>(BOOST_SIMD_TEST_RANDOM_SEED);
  srand( seed );
  printf("Benchmark Random Seed: %d \n",seed);
}

////////////////////////////////////////////////////////////////////////////////
// Benchmark functions
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/unit/details/helpers.hpp>
#include <boost/simd/sdk/unit/details/unary_benchmark.hpp>
#include <boost/simd/sdk/unit/details/binary_benchmark.hpp>
#include <boost/simd/sdk/unit/details/ternary_benchmark.hpp>
#include <boost/simd/sdk/unit/details/_4_ary_benchmark.hpp>
#include <boost/simd/sdk/unit/details/_5_ary_benchmark.hpp>

////////////////////////////////////////////////////////////////////////////////
// Benchmark macros
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_MIN_MAX(r,d,e)                                \
, BOOST_PP_TUPLE_ELEM(3,1,e), BOOST_PP_TUPLE_ELEM(3,2,e)  \
/**/

#define BOOST_SIMD_TYPE(r,d,e) BOOST_PP_TUPLE_ELEM(3,0,e),  \
/**/

////////////////////////////////////////////////////////////////////////////////
// Perform runtime benchamrk of a given functor tag
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_TIMING(TAG,SEQ)                         \
BOOST_SIMD_TEST_CASE( BOOST_PP_CAT(timing,__LINE__) )      \
{                                                   \
  typedef boost::simd::functor<TAG> callee_t;          \
  callee_t callee;                                  \
  timing_test                                       \
  <BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_TYPE,~,SEQ)            \
  void*                                             \
  >                                                 \
  ( callee, BOOST_SIMD_TEST_SAMPLES                        \
    BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_MIN_MAX,~,SEQ)        \
  , BOOST_PP_STRINGIZE(TAG)                         \
  );                                                \
}                                                   \
/**/

////////////////////////////////////////////////////////////////////////////////
// Perform runtime benchamrk of a given external function
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_TIMING_EXT(FUNC,RET,SEQ)                                          \
struct BOOST_PP_CAT(wrapper_,__LINE__)                                        \
{                                                                             \
  typedef RET result_type;                                                    \
  template<BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(SEQ),class A)>              \
  inline  RET                                                                 \
  operator()(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_SEQ_SIZE(SEQ),A, const& a)) \
  {                                                                           \
    return FUNC(BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(SEQ),a));              \
  }                                                                           \
};                                                                            \
                                                                              \
BOOST_SIMD_TEST_CASE(BOOST_PP_CAT(timing_,__LINE__))                                 \
{                                                                             \
  BOOST_PP_CAT(wrapper_,__LINE__) callee;                                     \
  timing_test                                                                 \
  <BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_TYPE,~,SEQ)                                      \
  void*                                                                       \
  >                                                                           \
  ( callee, BOOST_SIMD_TEST_SAMPLES                                                  \
    BOOST_PP_SEQ_FOR_EACH(BOOST_SIMD_MIN_MAX,~,SEQ)                                  \
   , BOOST_PP_STRINGIZE(FUNC)                                                 \
  );                                                                          \
}                                                                             \
/**/

#endif

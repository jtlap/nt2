//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_BENCH_BENCHMARK_HPP_INCLUDED

#include <nt2/sdk/config/type_lists.hpp>
#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/bench/suite.hpp>
#include <nt2/sdk/bench/args.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

/// INTERNAL ONLY
#define NT2_PP_TPL_BENCH(r,name,type)                                          \
&& nt2::details::register_benchmark ( BOOST_PP_STRINGIZE(name<type>)           \
                                    , &bench_##name<type>                      \
                                    )                                          \
/**/

/*!
  @brief Single benchmark registration with specific ID

  Create and register a function as a benchmark by creating all the needed
  boilerplate code around the body of the benchmark function itself while using
  a use-defined ID.

  @param ID   Identifier of the registered benchmark
  @param NAME Experiment type used in this benchmark
**/
#define NT2_REGISTER_BENCHMARK_NAMED(ID,NAME)                                  \
void bench_##ID();                                                             \
bool BOOST_PP_CAT(registered_,ID)                                              \
                        = nt2::details::register_benchmark(NAME,&bench_##ID);  \
void bench_##ID()                                                              \
/**/

/*!
  @brief Single benchmark registration

  Create and register a function as a benchmark by creating all the needed
  boilerplate code around the body of the benchmark function itself.

  @param NAME Experiment type used in this benchmark
**/
#define NT2_REGISTER_BENCHMARK(NAME)                                           \
NT2_REGISTER_BENCHMARK_NAMED(NAME,BOOST_PP_STRINGIZE(NAME))                    \
/**/

/*!
  @brief Template benchmarks registration

  Create and register a template function as benchmarks by creating all the
  needed boilerplate code around the body of the benchmark function itself so
  that every instantiation of said function for a type inside the preprocessor
  sequence TYPES is run independently.

  @param NAME   Experiment type used in this benchmark
  @param TYPES  Preprocessor sequence of type to pass to the benchmark function
**/
#define NT2_REGISTER_BENCHMARK_TPL(NAME,TYPES)                                 \
template<typename T> void bench_##NAME();                                      \
bool BOOST_PP_CAT(registered_,NAME) = true                                     \
BOOST_PP_SEQ_FOR_EACH(NT2_PP_TPL_BENCH,NAME,TYPES);                            \
template<typename T> void bench_##NAME()                                       \
/**/

#endif

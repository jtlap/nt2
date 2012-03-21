//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory padding "

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//==============================================================================
// Test if padding do padd along leading dimension
//==============================================================================
NT2_TEST_CASE_TPL(padding_on_non_singular, NT2_TYPES)
{
  using nt2::table;
  using nt2::of_size;
  using boost::proto::value;

  std::size_t N = 256/sizeof(T)-1, M = 2, k = 0;
  table<T> t0( of_size(N,M) );

  for(std::size_t j=1; j<=M; ++j)
    for(std::size_t i=1; i<=N; ++i)
      t0(i, j) = T(k++);

  T* pt0 = value(t0).begin();
  std::size_t rest = value(t0).leading_size() - N; // how many crap to jump over

  for(std::size_t j=1; j<=M; ++j)
  {
    for(std::size_t i=1; i<=N  ;++i) NT2_TEST_EQUAL( T(*pt0++), T(t0(i, j)) );
    for(std::size_t i=0; i<rest;++i) pt0++; // walk over rest of padding
  }
}

NT2_TEST_CASE_TPL(padding_on_singular, NT2_TYPES)
{
  using nt2::table;
  using nt2::of_size;
  using boost::proto::value;

  std::size_t N = 1, M = 256/sizeof(T)-1, k = 0;
  table<T> t0( of_size(N,M) );

  for(std::size_t j=1; j<=M; ++j)
    for(std::size_t i=1; i<=N; ++i)
      t0(i, j) = T(k++);

  T* pt0 = value(t0).begin();

  for(std::size_t j=1; j<=M; ++j)
    for(std::size_t i=1; i<=N; ++i)
      NT2_TEST_EQUAL( T(*pt0++), T(t0(i, j)) );
}

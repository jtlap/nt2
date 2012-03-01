//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory test"


#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>

//==============================================================================
// Test 
//==============================================================================
NT2_TEST_CASE_TPL(test, (float))
{

  using nt2::table;
  using nt2::of_size;
  using boost::proto::value;

  int N = 63;
  int M = 4;

  table<T> t0 (of_size(N,M));

  for(std::size_t j=1; j<=M; ++j){
    for(std::size_t i=1; i<=N; ++i){
      t0(i, j) = (T)((i-1)+(j-1)*N);
    }
  }


  T* pt0 = value(t0).begin();
  for(std::size_t j=0; j < M; ++j){
    for(std::size_t i=0; i<64; ++i){
      std::cout << *pt0 << " ";
      pt0++;
    }
    std::cout <<" \n";
  }

}



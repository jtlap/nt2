/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container allocation"

//#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

#include <iostream>

template<class T> struct std_allocation_test
{
  std_allocation_test(int n, T const& min, T const& max )
    : N(n), i(0)
  {
    // for(std::size_t i=0; i<N; ++i)
    //   a0[i] =  roll<T>(min,max);
  }

  ~std_allocation_test()
  {
    for(int n=0;n<i;++n) alloc.deallocate(a0[n],N);
  }

  void operator()()
  {
    std::cout << "N° " << i << std::endl;
    a0[i] = alloc.allocate(N*sizeof(T));
    ++i;
  }

  std::allocator<T> alloc;
  T* a0[1024];
  int i;
  int N;
};


template<class T> struct boost_simd_allocation_test
{
  boost_simd_allocation_test(int n, T const& min, T const& max )
      : N(n)
  {
    boost::simd::memory::allocator<T> alloc;
    a0 = alloc.allocate(n*sizeof(T));

    // for(std::size_t i=0; i<N; ++i)
    //   a0[i] =  roll<T>(min,max);
  }

  void operator()()
  {

    for(std::size_t i=0; i<N; ++i) 
      a0[i]++;
  }

  T* a0;
  int N;
};


NT2_TEST_CASE( small_table )
{
  typedef float T;

  int N = 128;


  double dw = nt2::unit::perform_benchmark( boost_simd_allocation_test<T>(N,-62.8319, 62.8319), 5.);
  std::cout << "boost_simd_allocation : " << dw/N << " cpe\n";

  double dv = nt2::unit::perform_benchmark( std_allocation_test<T>(N,-62.8319, 62.8319), 5.);


  std::cout << "std_allocation        : " << dv/N << " cpe\n";
}

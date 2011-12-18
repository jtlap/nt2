/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container allocation"

#include <boost/simd/sdk/memory/allocator.hpp>

#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

template<class T> struct std_allocation_test
{
  std_allocation_test(int n) : N(n) { a0.reserve(32768); }

  ~std_allocation_test()
  {
    for(int n=0;n<a0.size();++n) alloc.deallocate(a0[n],N);
  }

  void operator()() { a0.push_back(alloc.allocate(N*sizeof(T))); }

  std::allocator<T> alloc;
  std::vector<T*> a0;
  int N;
};

template<class T> struct simd_allocation_test
{
  simd_allocation_test(int n) : N(n) { a0.reserve(32768); }

  ~simd_allocation_test()
  {
    for(int n=0;n<a0.size();++n) alloc.deallocate(a0[n],N);
  }

  void operator()() { a0.push_back(alloc.allocate(N*sizeof(T))); }

  boost::simd::memory::allocator<T> alloc;
  std::vector<T*> a0;
  int N;
};

NT2_TEST_CASE_TPL( allocation_test, NT2_TYPES )
{
  for(int N=1;N<1024*1024;N*=2)
  {
    simd_allocation_test<T> g(N);
    std_allocation_test<T>  f(N);

    std::cout << "Allocating " << N << "elements.\n";
    double dw = nt2::unit::perform_benchmark(g , 1.);
    std::cout << "boost_simd_allocation : " << dw/N << " cpe\n";

    double dv = nt2::unit::perform_benchmark( f, 1.);
    std::cout << "std_allocation        : " << dv/N << " cpe\n";
  }
}

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
#include <nt2/sdk/memory/fixed_allocator.hpp>

#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

template<class T> struct std_allocation_test
{
  std_allocation_test(int n) : N(n) {}

  ~std_allocation_test()
  {
    for(int n=0;n<a0.size();++n) alloc.deallocate(a0[n],N);
  }

  void operator()() { a0.push_back(alloc.allocate(N)); }

  std::allocator<T> alloc;
  std::vector<T*> a0;
  int N;
};

template<class T> struct simd_allocation_test
{
  simd_allocation_test(int n) : N(n) {}

  ~simd_allocation_test()
  {
    for(int n=0;n<a0.size();++n) alloc.deallocate(a0[n],N);
  }

  void operator()() { a0.push_back(alloc.allocate(N)); }

  boost::simd::memory::allocator<T> alloc;
  std::vector<T*> a0;
  int N;
};

template<class T> struct fixed_allocation_test
{
  fixed_allocation_test(int n) : data(n), alloc(&data[0],&data[0]+n) {}

  void operator()() { a0.push_back(alloc.allocate(data.size())); }

  std::vector<T> data;
  nt2::memory::fixed_allocator<T>  alloc;
  std::vector<T*> a0;
};

NT2_TEST_CASE_TPL( allocation_test, NT2_TYPES )
{
  for(int N = 1; N <= 1*65536*256; N *= 4)
  {
    fixed_allocation_test<T>  i(N);
    simd_allocation_test<T>   g(N);
    std_allocation_test<T>    f(N);

    std::cout << "Allocating " << N << " elements.\n";
    nt2::details::cycles_t dv = nt2::unit::perform_benchmark( f, 1.);
    std::cout << "std::allocator   : " << dv/double(N) << " cpe\n";

    nt2::details::cycles_t dw = nt2::unit::perform_benchmark(g , 1.);
    std::cout << "simd::allocator  : " << dw/double(N) << " cpe\n";

    nt2::details::cycles_t du = nt2::unit::perform_benchmark(i , 1.);
    std::cout << "fixed allocator : " << du/double(N) << " cpe\n";
    std::cout << "\n";
  }
}

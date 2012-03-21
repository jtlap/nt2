/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 buffer bench"

#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/buffer.hpp>

#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <boost/fusion/include/vector_tie.hpp>

template<class T> struct buffer_test
{
  buffer_test ( std::size_t sz ) : data(sz), data2(sz) {}

  void operator()()
  {
    for(std::size_t i = 0; i < data.size(); ++i) data[i] = data2[i];
  }

  nt2::memory::buffer<T> data,data2;
};

template<class T> struct buffer_std_test
{
  buffer_std_test(std::size_t sz) : data(sz), data2(sz) {}

  void operator()()
  {
    for(std::size_t i = 0; i < data.size(); ++i) data[i] = data2[i];
  }

  std::vector<T> data,data2;
};

NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  std::cout << "Size\tnt2::buffer\tstd::vector\toverhead\n";
  std::cout.precision(2);

  for(int i=1;i<=16384;i*=2)
  {
    buffer_std_test<T>  b(i);
    buffer_test<T>      c(i);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( b, 1., dv);
    double d = dv.median / 2.;

    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( c, 1., dw);
    double e = dw.median / 2.;

    std::cout << i << "\t"
              << std::scientific << e/i << "\t"
              << std::scientific << d/i << "\t"
              << std::fixed << ((e-d)/d)*100
              << "\n";
  }
}

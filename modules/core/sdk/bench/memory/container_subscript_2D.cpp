/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container via subscript bench"

#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/table/semantic.hpp>

#include <iostream>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

template<class T> struct container_2D_test
{
  typedef nt2::memory::container<T,nt2::settings()>  buffer_t;

  container_2D_test ( std::size_t s0 )
                    : data(nt2::of_size(s0,s0))
                    , data2(nt2::of_size(s0,s0))
                    , s0_(s0)
  {}

  void operator()()
  {
    for(std::size_t j = 0; j < s0_; ++j)
      for(std::size_t i = 0; i < s0_; ++i)
        data[i+s0_*j] = data2[i+s0_*j];
  }

  void reset() {}

  buffer_t        data,data2;
  std::size_t  s0_;
};

template<class T> struct std_2D_test
{
  std_2D_test(std::size_t n) : s0_(n),data(n*n),data2(n*n) {}

  void operator()()
  {
    for(std::size_t j = 0; j < s0_; ++j)
      for(std::size_t i = 0; i < s0_; ++i)
        data[i+s0_*j] = data2[i+s0_*j];
  }

  void reset() {}

  std::size_t  s0_;
  std::vector<T,boost::simd::memory::allocator<T> > data,data2;
};

NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  std::cout << "Size\tnt2::container\tstd::vector\tover\tover \%\n";
  std::cout.precision(2);

  for(int i=1;i<4096;i*=2)
  {
    std_2D_test<T>        y(i);
    container_2D_test<T>  w(i);

    nt2::unit::benchmark_result<nt2::details::cycles_t> dy;
    nt2::unit::perform_benchmark( y, 1., dy);
    double f = dy.median / 2.;

    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( w, 1., dw);
    double d = dw.median / 2.;

    std::cout << i << "^2\t"
              << std::scientific << d/(i*i) << "\t"
              << std::scientific << f/(i*i) << "\t"
              << std::fixed << (d-f)/(i*i) << "\t"
              << std::fixed << ((d-f)/f)*100 << "\t"
              << "\n";
  }
}

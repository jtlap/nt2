/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 array_buffer bench"

#include <nt2/sdk/memory/array_buffer.hpp>

#include <vector>
#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

template<class T> struct array_buffer_test
{
  typedef nt2::memory::array_buffer<T,boost::mpl::size_t<1024> >  buffer_t;

  array_buffer_test(std::size_t sz) : up(sz)
  {
    for(std::size_t i = 0; i < up; ++i) data[i] = 0;
  }

  ~array_buffer_test() { pump = data[rand() % up]; }

  void operator()()
  {
    for(std::size_t i = 0; i < up; ++i) data[i] = data2[i];
  }

  void reset() {}

  T   v;
  std::size_t up;
  static T    pump;
  buffer_t    data, data2;
};

template<class T> struct array_buffer_std_test
{
  typedef std::vector<T>  buffer_t;

  array_buffer_std_test(std::size_t sz) : data(sz),data2(sz) {}

  ~array_buffer_std_test()
  {
    pump = data[rand() % data.size()];
  }

  void operator()()
  {
    for(std::size_t i = 0; i < data.size(); ++i) data[i] = data2[i];
  }

  void reset() {}

  static T pump;
  buffer_t data,data2;
};

template<class T> struct array_buffer_raw_test
{
  array_buffer_raw_test(std::size_t i) : size_(i)
  {
    for(std::size_t i = 0; i < size_; ++i) data[i] = 0;
  }

  void operator()()
  {
    for(std::size_t i = 0; i < size_; ++i) data[i] = data2[i];
  }

  ~array_buffer_raw_test() { pump = data[rand() % size_]; }

  void reset() {}

  T   data[1024];
  T   data2[1024];
  static T pump;
  int size_;
};

template<class T> T array_buffer_raw_test<T>::pump;
template<class T> T array_buffer_std_test<T>::pump;
template<class T> T array_buffer_test<T>::pump;

NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  std::cout << "Size\tnt2::array\tstd::array\tstd::vector\tarray\%\tvect\%\n";
  std::cout.precision(2);

  for(int i=1;i<=1024;i*=2)
  {
    array_buffer_test<T>      a(i);
    array_buffer_raw_test<T>  b(i);
    array_buffer_std_test<T>  c(i);

    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( a, 1., dv);
    double d = dv.median / 2.;

    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( b, 1., dw);
    double e = dw.median / 2.;

    nt2::unit::benchmark_result<nt2::details::cycles_t> dz;
    nt2::unit::perform_benchmark( c, 1., dz);
    double f = dz.median / 2.;

    std::cout << i << "\t"
              << std::scientific  << d/i            << "\t"
              << std::scientific  << e/i            << "\t"
              << std::scientific  << f/i            << "\t"
              << std::fixed       << ((d-e)/e)*100  << "\t"
              << std::fixed       << ((d-f)/f)*100  << "\n";
  }
}

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container buffer"

#include <nt2/sdk/memory/array_buffer.hpp>

#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

template<class T> struct buffer_test
{
  typedef nt2::memory::array_buffer<T,1024,1>  buffer_t;
  typedef typename buffer_t::size_type              size_type;
  typedef typename buffer_t::difference_type        difference_type;

  buffer_test(size_type sz) : data(sz) {}

  void operator()()
  {
    for(difference_type i = data.lower(); i <= data.upper(); ++i) ++data[i];
  }

  buffer_t data;
};

template<class T> struct raw_test
{
  raw_test(int i) : size_(i) {}

  void operator()()
  {
    for(std::size_t i = 0; i < size_; ++i) ++data[i];
  }

  T   data[1024];
  int size_;
};

NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  for(int i=1;i<=1024;i*=2)
  {
    raw_test<T>     b(i);
    buffer_test<T>  c(i);
    double d = nt2::unit::perform_benchmark( b, 1.);
    double e = nt2::unit::perform_benchmark( c, 1.);
    printf( "Size: %d - array_buffer %3.3f c/e - C array %3.3f c/e"
            " - overhead %3.3f %%\n"
          , i, e/i, d/i, ((e-d)/d)*100
          );
  }
}

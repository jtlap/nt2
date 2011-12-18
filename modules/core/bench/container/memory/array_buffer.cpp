/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container buffer"

#include <nt2/core/container/memory/array_buffer.hpp>

#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

template<class T> struct buffer_test
{
  typedef typename nt2::memory::array_buffer<T,1024*1024>::size_type        size_type;
  typedef typename nt2::memory::array_buffer<T,1024*1024>::difference_type  difference_type;

  buffer_test(size_type sz, difference_type bs) : data(sz,bs), v(1) {}

  void operator()()
  {
    for(difference_type i = data.lower(); i <= data.upper(); ++i) data[i] = v;
  }

  T v;
  nt2::memory::array_buffer<T,1024*1024> data;
};

NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  for(int i=-2;i<=2;++i)
  {
    buffer_test<T> b(1024*1024,i);
    double d = nt2::unit::perform_benchmark( b, 1.);
    std::cout << "array_buffer access (base=" << i << ") : "<< d/1024 << " cpe\n";
  }
}

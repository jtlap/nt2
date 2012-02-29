/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container buffer"

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
  typedef nt2::memory::buffer<T,1>            buffer_t;
  typedef typename buffer_t::size_type        size_type;
  typedef typename buffer_t::difference_type  difference_type;

  buffer_test ( size_type sz)
              : data(boost::fusion::vector_tie(sz))
              , data2(boost::fusion::vector_tie(sz))
  {}

  buffer_test ( buffer_test const& s) : data(s.data), data2(s.data2)  {}

  void operator()()
  {
    for(difference_type i = data.lower(); i <= data.upper(); ++i)
      data(i) = data2(i);
  }

  buffer_t data,data2;
};

template<class T> struct buffer_std_test
{
  buffer_std_test(std::size_t sz) : data(sz), data2(sz) {}

  ~buffer_std_test() {}

  void operator()()
  {
    for(std::size_t i = 0; i < data.size(); ++i) data[i] = data2[i];
  }

  std::vector<T> data,data2;
};

NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  for(int i=1;i<=4096;i*=2)
  {
    buffer_std_test<T>     b(i);
    buffer_test<T>  c(i);
    double d = nt2::unit::perform_benchmark( b, 1.) / 2.;
    double e = nt2::unit::perform_benchmark( c, 1.) / 2.;
    printf( "Size: %d - buffer %3.3f c/e - std::vector %3.3f c/e"
            " - overhead %3.3f %%\n"
          , i, e/i, d/i, ((e-d)/d)*100
          );
  }
}

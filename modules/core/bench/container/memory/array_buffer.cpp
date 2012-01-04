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
#include <vector>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>

#include <boost/fusion/include/vector_tie.hpp>

template<class T> struct buffer_test
{
  typedef nt2::memory::array_buffer<T,1024,1>  buffer_t;
  typedef typename buffer_t::size_type         size_type;
  typedef typename buffer_t::difference_type   difference_type;

  buffer_test(size_type sz) : up(sz+data.lower()-1), v(rand()) {}

  ~buffer_test()
  {
    int i = 1 + rand() % up;
    pump = data[boost::fusion::vector_tie(i)];
  }

  void operator()()
  {
    for(difference_type i = data.lower(); i <= up; ++i)
      data[boost::fusion::vector_tie(i)] = v;
  }

  T   v;
  difference_type up;
  static T pump;
  buffer_t data;
};

template<class T> struct std_test
{
  typedef std::vector<T>  buffer_t;
  typedef typename buffer_t::size_type         size_type;
  typedef typename buffer_t::difference_type   difference_type;

  std_test(size_type sz) : data(sz), v(rand()) {}

  ~std_test()
  {
    pump = data[rand() % data.size()];
  }

  void operator()()
  {
    for(difference_type i = 0; i < data.size(); ++i)
      data[i] = v;
  }

  T   v;
  static T pump;
  buffer_t data;
};

template<class T> struct raw_test
{
  raw_test(int i) : size_(i), v(rand()) {}

  void operator()()
  {
    for(std::size_t i = 0; i < size_; ++i) data[i] = v;
  }

  ~raw_test() { pump = data[rand() % size_]; }

  T   v;
  T   data[1024];
  static T pump;
  int size_;
};

template<class T> T raw_test<T>::pump;
template<class T> T std_test<T>::pump;
template<class T> T buffer_test<T>::pump;


NT2_TEST_CASE_TPL( buffer_access, NT2_TYPES )
{
  double raw[11],buff[11],std_[11];

  for(int i=0;i<11;++i)
  {
    raw_test<T>     b(1 << i);
    raw[i] = nt2::unit::perform_benchmark( b, 1.) / (1 << i);
  }

  for(int i=0;i<11;++i)
  {
    buffer_test<T>     b(1 << i);
    buff[i] = nt2::unit::perform_benchmark( b, 1.) / (1 << i);
  }

  for(int i=0;i<11;++i)
  {
    std_test<T>     b(1 << i);
    std_[i] = nt2::unit::perform_benchmark( b, 1.) / (1 << i);
  }

  for(int i=0;i<11;++i)
  {
    printf( "Size: %d - array_buffer %.6f c/e - C array %.6f c/e - vector %.6f c/e"
            " - overhead %.6f %% - %.6f %%\n"
          , 1<<i, buff[i], raw[i], std_[i]
          , ((buff[i]-raw[i])/raw[i])*100
          , ((buff[i]-std_[i])/std_[i])*100
          );
  }
}

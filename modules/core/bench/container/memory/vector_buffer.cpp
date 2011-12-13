/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container vector_buffer"

#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/core/container/memory/vector_buffer.hpp>

#include <iostream>

template<class T> struct vector_buffer_ctor_test
{
  vector_buffer_ctor_test(std::size_t size, std::size_t base)
    :data(size)
  {
    sz[0] = size;
    bs[0] = base;

    //    data = alloc.allocate(size*sizeof(T));

  }

  ~vector_buffer_ctor_test()
  {
    //    alloc.deallocate(data,size);
  }

  void operator()()
  {
    nt2::memory::vector_buffer<T> buffer(data,sz,bs);
  }

  //  boost::simd::memory::allocator<T> alloc;
  boost::array<std::size_t,1> sz;
  boost::array<std::size_t,1> bs;
  std::vector<T> data;
};


template<class T> struct vector_buffer_acc_test
{
  vector_buffer_acc_test(std::size_t size, std::size_t base)
    : data(size)
  {
    sz[0] = size;
    bs[0] = base;

    b = nt2::meta::as_buffer<std::vector<T> >()(data,sz,bs);
  }

  ~vector_buffer_acc_test()
  {
    //    alloc.deallocate(data,size);
  }

  void operator()()
  {
    for ( int i = b.lower(); i <= b.upper(); ++i )
      ++dereference(b,boost::fusion::single_view<int>(i));
  }

  //  boost::simd::memory::allocator<T> alloc;
  boost::array<std::size_t,1> sz;
  boost::array<std::size_t,1> bs;
  nt2::memory::vector_buffer<T> b;
  std::vector<T> data;
};



NT2_TEST_CASE( vector_buffer_test )
{
  typedef float T;

  int N = 1024*1024;

  vector_buffer_ctor_test<T> f(N,0);
  double dv = nt2::unit::perform_benchmark( f, 1.);
  std::cout << "vector_buffer_ctor              : " << dv/N << " cpe\n";

  vector_buffer_acc_test<T> g(N,0);
  double dw = nt2::unit::perform_benchmark( g, 1.);
  std::cout << "vector_buffer_acc (base = 0)    : " << dw/N << " cpe\n";

  vector_buffer_acc_test<T> h(N,3);
  double dx = nt2::unit::perform_benchmark( h, 1.);
  std::cout << "vector_buffer_acc (base = 3)    : " << dx/N << " cpe\n";

  vector_buffer_acc_test<T> k(N,-2);
  double dy = nt2::unit::perform_benchmark( k, 1.);
  std::cout << "vector_buffer_acc (base = -2)   : " << dy/N << " cpe\n";

}

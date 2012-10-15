/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container iliffe_buffer"

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/array_buffer.hpp>
#include <nt2/sdk/memory/iliffe_buffer.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <iostream>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

template<class T> struct iliffe_buffer_1D_dynamic_test
{
  typedef nt2::memory::
          iliffe_buffer < nt2::memory::buffer<T,1>, void>  buffer_t;

  iliffe_buffer_1D_dynamic_test ( std::ptrdiff_t s0 )
                              : data(boost::fusion::vector_tie(s0))
                              , data2(boost::fusion::vector_tie(s0))
                              , s0_(s0)
  {}

  void operator()()
  {
    for(std::ptrdiff_t i = 1; i <= s0_; ++i) data(i) = data2(i);
  }

  void reset() {}

  buffer_t        data,data2;
  std::ptrdiff_t  s0_;
};

template<class T> struct iliffe_buffer_1D_static_test
{
  typedef nt2::memory::
          iliffe_buffer < nt2::memory::array_buffer<T,256*256,1>
                        , void
                        >                           buffer_t;

  iliffe_buffer_1D_static_test ( std::ptrdiff_t s0 )
                              : data(boost::fusion::vector_tie(s0))
                              , data2(boost::fusion::vector_tie(s0))
                              , s0_(s0)
  {}

  void operator()()
  {
    for(std::ptrdiff_t i = 1; i <= s0_; ++i) data(i) = data2(i);
  }

  void reset() {}

  buffer_t        data,data2;
  std::ptrdiff_t  s0_;
};

template<class T> struct iliffe_buffer_2D_static_test
{
  typedef nt2::memory::
          iliffe_buffer < nt2::memory::array_buffer<T,256*256,1>
                        , nt2::memory::array_buffer<T*,256,1>
                        >                           buffer_t;

  iliffe_buffer_2D_static_test( std::size_t s0, std::size_t s1 )
                              : data( boost::fusion::make_vector(s0,s1) )
                              , data2( boost::fusion::make_vector(s0,s1) )
                              , s0_(s0), s1_(s1)
  {}

  void operator()()
  {
    for(std::ptrdiff_t j = 1; j <= s1_; ++j)
      for(std::ptrdiff_t i = 1; i <= s0_; ++i)
        data(i,j) = data2(i,j);
  }

  void reset() {}

  buffer_t        data,data2;
  std::ptrdiff_t s0_,s1_;
};

template<class T> struct iliffe_buffer_2D_dynamic_test
{
  typedef nt2::memory::
          iliffe_buffer < nt2::memory::buffer<T,1>
                        , nt2::memory::buffer<T*,1>
                        >                           buffer_t;

  typedef typename buffer_t::size_type        size_type;
  typedef typename buffer_t::difference_type  difference_type;

  iliffe_buffer_2D_dynamic_test ( std::size_t s0, std::size_t s1)
                              : data( boost::fusion::make_vector(s0,s1) )
                              , data2( boost::fusion::make_vector(s0,s1) )
                              , s0_(s0), s1_(s1)
  {}

  void operator()()
  {
    for(std::ptrdiff_t j = 1; j <= s1_; ++j)
      for(std::ptrdiff_t i = 1; i <= s0_; ++i)
        data(i,j) = data2(i,j);
  }

  void reset() {}

  buffer_t        data,data2;
  std::ptrdiff_t s0_,s1_;
};

template<class T> struct std_1D_test
{
  std_1D_test(std::ptrdiff_t h, std::ptrdiff_t w) : data(h*w),data2(h*w)
  {}

  void operator()()
  {
    for(std::size_t i = 0; i < data.size(); ++i)
      data[i] = data2[i];
  }

  void reset() {}

  std::vector<T,boost::simd::memory::allocator<T> > data,data2;
};

template<class T> struct std_2D_test
{
  std_2D_test(std::ptrdiff_t h, std::ptrdiff_t w) : data(h*w),data2(h*w)
  {
    s = h;
    d = w;
  }

  void operator()()
  {
    for(std::ptrdiff_t j = 0; j < d; ++j)
      for(std::ptrdiff_t i = 0; i < s; ++i)
        data[i+s*j] = data2[i+s*j];
  }

  void reset() {}

  std::ptrdiff_t d,s;
  std::vector<T,boost::simd::memory::allocator<T> > data,data2;
};

template<class T> void do_large(int H, int W)
{
  iliffe_buffer_1D_dynamic_test<T> b(H*W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> db;
  nt2::unit::perform_benchmark(b, 1., db);
  double d = db.median/2.;

  iliffe_buffer_2D_dynamic_test<T> c(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dc;
  nt2::unit::perform_benchmark(c, 1., dc);
  double e = dc.median/2.;

  std_1D_test<T> z(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dz;
  nt2::unit::perform_benchmark(z, 1., dz);
  double w = dz.median/2.;

  std_2D_test<T> y(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dy;
  nt2::unit::perform_benchmark(y, 1., dy);
  double v = dy.median/2.;

  printf( "%d x %d : 1D %3.3f %3.3f (%3.3f%%) | 2D: %3.3f %3.3f (%3.3f%%)\n"
        , H, W
        , d/(H*W), w/(H*W), ((d-w)/w)*100
        , e/(H*W), v/(H*W), ((e-v)/v)*100
        );
}

NT2_TEST_CASE_TPL( iliffe_buffer_large, (double)(float)(short)(char) )
{
  do_large<T>(320 , 240);
  do_large<T>(640 , 480);
  do_large<T>(1024, 768);
  do_large<T>(2048, 1556);
  do_large<T>(4096, 4096);
}

template<class T> void do_small(int H, int W)
{
  iliffe_buffer_1D_dynamic_test<T> b(H*W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> db;
  nt2::unit::perform_benchmark(b, 1., db);
  double d = db.median/2.;

  std_1D_test<T> z(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dz;
  nt2::unit::perform_benchmark(z, 1., dz);
  double w = dz.median/2.;

  iliffe_buffer_2D_dynamic_test<T> c(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dc;
  nt2::unit::perform_benchmark(c, 1., dc);
  double e = dc.median/2.;

  iliffe_buffer_1D_static_test<T> bs(H*W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dbs;
  nt2::unit::perform_benchmark(bs, 1., dbs);
  double ds = dbs.median/2.;

  iliffe_buffer_2D_static_test<T> cs(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dcs;
  nt2::unit::perform_benchmark(cs, 1., dcs);
  double es = dcs.median/2.;

  std_2D_test<T> y(H,W);
  nt2::unit::benchmark_result<nt2::details::cycles_t> dy;
  nt2::unit::perform_benchmark(y, 1., dy);
  double v = dy.median/2.;

  printf( "%d x %d : 1D %3.3f (%3.3f%%) %3.3f [%3.3f%%] %3.3f "
                  "| 2D %3.3f (%3.3f%%) %3.3f [%3.3f%%] %3.3f \n"
        , H, W
        , d/(H*W), ((d-w)/w)*100, ds/(H*W), ((ds-w)/w)*100  , w/(H*W)
        , e/(H*W), ((e-v)/v)*100, es/(H*W), ((es-v)/v)*100  , v/(H*W)
        );
}

NT2_TEST_CASE_TPL( iliffe_buffer_small, (double)(float)(short)(char) )
{
  for(int W=1;W<=256;W*=2)
    for(int H=1;H<=256;H*=2)
      do_small<T>(H,W);
}

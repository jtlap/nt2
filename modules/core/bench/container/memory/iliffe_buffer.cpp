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
          iliffe_buffer < boost::mpl::size_t<1>
                        , nt2::memory::buffer<T>
                        , nt2::memory::buffer<T*>
                        >                           buffer_t;

  iliffe_buffer_1D_dynamic_test ( std::ptrdiff_t s0
                                , std::ptrdiff_t b0
                                )
                              : data(s0,b0), s0_(s0+b0), b0_(b0)
  {}

  void operator()()
  {
    for(std::ptrdiff_t i = b0_; i < s0_; ++i) ++data[i];
  }

  buffer_t        data;
  std::ptrdiff_t  s0_;
  std::ptrdiff_t  b0_;
};

template<class T> struct iliffe_buffer_1D_static_test
{
  typedef nt2::memory::
          iliffe_buffer < boost::mpl::size_t<1>
                        , nt2::memory::array_buffer<T,256*256>
                        , void
                        >                           buffer_t;

  iliffe_buffer_1D_static_test ( std::ptrdiff_t s0
                                , std::ptrdiff_t b0
                                )
                              : data(s0,b0), s0_(s0+b0), b0_(b0)
  {}

  void operator()()
  {
    for(std::ptrdiff_t i = b0_; i < s0_; ++i) ++data[i];
  }

  buffer_t        data;
  std::ptrdiff_t  s0_;
  std::ptrdiff_t  b0_;
};

template<class T> struct iliffe_buffer_2D_static_test
{
  typedef nt2::memory::
          iliffe_buffer < boost::mpl::size_t<1>
                        , nt2::memory::array_buffer<T,256*256>
                        , nt2::memory::array_buffer<T*,256>
                        >                           buffer_t;

  iliffe_buffer_2D_static_test( std::size_t s0
                                , std::size_t s1
                                , std::ptrdiff_t b0
                                , std::ptrdiff_t b1
                                )
                              : data( boost::fusion::make_vector(s0,s1)
                                    , boost::fusion::make_vector(b0,b1)
                                    )
                              ,s0_(s0+b0), b0_(b0)
                              ,s1_(s1+b1), b1_(b1)
  {}

  void operator()()
  {
    for(std::ptrdiff_t j = b1_; j < s1_; ++j)
      for(std::ptrdiff_t i = b0_; i < s0_; ++i)
        ++data[boost::fusion::vector_tie(i,j)];
  }

  buffer_t        data;
  std::ptrdiff_t s0_,s1_;
  std::ptrdiff_t b0_,b1_;
};

template<class T> struct iliffe_buffer_2D_dynamic_test
{
  typedef nt2::memory::
          iliffe_buffer < boost::mpl::size_t<2>
                        , nt2::memory::buffer<T>
                        , nt2::memory::buffer<T*>
                        >                           buffer_t;
  
  typedef typename buffer_t::size_type        size_type;
  typedef typename buffer_t::difference_type  difference_type;

  iliffe_buffer_2D_dynamic_test ( std::size_t s0
                                , std::size_t s1
                                , std::ptrdiff_t b0
                                , std::ptrdiff_t b1
                                )
                              : data( boost::fusion::make_vector(s0,s1)
                                    , boost::fusion::make_vector(b0,b1)
                                    )
                              ,s0_(s0+b0), b0_(b0)
                              ,s1_(s1+b1), b1_(b1)
  {}

  void operator()()
  {
    for(std::ptrdiff_t j = b1_; j < s1_; ++j)
      for(std::ptrdiff_t i = b0_; i < s0_; ++i)
        ++data[boost::fusion::vector_tie(i,j)];
  }

  buffer_t        data;
  std::ptrdiff_t s0_,s1_;
  std::ptrdiff_t b0_,b1_;
};

template<class T> struct std_1D_test
{
  std_1D_test(std::ptrdiff_t h, std::ptrdiff_t w) : data(h*w)
  {}

  void operator()()
  {
    for(std::size_t i = 0; i < data.size(); ++i)
      ++data[i];
  }

  std::vector<T,boost::simd::memory::allocator<T> > data;
};

template<class T> struct std_2D_test
{
  std_2D_test(std::ptrdiff_t h, std::ptrdiff_t w) : data(h*w)
  {
    s = h;
    d = w;
  }

  void operator()()
  {
    for(std::size_t j = 0; j < d; ++j)
      for(std::size_t i = 0; i < s; ++i)
        ++data[i+s*j];
  }

  std::ptrdiff_t d,s;
  std::vector<T,boost::simd::memory::allocator<T> > data;
};

template<class T> void do_large(int H, int W)
{
  iliffe_buffer_1D_dynamic_test<T> b(H*W,1);
  double d = nt2::unit::perform_benchmark( b, 3.) / 2;
  
  iliffe_buffer_2D_dynamic_test<T> c(H,W,1,1);
  double e = nt2::unit::perform_benchmark( c, 3.) / 2;

  std_1D_test<T> z(H,W);
  double w = nt2::unit::perform_benchmark( z, 3.) / 2;

  std_2D_test<T> y(H,W);
  double v = nt2::unit::perform_benchmark( y, 3.) / 2;

  printf( "%d x %d : 1D %3.3f %3.3f (%3.3f%%) | 2D: %3.3f %3.3f (%3.3f%%)\n"
        , H, W
        , d/(H*W), w/(H*W), ((d-w)/w)*100
        , e/(H*W), v/(H*W), ((e-v)/v)*100
        );
}

NT2_TEST_CASE_TPL( iliffe_buffer_large, (double)(float) )
{
  do_large<T>(320 , 240);
  do_large<T>(640 , 480);
  do_large<T>(1024, 768);
  do_large<T>(2048, 1556);
  do_large<T>(4096, 4096);
}

template<class T> void do_small(int H, int W)
{
  iliffe_buffer_1D_dynamic_test<T> b(H*W,1);
  double d = nt2::unit::perform_benchmark( b, 3.) / 2;
  
  iliffe_buffer_1D_static_test<T> bs(H*W,1);
  double ds = nt2::unit::perform_benchmark( bs, 3.) / 2;
  
  iliffe_buffer_2D_dynamic_test<T> c(H,W,1,1);
  double e = nt2::unit::perform_benchmark( c, 3.) / 2;

  iliffe_buffer_2D_static_test<T> cs(H,W,1,1);
  double es = nt2::unit::perform_benchmark( cs, 3.) / 2;

  std_1D_test<T> z(H,W);
  double w = nt2::unit::perform_benchmark( z, 3.) / 2;

  std_2D_test<T> y(H,W);
  double v = nt2::unit::perform_benchmark( y, 3.) / 2;

  printf( "%d x %d : 1D %3.3f (%3.3f%%) %3.3f [%3.3f%%] %3.3f "
                  "| 2D %3.3f (%3.3f%%) %3.3f [%3.3f%%] %3.3f \n"
        , H, W
        , d/(H*W), ((d-w)/w)*100, ds/(H*W), ((ds-w)/w)*100  , w/(H*W)
        , e/(H*W), ((e-v)/v)*100, es/(H*W), ((es-v)/v)*100  , v/(H*W)
        );
}

NT2_TEST_CASE_TPL( iliffe_buffer_small, (double)(float) )
{
  for(int W=1;W<=256;W*=2)
    for(int H=1;H<=256;H*=2)
      do_small<T>(H,W);
}

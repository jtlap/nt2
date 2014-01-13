//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/unit/details/prng.hpp>

#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>

#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/protocol/until.hpp>

#include <nt2/sdk/bench/setup/geometric.hpp>

#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>

#include <nt2/linalg/details/blas/blas1.hpp>
#include <cmath>
#include <cstdlib>

#include <vector>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct fortran_dot;

template<> struct fortran_dot<float>
{
  static BOOST_FORCEINLINE
  float run(nt2_la_int s, float* x, nt2_la_int incx, float* y, nt2_la_int incy )
  {
    return NT2_F77NAME(sdot)(&s, x, &incx, y, &incy);
  }
};

template<> struct fortran_dot<double>
{
  static BOOST_FORCEINLINE
  double run(nt2_la_int s, double* x, nt2_la_int incx, double* y, nt2_la_int incy )
  {
    return NT2_F77NAME(ddot)(&s, x, &incx, y, &incy);
  }
};

template<typename T> struct dot_mkl
{
  typedef void experiment_is_immutable;
  dot_mkl(std::size_t n)
                  :  size_(n)
  {
    incx = incy = 1;
    x.resize(size_);
    y.resize(size_);
    for(int i = 0; i<size_; i++) x[i] = y[i] = i;
  }

  void operator()()
  {
    res_ = fortran_dot<T>::run(size_, &x[0], incx, &y[0], incy);
  }

  friend std::ostream& operator<<(std::ostream& os, dot_mkl<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_ ; }
  std::size_t flops() const { return 2 ; }

  private:
    nt2_la_int incx, incy;
    T res_;
    std::vector<T> x;
    std::vector<T> y;
    nt2_la_int size_;
};

NT2_REGISTER_BENCHMARK_TPL( dot_mkl, NT2_SIMD_REAL_TYPES )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 2);

  run_during_with< dot_mkl<T> > ( 1.
                                  , geometric(size_min,size_max,size_step)
                                  , gflops<stat::median_>()
                                  );
}

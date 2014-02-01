//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/linalg/details/blas/blas1.hpp>
#include <boost/fusion/include/at.hpp>
#include <cmath>
#include <cstdlib>
#include <vector>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct fortran_axpy;

template<> struct fortran_axpy<float>
{
  static BOOST_FORCEINLINE
  void run( nt2_la_int s, float alpha, float* x, nt2_la_int incx, float* y, nt2_la_int incy )
  {
    NT2_F77NAME(saxpy)( &s, &alpha, x, &incx, y, &incy);
  }
};

template<> struct fortran_axpy<double>
{
  static BOOST_FORCEINLINE
  void run( nt2_la_int s, double alpha, double* x, nt2_la_int incx, double* y, nt2_la_int incy )
  {
    NT2_F77NAME(daxpy)( &s, &alpha, x, &incx, y, &incy);
  }
};

template<typename T> struct axpy_mkl
{
 template<typename Setup>
  axpy_mkl(Setup const& s)
              :  alpha(boost::fusion::at_c<1>(s))
              ,  size_(boost::fusion::at_c<0>(s))
  {
    incx = incy = 1;
    x.resize(size_);
    y.resize(size_);
    for(int i = 0; i<size_; i++) x[i] = y[i] = T(i);
  }

  void operator()()
  {
    fortran_axpy<T>::run(size_, alpha, &x[0], incx, &y[0], incy);
  }

  friend std::ostream& operator<<(std::ostream& os, axpy_mkl<T> const& p)
  {
    return os << "(" << p.size()  << ")";
  }

  void reset()
  {
    x.resize(size_);
    y.resize(size_);
    for(int i = 0; i<size_; i++) x[i] = y[i] = T(i);
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return 2; }

private:
  nt2_la_int incx, incy;
  T alpha;
  std::vector<T> x, y;
  nt2_la_int size_;
};

NT2_REGISTER_BENCHMARK_TPL( axpy_mkl, NT2_SIMD_REAL_TYPES )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 2);
  T alpha = args("alpha", 1.);

  run_during_with< axpy_mkl<T> > ( 1.
                                  , and_( geometric(size_min,size_max,size_step)
                                        , constant(alpha)
                                  )
                                  , gflops<stats::median_>()
                                  );
}

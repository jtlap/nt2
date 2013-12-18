//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/linalg/details/blas/blas1.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>

#ifdef __ANDROID__
  #define TURBOFREQ 1.008000
#else
  #define TURBOFREQ 3.401
#endif
#define NOPS 2.0

template<typename T>
NT2_EXPERIMENT(daxpy_mkl)
{
  public:
    daxpy_mkl(std::size_t const& s, double const& a)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"), alpha(a), size(s)
    {
      incx = incy = 1;
      len_x = s;
      len_y = s;
      x    = (double *)calloc( len_x, sizeof( double ) );
      y    = (double *)calloc( len_y, sizeof( double ) );
      for(int i = 0; i<size; i++) x[i] = y[i] = i;
    }

  virtual void reset()
  {
    free(x);
    free(y);
  }
  virtual void info(std::ostream& os) const { os << size; }

  virtual void run() const
  {
    nt2_la_int sz = size;
    NT2_F77NAME(daxpy)(&size, &alpha, x, &incx, y, &incy);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return(double(size)*NOPS*TURBOFREQ/r.first);
  }

private:
  std::size_t size;
  nt2_la_int incx, incy;
  float      alpha;
  float      *x, *y;
  nt2_la_int len_x, len_y;
};

template<typename T>
NT2_EXPERIMENT(saxpy_mkl)
{
  public:
    saxpy_mkl(std::size_t const& s, float const& a)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"), alpha(a), size(s)
    {
      incx = incy = 1;
      len_x = s;
      len_y = s;
      x    = (float *)calloc( len_x, sizeof( float ) );
      y    = (float *)calloc( len_y, sizeof( float ) );
      for(int i = 0; i<size; i++) x[i] = y[i] = i;
    }

  virtual void reset()
  {
    free(x);
    free(y);
  }

  virtual void info(std::ostream& os) const { os << size; }

  virtual void run() const
  {
    nt2_la_int sz = size;
    NT2_F77NAME(saxpy)(&size, &alpha, x, &incx, y, &incy);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return(double(size)*NOPS*TURBOFREQ/r.first);
  }

private:
  std::size_t size;
  nt2_la_int incx, incy;
  float      alpha;
  float      *x, *y;
  nt2_la_int len_x, len_y;
};

typedef float K;

NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (32,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (64,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (128,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (256,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (512,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (1024,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (2048,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (4096,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (8192,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (16384,2.7f));
NT2_RUN_EXPERIMENT_TPL( saxpy_mkl, (K), (163840,2.7f));

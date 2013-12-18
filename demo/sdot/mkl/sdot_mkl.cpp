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
NT2_EXPERIMENT(ddot_mkl)
{
  public:
    ddot_mkl(std::size_t const& s)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"), size(s)
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
    res = NT2_F77NAME(ddot)(&sz, x, &incx, y, &incy);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return(double(size)*NOPS*TURBOFREQ/r.first);
  }

private:
  std::size_t size;
  nt2_la_int incx, incy;
  mutable T res;
  double *x, *y;
  nt2_la_int len_x, len_y;
};

template<typename T>
NT2_EXPERIMENT(sdot_mkl)
{
  public:
    sdot_mkl(std::size_t const& s)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"), size(s)
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
    res = NT2_F77NAME(sdot)(&sz, x, &incx, y, &incy);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return(double(size)*NOPS*TURBOFREQ/r.first);
  }

private:
  std::size_t size;
  mutable T res;
  nt2_la_int incx, incy;
  float *x, *y;
  nt2_la_int len_x, len_y;
};

typedef float K;
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (16));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (32));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (64));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (128));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (256));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (512));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (1024));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (2048));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (4096));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (8192));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (16384));
NT2_RUN_EXPERIMENT_TPL( sdot_mkl, (K), (163840));

typedef double L;
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (16));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (32));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (64));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (128));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (256));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (512));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (1024));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (2048));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (4096));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (8192));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (16384));
NT2_RUN_EXPERIMENT_TPL( ddot_mkl, (L), (163840));

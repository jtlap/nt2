//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include "/opt/intel/mkl/include/mkl_types.h"
#include "/opt/intel/mkl/include/mkl_cblas.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

#define TURBOFREQ 3.401
#define NOPS 2.0

template<typename T>
NT2_EXPERIMENT(daxpy_mkl)
{
  public:
    daxpy_mkl(std::size_t const& s, double const& a)
    : NT2_EXPRIMENT_CTOR(1., "GFLOPS"), alpha(a), size(s)
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
    cblas_daxpy(size, alpha, x, incx, y, incy);
    //for(int i = 0; i<size; i++) std::cout << y[i] << "\n";
  }

      virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size)*NOPS*TURBOFREQ/r.first);
    }

private:
  std::size_t size;
  MKL_INT     incx, incy;
  double      alpha;
  double      *x, *y;
  MKL_INT     len_x, len_y;
};

template<typename T>
NT2_EXPERIMENT(saxpy_mkl)
{
  public:
    saxpy_mkl(std::size_t const& s, float const& a)
    : NT2_EXPRIMENT_CTOR(1., "GFLOPS"), alpha(a), size(s)
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
    cblas_saxpy(size, alpha, x, incx, y, incy);
    //for(int i = 0; i<size; i++) std::cout << y[i] << "\n";
  }

      virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size)*NOPS*TURBOFREQ/r.first);
    }

private:
  std::size_t size;
  MKL_INT     incx, incy;
  float      alpha;
  float      *x, *y;
  MKL_INT     len_x, len_y;
};


//NT2_RUN_EXPERIMENT_TPL( daxpy_mkl, (double), (8000,2.7f));
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

/*struct saxpy_mkl
{

  saxpy_mkl(std::size_t const& s, float const& a) : alpha(a), size(s)
  {
    incx = incy = 1;
    len_x = s;
    len_y = s;
    x    = (float *)calloc( len_x, sizeof( float ) );
    y    = (float *)calloc( len_y, sizeof( float ) );
    for(int i = 0; i<size; i++) x[i] = y[i] = i;
  }

  ~saxpy_mkl()
  {
    free(x);
    free(y);
  }

  inline void operator()()
  {
    cblas_saxpy(size, alpha, x, incx, y, incy);
    //for(int i = 0; i<size; i++) std::cout << y[i] << "\n";
  }

private:
  std::size_t size;
  MKL_INT     incx, incy;
  float      alpha;
  float      *x, *y;
  MKL_INT     len_x, len_y;
};
*/
/*
int main(int argc, char *argv[])
{
  std::size_t size = atoi(argv[1]);
  double nanotimec;

  std::cout << "saxpy mkl float\n";
  nt2::unit::benchmark_result<nt2::details::cycles_t> fc;
  nt2::unit::perform_benchmark( saxpy_mkl(size,6.558943), 1.0, fc);
  std::cout << "\tcycles/element : "<< fc.median/double(size) << "\n\t";
  //nt2::unit::benchmark_result<double> fd;
  //nt2::unit::perform_benchmark( saxpy_mkl(size,6.558943), 1.0, fd);
  //std::cout << "\ttime : "<< fd.median << "\n\t";
  nanotimec = fc.median/TURBOFREQ;
  //std::cout << "\ttime from cycles : "<< nanotimec << "\n";
  std::cout << (double(size)*NOPS)/nanotimec << "\n";

  std::cout << "saxpy mkl double\n";
  nt2::unit::benchmark_result<nt2::details::cycles_t> dc;
  nt2::unit::perform_benchmark( daxpy_mkl(size,6.558943), 1.0, dc);
  std::cout << "\tcycles/element : "<< dc.median/double(size) << "\n\t";
  //nt2::unit::benchmark_result<double> dd;
  //nt2::unit::perform_benchmark( daxpy_mkl(size,6.558943), 1.0, dd);
  //std::cout << "\ttime : "<< dd.median << "\n\t";
  nanotimec = dc.median/TURBOFREQ;
  //std::cout << "\ttime from cycles : "<< nanotimec << "\n";
  std::cout << (double(size)*NOPS)/nanotimec << "\n";

  return 0;
}
*/

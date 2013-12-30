//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <nt2/sdk/bench/benchmark.hpp>
#include "../include/utils.hpp"

int mandelbrot_work(float a, float b, int max_iter)
{
  int iter = 0;
  float x = 0;
  float y = 0;
  float t;
  do {
     t = x*x - y*y + a;
     y = 2*x*y + b;
     x = t;
     iter++;
    } while ((x*x+y*y<4) && (iter<max_iter));

    return iter;
}

template<typename T> NT2_EXPERIMENT(mandelbrot_scalar)
{
public:
  typedef T value_type;

  mandelbrot_scalar( std::size_t const& h, std::size_t const& w
                , value_type const& a0, value_type const& a1
                , value_type const& b0, value_type const& b1
                , std::size_t const& max_iter
                )
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , size_(h*w), h_(h), w_(w), max_iter_(max_iter), a0_(a0), a1_(a1), b0_(b0), b1_(b1)
  {
    C.resize(h*w);
  }

  virtual void run() const
  {
    std::size_t i, j;
    float da, db;
    float a, b;

    for(i=0; i<h_; i++)
    {
      for(j=0; j<w_; j++)
      {
        C[j+w_*i] = mandelbrot_work(A[j+w_*i], B[j+w_*i], max_iter_);
      }
    }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(h_*w_);
  }

  virtual void info(std::ostream& os) const { os << h_ << "x" << w_; }

  virtual void reset() const
  {
    static int pass = 0;
    if(pass==1)
    {
      utils::save_pgm(C,h_,w_, "test_pgm.pgm");
    }
    C.resize(size_);
    A.resize(size_);

    T interval_A=(a1_-a0_)/(h_-1);
    T new_val=a0_;
    for (std::size_t jj=0;jj<w_;jj++){
      for (std::size_t ii=0;ii<h_;ii++){
        A[jj*h_+ii]=new_val;
        new_val+=interval_A;
      }
      new_val=a0_;
    }
    B.resize(size_);
    new_val=b0_;
    T interval_B=(b1_-b0_)/(w_-1);
    for (std::size_t jj=0;jj<w_;jj++){
      for (std::size_t ii=0;ii<h_;ii++){
        B[jj*h_+ii]=new_val;
      }
      new_val+=interval_B;
    }
    pass++;
  }

  private:
    mutable std::vector<value_type> A, B;
    mutable std::vector<int> C;
    mutable std::size_t size_;
    std::size_t h_, w_, max_iter_;
    value_type a0_, a1_, b0_, b1_;
};

NT2_RUN_EXPERIMENT_TPL( mandelbrot_scalar, (float), (100,100,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_scalar, (float), (200,200,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_scalar, (float), (400,400,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_scalar, (float), (800,800,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_scalar, (float), (1600,1600,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_scalar, (float), (3200,3200,-1.5,0.5,-1.0,1.0,256));

//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/fusion/include/at.hpp>
#include <vector>
#include <iostream>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>

using namespace nt2::bench;
using namespace nt2;

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

template<typename T> struct mandelbrot_scalar
{
  typedef T value_type;
  template<typename Setup>
  mandelbrot_scalar(Setup const& s)
                    :  h_(boost::fusion::at_c<0>(s))
                    ,  w_(boost::fusion::at_c<1>(s))
                    ,  a0_(boost::fusion::at_c<2>(s))
                    ,  a1_(boost::fusion::at_c<3>(s))
                    ,  b0_(boost::fusion::at_c<4>(s))
                    ,  b1_(boost::fusion::at_c<5>(s))
                    ,  max_iter_(boost::fusion::at_c<6>(s))
  {
    size_ = h_ * w_;

    A.resize(size_);
    B.resize(size_);
    C.resize(size_);

    T interval_A=(a1_-a0_)/(h_-1);
    T new_val=a0_;
    for (std::size_t jj=0;jj<w_;jj++){
      for (std::size_t ii=0;ii<h_;ii++){
        A[jj*h_+ii]=new_val;
        new_val+=interval_A;
      }
      new_val=a0_;
    }
    new_val=b0_;
    T interval_B=(b1_-b0_)/(w_-1);
    for (std::size_t jj=0;jj<w_;jj++)
    {
      for (std::size_t ii=0;ii<h_;ii++)
      {
        B[jj*h_+ii]=new_val;
      }
      new_val+=interval_B;
    }
  }

  void operator()()
  {
    std::size_t i, j;

    for(i=0; i<h_; i++)
    {
      for(j=0; j<w_; j++)
      {
        C[j+w_*i] = mandelbrot_work(A[j+w_*i], B[j+w_*i], max_iter_);
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& os, mandelbrot_scalar<T> const& p)
  {
    return os << "(" << p.h_ << " x " << p.w_ << ")";
  }

  std::size_t size() const { return size_; }

private:
  std::size_t h_, w_;
  T a0_, a1_, b0_, b1_;
  std::size_t max_iter_, size_;
  std::vector<value_type> A, B;
  std::vector<int> C;
};

NT2_REGISTER_BENCHMARK_TPL( mandelbrot_scalar, (float) )
{
  std::size_t hmin = args("hmin", 100);
  std::size_t hmax = args("hmax", 1600);
  std::size_t hstep = args("hstep", 2);
  std::size_t wmin = args("wmin", 100);
  std::size_t wmax = args("wmax",1600);
  std::size_t wstep = args("wstep", 2);
  T xmin = args("xmin", -1.5);
  T xmax = args("xmax", 1.5);
  T ymin = args("ymin", -1.5);
  T ymax = args("ymax", 1.5);
  T max_iter = args("max_iter", 256);

  run_during_with< mandelbrot_scalar<float> > ( 1.
                                              , and_( geometric(hmin,hmax,hstep)
                                                    , geometric(wmin,wmax,wstep)
                                                    , constant(xmin)
                                                    , constant(xmax)
                                                    , constant(ymin)
                                                    , constant(ymax)
                                                    , constant(max_iter)
                                                    )
                                              , cycles_per_element<stats::median_>()
                                              );
}

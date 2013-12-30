//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/times.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/arrayfun.hpp>

#include "../include/utils.hpp"

namespace mandelbrot
{

  struct step
  {
    template<class Sig> struct result;
    template<class This, class A0, class A1>
    struct result<This(A0,A1)>
    {
      typedef typename boost::dispatch::meta::
              as_integer<typename boost::dispatch::meta::strip<A0>::type
                        >::type type;
    };

    step(std::size_t const& n) : max_iter_(n) {}

    template<class T>
    typename result<step(T,T)>::type operator()(T const& a, T const& b) const
    {
      typedef typename result<step(T,T)>::type iter_type;
      typedef typename boost::simd::meta::scalar_of<T>::type s_type;
      iter_type iter = nt2::Zero<iter_type>();
      iter_type const o = nt2::One<iter_type>();
      T x = nt2::Zero<T>();
      T y = nt2::Zero<T>();
      T x2,y2,xy,m2;
      typename boost::simd::meta::as_logical<T>::type mask;
      std::size_t i = 0;
      bool flag;
      do
      {
        x2 = x*x;
        y2 = y*y;
        xy = s_type(2)  *x*y;
        x = x2 - y2 + a;
        y = xy + b;
        m2 = x2 + y2;
        mask= m2<s_type(4);
        iter = nt2::seladd(mask, iter, o);
        flag = nt2::any(mask);
        i++;
      }while(flag && i < 256);

      return iter;
    }

    std::size_t max_iter_;
  };
}

template<typename T> NT2_EXPERIMENT(mandelbrot_nt2)
{
public:
  typedef T value_type;

  mandelbrot_nt2( std::size_t const& h, std::size_t const& w
                , value_type const& a0, value_type const& a1
                , value_type const& b0, value_type const& b1
                , std::size_t const& max_iter
                )
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , julia(max_iter), h_(h), w_(w), max_iter_(max_iter), size_(h_*w_), a0_(a0), a1_(a1), b0_(b0), b1_(b1)
  {
    A.resize(nt2::of_size(h_,w_));
    B.resize(nt2::of_size(h_,w_));
    C.resize(nt2::of_size(h_,w_));
  }

  virtual void run() const
  {
    C = arrayfun(julia, A, B);
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
    C.resize(nt2::of_size(h_,w_));
    A.resize(nt2::of_size(h_,w_));

    A=nt2::expand_to(nt2::linspace(a0_,a1_,h_),h_,w_);
    B=nt2::expand_to(nt2::colvect(nt2::linspace(b0_,b1_,w_)),h_,w_);
    pass++;
  }

  private:
    mutable nt2::table<value_type> A, B;
    mutable nt2::table<int> C;
    mandelbrot::step julia;
    std::size_t h_, w_, max_iter_, size_;
    mutable std::size_t step_size_;
    value_type a0_, a1_, b0_, b1_;
};

NT2_RUN_EXPERIMENT_TPL( mandelbrot_nt2, (float), (100,100,-1.5f,0.5f,-1.0f,1.0f,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_nt2, (float), (200,200,-1.5f,0.5f,-1.0f,1.0f,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_nt2, (float), (400,400,-1.5f,0.5f,-1.0f,1.0f,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_nt2, (float), (800,800,-1.5f,0.5f,-1.0f,1.0f,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_nt2, (float), (1600,1600,-1.5f,0.5f,-1.0f,1.0f,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_nt2, (float), (3200,3200,-1.5f,0.5f,-1.0f,1.0f,256));

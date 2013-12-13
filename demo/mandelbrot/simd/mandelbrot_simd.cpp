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
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/any.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/times.hpp>
#include "../include/utils.hpp"
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>


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
      iter_type iter = boost::simd::Zero<iter_type>();
      iter_type const o = boost::simd::One<iter_type>();
      T x = boost::simd::Zero<T>();
      T y = boost::simd::Zero<T>();
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
        iter = boost::simd::seladd(mask, iter, o);
        flag = boost::simd::any(mask);
        i++;
      }while(flag && i < 256);

      return iter;
    }

    std::size_t max_iter_;
  };
}

template<typename T> NT2_EXPERIMENT(mandelbrot_exp)
{
public:
  typedef T value_type;

  mandelbrot_exp( std::size_t const& h, std::size_t const& w
                , value_type const& a0, value_type const& a1
                , value_type const& b0, value_type const& b1
                , std::size_t const& max_iter
                )
  : NT2_EXPRIMENT_CTOR(1., "cycles/elements")
  , h_(h), w_(w), a0_(a0), a1_(a1), b0_(b0), b1_(b1), max_iter_(max_iter), julia(max_iter), size_(h_*w_)
  {
    A.resize(size_);
    B.resize(size_);
    C.resize(size_);
  }

  virtual void run() const
  {
    using boost::simd::pack;
    using boost::simd::aligned_store;
    typedef pack<value_type> type;
    for (std::size_t ii=0;ii<size_;ii+=boost::simd::meta::cardinal_of<type>::value){
      type A_pack = (&A[ii]);
      type B_pack = (&B[ii]);
      aligned_store(julia(A_pack, B_pack), &C[ii]);
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
    for (int jj=0;jj<w_;jj++){
      for (int ii=0;ii<h_;ii++){
        A[jj*h_+ii]=new_val;
        new_val+=interval_A;
      }
      new_val=a0_;
    }
    B.resize(size_);
    new_val=b0_;
    T interval_B=(b1_-b0_)/(w_-1);
    for (int jj=0;jj<w_;jj++){
      for (int ii=0;ii<h_;ii++){
        B[jj*h_+ii]=new_val;
      }
      new_val+=interval_B;
    }
    pass++;
  }

 private:
  mutable std::vector<value_type, boost::simd::allocator<value_type> > A, B;
  mutable std::vector<int, boost::simd::allocator<int> > C;
  mandelbrot::step julia;
  std::size_t h_, w_, max_iter_, size_;
  value_type a0_, a1_, b0_, b1_;
};

NT2_RUN_EXPERIMENT_TPL( mandelbrot_exp, (float), (2000,2000,-1.5,0.5,-1.0,1.0,256));

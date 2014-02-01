//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
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
#include <boost/fusion/include/at.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <vector>
#include <iostream>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

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

template<typename T> struct mandelbrot_nt2
{
  typedef T value_type;
  template<typename Setup>
  mandelbrot_nt2(Setup const& s)
                    :  h_(boost::fusion::at_c<0>(s))
                    ,  w_(boost::fusion::at_c<1>(s))
                    ,  a0_(boost::fusion::at_c<2>(s))
                    ,  a1_(boost::fusion::at_c<3>(s))
                    ,  b0_(boost::fusion::at_c<4>(s))
                    ,  b1_(boost::fusion::at_c<5>(s))
                    ,  max_iter_(boost::fusion::at_c<6>(s))
                    ,  size_(h_*w_)
                    ,  julia(max_iter_)
  {
    A.resize(nt2::of_size(h_,w_));
    B.resize(nt2::of_size(h_,w_));
    C.resize(nt2::of_size(h_,w_));

    A=nt2::expand_to(nt2::linspace(a0_,a1_,h_),h_,w_);
    B=nt2::expand_to(nt2::colvect(nt2::linspace(b0_,b1_,w_)),h_,w_);
  }

  void operator()()
  {
    C = arrayfun(julia, A, B);
  }

  friend std::ostream& operator<<(std::ostream& os, mandelbrot_nt2<T> const& p)
  {
    return os << "(" << p.h_ << " x " << p.w_ << ")";
  }

  std::size_t size() const { return size_; }

  private:
    std::size_t h_, w_;
    value_type a0_, a1_, b0_, b1_;
    std::size_t max_iter_, size_, step_size_, aligned_sz, it;
    mandelbrot::step julia;
    nt2::table<value_type> A, B;
    nt2::table<int> C;
};

NT2_REGISTER_BENCHMARK_TPL( mandelbrot_nt2, (float) )
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

  run_during_with< mandelbrot_nt2<float> > ( 1.
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

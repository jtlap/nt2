//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/fusion/include/at.hpp>
#include <iostream>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename K, typename L>
BOOST_FORCEINLINE void rgb2yuv_work(const K& r, const K& g, const K& b, L *y, L *u, L *v)
{
  *y = 0.299f*r + 0.587f*g + 0.114f*b;
  *u = 0.492f*(b - *y);
  *v = 0.877f*(r - *y);
}

template<typename T> struct rgb2yuv_scalar
{
  template<typename Setup>
  rgb2yuv_scalar(Setup const& s)
                    :  height(boost::fusion::at_c<0>(s))
                    ,  width(boost::fusion::at_c<1>(s))
                    ,  size_(height*width)
  {
    y.resize(size_);
    u.resize(size_);
    v.resize(size_);
    r.resize(size_);
    g.resize(size_);
    b.resize(size_);
    for(std::size_t i=0; i<size_; i++)
      r[i] = g[i] = b[i] = y[i] = u[i] = v[i] = T(i);
  }

  void operator()()
  {
    for(std::size_t it = 0; it < size_; it++)
      rgb2yuv_work(r[it], g[it], b[it], &y[it], &u[it], &v[it]);
  }

  friend std::ostream& operator<<(std::ostream& os, rgb2yuv_scalar<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }

  private:
    int height;
    int width;
    int size_;
    std::vector<T> r, g, b, y, u, v;
};

NT2_REGISTER_BENCHMARK_TPL( rgb2yuv_scalar, (float) )
{
  std::size_t hmin  = args("hmin",  32);
  std::size_t hmax  = args("hmax", 128);
  std::size_t hstep = args("hstep",  2);
  std::size_t wmin  = args("wmin",  32);
  std::size_t wmax  = args("wmax", 128);
  std::size_t wstep = args("wstep",  2);

  run_during_with< rgb2yuv_scalar<float> > ( 1.
                                          , and_( geometric(hmin,hmax,hstep)
                                                , geometric(wmin,wmax,wstep)
                                                )
                                          , cycles_per_element<stats::median_>()
                                          );
}

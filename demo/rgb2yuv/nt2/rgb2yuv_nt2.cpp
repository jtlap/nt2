//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/unit/details/prng.hpp>

#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>

#include <nt2/sdk/bench/protocol/max_iteration.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>

#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>

#include <nt2/sdk/bench/stats/average.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/stats/min.hpp>
#include <nt2/sdk/bench/stats/max.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <fstream>
#include <nt2/table.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/sum.hpp>

#include <boost/fusion/include/at.hpp>

#include <iostream>

using namespace nt2::bench;
using namespace nt2;

template<typename K>
BOOST_FORCEINLINE void rgb2yuv_work(const table<K>& r, const table<K>& g, const table<K>& b, table<K>& y, table<K>& u, table<K>& v)
{
  y = K(0.299f)*r + K(0.587f)*g + K(0.114f)*b;
  u = K(0.492f)*(b - y);
  v = K(0.877f)*(r - y);
}

template<typename T> struct rgb2yuv_nt2
{
  template<typename Setup>
  rgb2yuv_nt2(Setup const& s)
                    :  height(boost::fusion::at_c<0>(s))
                    ,  width(boost::fusion::at_c<1>(s))
                    ,  size_(height*width)
  {
    y.resize(nt2::of_size(size_));
    u.resize(nt2::of_size(size_));
    v.resize(nt2::of_size(size_));
    r.resize(nt2::of_size(size_));
    g.resize(nt2::of_size(size_));
    b.resize(nt2::of_size(size_));

    for(std::size_t i=1; i<=size_; i++)
      r(i) = g(i) = b(i) = y(i) = u(i) = v(i) = T(i-1);
  }

  void operator()()
  {
    rgb2yuv_work(r, g, b, y, u, v);
  }

  friend std::ostream& operator<<(std::ostream& os, rgb2yuv_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_ ; }

  private:
    std::size_t height, width, size_;
    nt2::table<T> r, g, b, y, u, v;
};

NT2_REGISTER_BENCHMARK_TPL( rgb2yuv_nt2, (float) )
{

  std::size_t hmin = args("hmin", 32);
  std::size_t hmax = args("hmax", 128);
  std::size_t hstep = args("hstep", 2);
  std::size_t wmin = args("wmin", 32);
  std::size_t wmax = args("wmax", 128);
  std::size_t wstep = args("wstep", 2);

  run_during_with< rgb2yuv_nt2<float> > ( 1.
                                          , and_( geometric(hmin,hmax,hstep)
                                                , geometric(wmin,wmax,wstep)
                                                )
                                          , cycles_per_element<stats::median_>()
                                          );
}

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

template<typename T> struct rgb2grey_scalar
{
  template<typename Setup>
  rgb2grey_scalar(Setup const& s)
                    :  height(boost::fusion::at_c<0>(s))
                    ,  width(boost::fusion::at_c<1>(s))
                    ,  size_(height*width)
  {
    gr.resize(size_);
    r.resize(size_);
    g.resize(size_);
    b.resize(size_);
    for(std::size_t i=0; i<size_; i++)
      r[i] = g[i] = b[i] = gr[i] = T(i);
  }

  void operator()()
  {
    for(std::size_t it = 0; it < size_; it++)
      gr[it] = T(0.3) * r[it] + T(0.59) * g[it] + T(0.11) * b[it];
  }

  friend std::ostream& operator<<(std::ostream& os, rgb2grey_scalar<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }

  private:
  std::size_t height, width, size_;
  std::vector<T> r, g, b, gr;
};

NT2_REGISTER_BENCHMARK_TPL( rgb2grey_scalar, (float) )
{
  std::size_t hmin  = args("hmin" ,  32   );
  std::size_t hmax  = args("hmax" , 128   );
  std::size_t hstep = args("hstep",   2   );
  std::size_t wmin  = args("wmin" , hmin  );
  std::size_t wmax  = args("wmax" , hmax  );
  std::size_t wstep = args("wstep", hstep );

  run_during_with< rgb2grey_scalar<T> > ( 1.
                                        , and_( geometric(hmin,hmax,hstep)
                                              , geometric(wmin,wmax,wstep)
                                              )
                                        , cycles_per_element<stats::median_>()
                                        );
}

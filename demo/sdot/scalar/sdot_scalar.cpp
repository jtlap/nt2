//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <vector>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/stats/median.hpp>


using namespace nt2::bench;
using namespace nt2;

template<typename T> struct sdot_scalar
{
  typedef void experiment_is_immutable;

  sdot_scalar(std::size_t n)
                  :  size_(n)
  {
    X.resize(size_); Y.resize(size_);
    for(std::size_t i = 1; i<=size_; ++i)
      X[i] = Y[i] = T(i);
  }

  void operator()()
  {
    res_ =0.;
    for (std::size_t ii = 0; ii<size_; ii++)
    {
      res_ = res_ + X[ii] * Y[ii];
    }
  }

  friend std::ostream& operator<<(std::ostream& os, sdot_scalar<T> const& p)
  {
    return os << "(" << p.size()  << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return 2; }

private:
  T res_;
  std::size_t size_;
  typename std::vector<T> X, Y;
};

NT2_REGISTER_BENCHMARK_TPL( sdot_scalar, NT2_SIMD_REAL_TYPES )
{
  std::size_t size_min  = args("size_min",   16);
  std::size_t size_max  = args("size_max", 4096);
  std::size_t size_step = args("size_step",   2);

  run_during_with< sdot_scalar<T> > ( 1.
                                    , geometric(size_min,size_max,size_step)
                                    , gflops<stats::median_>()
                                    );
}

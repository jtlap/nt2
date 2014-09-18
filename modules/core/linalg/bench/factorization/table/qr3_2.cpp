//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/of_size.hpp>
#include "../../flops/qr.hpp"

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct qr3_2_nt2
{
  qr3_2_nt2(std::size_t n)
              :  size_(n)
              , Q(of_size(n,n))
              , R(of_size(n,n))
              , P(of_size(n,n))
  {
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    nt2::tie(Q,R,P) = nt2::qr(input, nt2::matrix_);
  }

  friend std::ostream& operator<<(std::ostream& os, qr3_2_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return ( FLOPS_GEQRF(size_,size_)
                                     + FLOPS_ORGQR(size_,size_,size_) ); }

private:
  std::size_t size_;
  nt2::table<T> input, Q,R,P;
};

NT2_REGISTER_BENCHMARK_TPL( qr3_2_nt2, NT2_SIMD_REAL_TYPES )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< qr3_2_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

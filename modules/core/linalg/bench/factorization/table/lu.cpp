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
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include "../../flops/lu.hpp"

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct lu1_nt2
{
  lu1_nt2(std::size_t n)
              :  size_(n)
  {
    result = nt2::zeros(n,n, nt2::meta::as_<T>());
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    result = nt2::lu(input);
  }

  friend std::ostream& operator<<(std::ostream& os, lu1_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return FLOPS_GETRF(size_,size_)/size_; }

private:
  std::size_t size_;
  nt2::table<T> input, result;
};

NT2_REGISTER_BENCHMARK_TPL( lu1_nt2, NT2_SIMD_REAL_TYPES )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< lu1_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

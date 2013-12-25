//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/stat/median.hpp>

#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/table.hpp>

using nt2::table;
using nt2::of_size;
using namespace nt2::bench;

template<typename T>
struct norm_test
{
  norm_test( std::size_t n) : n_( n ), a(of_size(n_,n_))
  {
    nt2::roll(a,-10.,10.);
  }

  void operator()()
  {
    norm_res = nt2::norm(a, 'I');
  }

  std::size_t size() const { return n_; }

  friend std::ostream& operator<<(std::ostream& os, norm_test<T> const& p)
  {
    return os << p.a.extent();
  }

  private:
  std::size_t   n_;
  T             norm_res;
  nt2::table<T> a;
};

NT2_REGISTER_BENCHMARK_TPL( norm_test, (float)(double) )
{
  std::size_t m = args("min" ,    2);
  std::size_t n = args("max" , 4096);
  std::size_t s = args("step",    2);

  run_during_with< norm_test<T> > ( 1.
                                  , geometric(m,n,s)
                                  , cycles_per_element<stat::median_>()
                                  );
}

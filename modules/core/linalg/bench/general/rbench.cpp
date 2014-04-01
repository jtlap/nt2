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
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <boost/fusion/include/at.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct rbench_nt2
{
  template<typename Setup>
  rbench_nt2(Setup const& s)
              :  w(boost::fusion::at_c<1>(s))
              ,  h(boost::fusion::at_c<0>(s))
  {

    A = nt2::rand(h,w, nt2::meta::as_<T>());
    B = A;
    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    b  = nt2::zeros(h,w, nt2::meta::as_<T>());  }

  void operator()()
  {
    a = A(nt2::_ , 1);
    B(nt2::_,1) = T(1);
    tb = nt2::trans(B);
    b = nt2::mtimes(tb,a);
    B = nt2::mtimes(tb,B);
    a = nt2::inv(B);
    result = nt2::mtimes(a,b);
  }

  friend std::ostream& operator<<(std::ostream& os, rbench_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return h*w; }

private:
  std::size_t w,h;
  nt2::table<T> B,b, tb, result;
  nt2::table<T> A, a ;
};

NT2_REGISTER_BENCHMARK_TPL( rbench_nt2, (float)(double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< rbench_nt2<T> > ( 1.
                                , and_( geometric(size_min,size_max,size_step)
                                      , geometric(size_min,size_max,size_step)
                                      )
                                , absolute_time<stats::median_>()
                                );
}

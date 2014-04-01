//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/linalg/details/utility/llspgen.hpp>
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/transpose.hpp>
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"
#include "../../flops/qr.hpp"
#include <nt2/include/functions/mcsne.hpp>
#include <nt2/include/functions/ls.hpp>
#include <boost/fusion/include/at.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct linsolve_nt2
{
  template<typename Setup>
  linsolve_nt2(Setup const& s)
              :  w(boost::fusion::at_c<1>(s))
              ,  h(boost::fusion::at_c<0>(s))
  {

    nr = 1;
    nt2::tie(a,x,r,b)= nt2::llspgen(h,w,nr,nr,nt2::meta::as_<T>());
    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    }

  void operator()()
  {
    // result = b;
    //  ac = a;
    nt2::ls(boost::proto::value(a),boost::proto::value(b) );
    // result = mcsne(a,b);
    // result = nt2::mtimes(a,b);
    // result = nt2::linsolve(a,b);
  }

  friend std::ostream& operator<<(std::ostream& os, linsolve_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return h*w; }
  std::size_t flops() const {
       // return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,1))/r.second)/1000.;
     // return ((FLOPS_DGEMM(h,w,w))/r.second)/1000.;
    return ((FLOPS_GEQRF(h,w)+ FLOPS_DGETRS(h,1))/size());
    // return (FLOPS_GEQRF(h,w)+ FLOPS_DGETRS(h,1));
  }

private:
  std::size_t w,h,nr;
  nt2::table<T> B,b, tb, result;
  nt2::table<T> A, a, ac ,x , r ;
};

NT2_REGISTER_BENCHMARK_TPL( linsolve_nt2, (float)(double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< linsolve_nt2<T> > ( 1.
                                , and_( geometric(size_min,size_max,size_step)
                                      , geometric(size_min,size_max,size_step)
                                      )
                                , gflops<stats::median_>()
                                );
}

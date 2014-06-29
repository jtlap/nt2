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
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/geqp3.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/options.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include "../../flops/qr.hpp"
#include "details.hpp"

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct qr_float_nt2
{
  qr_float_nt2(std::size_t n)
              :  size_(n)
              , result(of_size(n,n))
  {
    lwork = -1;
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    h1 = w1 = size_;
    tau.resize(nt2::of_size(std::min(w1,h1), 1));
    nt2_la_int lwork_query = -1;
    magma_sgeqp3(h1,w1,0,h1,0,0,work.main(),lwork_query,&i);

    work.prepare_main();
    jpvt = nt2::zeros(w1,1,nt2::meta::as_<nt2_la_int>());
    lwork = work.main_size();

    magma_sgeqp3(h1,w1,input.data(),h1,jpvt.data(),tau.data(),work.main()
                       ,lwork, &i
                       );

    result = input;
       }

  friend std::ostream& operator<<(std::ostream& os, qr_float_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_*size_; }
  std::size_t flops() const { return FLOPS_GEQRF(size_,size_); }

private:
  std::size_t size_;
  nt2::details::workspace<float> work;
  nt2_la_int i,m,lwork,h1,w1;
  nt2::table<T> input, result, tau;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( qr_float_nt2, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< qr_float_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

template<typename T> struct qr_double_nt2
{
  qr_double_nt2(std::size_t n)
              :  size_(n)
              , result(of_size(n,n))
  {
    lwork = -1;
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    h1 = w1 = size_;
    tau.resize(nt2::of_size(std::min(w1,h1), 1));
    nt2_la_int lwork_query = -1;
    magma_dgeqp3(h1,w1,0,h1,0,0,work.main(),lwork_query,&i);

    work.prepare_main();
    jpvt = nt2::zeros(w1,1,nt2::meta::as_<nt2_la_int>());
    lwork = work.main_size();

    magma_dgeqp3(h1,w1,input.data(),h1,jpvt.data(),tau.data(),work.main()
                       ,lwork, &i
                       );

    result = input;
     }

  friend std::ostream& operator<<(std::ostream& os, qr_double_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_*size_; }
  std::size_t flops() const { return FLOPS_GEQRF(size_,size_); }

private:
  std::size_t size_;
  nt2::details::workspace<double> work;
  nt2_la_int i,m,lwork,h1,w1;
  nt2::table<T> input, result, tau;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( qr_double_nt2, (double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< qr_double_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

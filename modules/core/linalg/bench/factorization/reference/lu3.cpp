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
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tri1l.hpp>
#include "../../flops/lu.hpp"
#include "details.hpp"
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct lu3_float_nt2
{
  lu3_float_nt2(std::size_t n)
              :  size_(n)
              , L(of_size(n,n))
              , U(of_size(n,n))
  {
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    m = size();
    jpvt.resize(nt2::of_size(std::min(size_, size_), 1) );
    NT2_F77NAME(sgetrf)( &m, &m, input.data(), &m, jpvt.data(), &info);
    L = nt2::tri1l(input);
    U = nt2::triu(input);

    P = nt2::zeros(m,m, nt2::meta::as_<T>());
    for(std::size_t i = 1; i <= (std::size_t)m;++i)
      P(i,jpvt(i)) = 1;
  }

  friend std::ostream& operator<<(std::ostream& os, lu3_float_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return FLOPS_GETRF(size_,size_); }

private:
  std::size_t size_;
  nt2_la_int info,m;
  nt2::table<T> input, L, U, P;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( lu3_float_nt2, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< lu3_float_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}



template<typename T> struct lu3_double_nt2
{
  lu3_double_nt2(std::size_t n)
              :  size_(n)
              , L(of_size(n,n))
              , U(of_size(n,n))
  {
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    m= size();
    jpvt.resize(nt2::of_size(std::min(size_, size_), 1) );
    NT2_F77NAME(dgetrf)( &m, &m, input.data(), &m, jpvt.data(), &info);
    L = nt2::tri1l(input);
    U = nt2::triu(input);

    P = nt2::zeros(m,m, nt2::meta::as_<T>());
    for(std::size_t i = 1; i <= (std::size_t)m;++i)
      P(i,jpvt(i)) = 1;
  }

  friend std::ostream& operator<<(std::ostream& os, lu3_double_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return FLOPS_GETRF(size_,size_); }

private:
  std::size_t size_;
  nt2_la_int info,m;
  nt2::table<T> input, L,U, P;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( lu3_double_nt2, (double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< lu3_double_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

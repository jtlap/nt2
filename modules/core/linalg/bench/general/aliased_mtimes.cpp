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
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/protocol/until.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/table.hpp>
#include <nt2/linalg/details/blas/mm.hpp>

using nt2::table;
using nt2::of_size;
using namespace nt2::bench;

//==============================================================================
// mtimes with xGEMM benchmark
//==============================================================================
template<typename T>
struct gemm_test
{
  gemm_test ( std::size_t n )
            : n_(n)
            , a1(of_size(n_,n_))
            , a2(of_size(n_,n_))
            , a3(of_size(n_,n_))
  {
    nt2::roll(a1,-10.,10.);
    nt2::roll(a2,-10.,10.);
  }

  void operator()()
  {
    T alpha = T(1);
    T beta  = T(0);
    nt2::details::gemm( "N", "N"
                      , &n_, &n_, &n_
                      , &alpha
                      , a1.data(), &n_
                      , a2.data(), &n_
                      , &beta
                      , a3.data(), &n_
                      );
    a1 = a3;
  }

  std::size_t size() const { return n_; }

  private:
  int   n_,i_;
  nt2::table<T> a1,a2,a3;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, gemm_test<T> const& p)
{
  return os << "(" << p.size() << "x" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( gemm_test, (float)(double) )
{
  std::size_t m = args("min" ,   2);
  std::size_t n = args("max" , 256);
  std::size_t s = args("step",   2);
  std::size_t i = args("iteration",  100);
  std::size_t d = args("duration" , 3.);

  run_until_with< gemm_test<T>  > ( d, i
                                  , geometric(m,n,s)
                                  , absolute_time<stats::median_>()
                                  );
}

//==============================================================================
// mtimes with table benchmark
//==============================================================================
template<typename T>
struct alias_mtimes_test
{
  alias_mtimes_test ( std::size_t n )
                    : n_( n )
                    , a1(of_size(n_,n_))
                    , a2(of_size(n_,n_))
  {
    nt2::roll(a1,-10.,10.);
    nt2::roll(a2,-10.,10.);
  }

  void operator()()
  {
    a1 = nt2::mtimes(a1, a2);
  }

  std::size_t size() const { return n_; }

  friend std::ostream& operator<<(std::ostream& os, alias_mtimes_test<T> const& p)
  {
    return os << p.a1.extent();
  }

  private:
  int   n_,i_;
  nt2::table<T,nt2::_2D> a1,a2;
};

NT2_REGISTER_BENCHMARK_TPL( alias_mtimes_test, (float)(double) )
{
  std::size_t m = args("min" ,   2);
  std::size_t n = args("max" , 256);
  std::size_t s = args("step",   2);
  std::size_t i = args("iteration",  100);
  std::size_t d = args("duration" , 3.);

  run_until_with< alias_mtimes_test<T> > (d, i
                                          , geometric(m,n,s)
                                          , absolute_time<stats::median_>()
                                          , speedup < gemm_test<T>
                                                    , absolute_time<stats::median_>
                                                    >()
                                          );
}

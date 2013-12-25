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
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/stat/median.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/table.hpp>
#include <nt2/linalg/details/blas/mm.hpp>

using nt2::table;
using nt2::of_size;
using namespace nt2::bench;

//==============================================================================
// mtimes with xGEMM benchmark
//==============================================================================
template<typename T>
struct trans_gemm_test
{
  trans_gemm_test() {}

  template<typename Args>
  trans_gemm_test ( Args const& a )
                  : n_( boost::fusion::at_c<0>(a))
                  , i_( boost::fusion::at_c<1>(a))
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
    for(int i = 0; i < i_; ++i)
    {
      nt2::details::gemm( "T", "N"
                        , &n_, &n_, &n_
                        , &alpha
                        , a1.raw(), &n_
                        , a2.raw(), &n_
                        , &beta
                        , a3.raw(), &n_
                        );
    }
  }

  std::size_t size() const { return n_; }

  private:
  int   n_,i_;
  nt2::table<T> a1,a2,a3;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, trans_gemm_test<T> const& p)
{
  return os << "(" << p.size() << "x" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( trans_gemm_test, (float)(double) )
{
  std::size_t m = args("min" ,   2);
  std::size_t n = args("max" , 256);
  std::size_t s = args("step",   2);
  std::size_t i = args("iter", 100);

  run_during_with< trans_gemm_test<T> > ( 1.
                                        , and_( geometric(m,n,s)
                                              , constant(i)
                                              )
                                        , absolute_time<stat::median_>()
                                        );
}

//==============================================================================
// mtimes with table benchmark
//==============================================================================
template<typename T>
struct trans_mtimes_test
{
  trans_mtimes_test() {}

  template<typename Args>
  trans_mtimes_test ( Args const& a )
                    : n_( boost::fusion::at_c<0>(a))
                    , i_( boost::fusion::at_c<1>(a))
                    , a1(of_size(n_,n_))
                    , a2(of_size(n_,n_))
                    , a3(of_size(n_,n_))
  {
    nt2::roll(a1,-10.,10.);
    nt2::roll(a2,-10.,10.);
  }

  void operator()()
  {
    for(int i = 0; i < i_; ++i)
      a3 = nt2::mtimes(a1, a2);
  }

  std::size_t size() const { return n_; }

  friend std::ostream& operator<<(std::ostream& os, trans_mtimes_test<T> const& p)
  {
    return os << p.a1.extent();
  }

  private:
  int   n_,i_;
  nt2::table<T> a1,a2,a3;
};

NT2_REGISTER_BENCHMARK_TPL( trans_mtimes_test, (float)(double) )
{
  std::size_t m = args("min" ,   2);
  std::size_t n = args("max" , 256);
  std::size_t s = args("step",   2);
  std::size_t i = args("iter", 100);

  run_during_with< trans_mtimes_test<T> > ( 1.
                                          , and_( geometric(m,n,s)
                                                , constant(i)
                                                )
                                          , absolute_time<stat::median_>()
                                          , speedup < trans_gemm_test<T>
                                                    , absolute_time<stat::median_>
                                                    >()
                                          );
}

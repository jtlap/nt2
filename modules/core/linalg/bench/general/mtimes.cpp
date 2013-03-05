
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 container mtimes"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/toolbox/linalg/details/blas/mm.hpp>

template<class T> struct mtimes_test
{
  mtimes_test(std::size_t n, std::size_t m, T const& min, T const& max )
    : a1(nt2::of_size(n,m)),
      a2(nt2::of_size(m,n)),
      a3(nt2::of_size(n,n))
    , N(n), M(m)
  {
    for(size_t i = 1; i <= N * M; ++i)
    {
      a1(i) = roll<T>(min,max);
      a2(i) = roll<T>(min,max);
    }
  }

  void operator()()
  {
    for(int i = 0; i < 100; ++i)
      a3 = mtimes(a1, a2);
  }

  void reset() {}

  nt2::table<T> a1,a2,a3;
  std::size_t N,M;
};

template<class T> struct gemm_test
{
  gemm_test(std::size_t n, std::size_t m, T const& min, T const& max )
    : a1(nt2::of_size(m, n)),
      a2(nt2::of_size(n, m)),
      a3(nt2::of_size(m, m))
    , N(n), M(m)
  {
    for(int i = 1; i <= N * M; ++i)
    {
      a1(i) = roll<T>(min,max);
      a2(i) = roll<T>(min,max);
    }
  }


  void operator()()
  {
    T alpha = nt2::One<T>();
    T beta  = nt2::Zero<T>();
    for(int i = 0; i < 100; ++i)
      nt2::details::gemm( "N", "N"
                          , &M, &M, &N
                          , &alpha
                          , a1.raw(), &M
                          , a2.raw(), &N
                          , &beta
                          , a3.raw(), &M
      );

  }

  void reset() {}

  nt2::table<T> a1,a2,a3;
  nt2_la_int N,M;

};

template<class T> void do_test()
{
  std::cout << "Size\tmtimes (c/e)\tmtimes (s)\tgemm (c/e)\tgemm (s)\tG(c/e)\tG(s)\n";

  for(int N=1;N<=256;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "^2\t";
    mtimes_test<T> tt(N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tv.median << "\t";

    gemm_test<T> vv(N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( vv, 1., dw);
    nt2::unit::benchmark_result<double> tw;
    nt2::unit::perform_benchmark( vv, 1., tw);
    std::cout << std::scientific << dw.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tw.median << "\t";

    std::cout << std::fixed << (double)dw.median/dv.median << "\t";
    std::cout << std::fixed << (double)tw.median/tv.median << "\n";
  }
}

NT2_TEST_CASE_TPL( small_table, (double)(float) )
{
  do_test<T>();
}

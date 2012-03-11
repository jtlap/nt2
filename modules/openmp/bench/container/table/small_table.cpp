/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container runner"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/fast_cos.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/fast_sin.hpp>
#include <nt2/include/functions/sqrt.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

template<class T> struct table_test
{
  table_test(int n, int m, T const& min, T const& max )
      : a0(nt2::of_size(n,m)), a1(nt2::of_size(n,m)), a2(nt2::of_size(n,m))
      , N(n), M(m)
  {
    for(std::size_t j=1; j<=M; ++j)
      for(std::size_t i=1; i<=N; ++i)
        a1(i, j) = a2(i, j) = a0(i, j) = roll<T>(min,max);
  }

  void operator()()
  {
    a1 = nt2::sqrt(nt2::cos(a0)/nt2::sin(a0) + a2*a2/a1);
  }

  nt2::container::table<T> a0,a1,a2;
  int N,M;
};

template<class T> struct vector_test
{
  vector_test(int n, int m, T const& min, T const& max )
      : a0(n*m), a1(n*m), a2(n*m)
      , N(n), M(m)
  {
    for(std::size_t i=0; i<M*N; ++i)
      a2[i] = a1[i] = a0[i] = roll<T>(min,max);
  }

  void operator()()
  {
    for(std::size_t i=0; i<M*N; ++i)
      a1[i] = std::sqrt(std::cos(a0[i])/std::sin(a0[i]) + a2[i]*a2[i]/a1[i]);
  }

  std::vector<T> a0,a1,a2;
  int N,M;
};

template<class T> struct vector_omp_test
{
  vector_omp_test(int n, int m, T const& min, T const& max )
      : a0(n*m), a1(n*m), a2(n*m)
      , N(n), M(m)
  {
    for(std::size_t i=0; i<M*N; ++i)
      a2[i] = a1[i] = a0[i] = roll<T>(min,max);
  }

  void operator()()
  {
    #pragma omp parallel for
    for(std::size_t i=0; i<M*N; ++i)
      a1[i] = std::sqrt(std::cos(a0[i])/std::sin(a0[i]) + a2[i]*a2[i]/a1[i]);
  }

  std::vector<T> a0,a1,a2;
  int N,M;
};

template<class T> void do_test()
{
  std::cout << "Size\ttable (c/e)\ttable (s)\tvector (c/e)\tvector (s)";
  std::cout << "\tOvec (c/e)\tvOvec (s) \tG(c/e)\tG(s)\tOG(c/e)\tOG(s)\n";

  for(int N=1;N<=4096;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "\t";
    table_test<T> tt(N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tv.median << "\t";

    vector_test<T> vv(N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( vv, 1., dw);
    nt2::unit::benchmark_result<double> tw;
    nt2::unit::perform_benchmark( vv, 1., tw);
    std::cout << std::scientific << dw.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tw.median << "\t";

    vector_omp_test<T> vo(N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dow;
    nt2::unit::perform_benchmark( vo, 1., dow);
    nt2::unit::benchmark_result<double> tow;
    nt2::unit::perform_benchmark( vo, 1., tow);
    std::cout << std::scientific << dow.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tow.median << "\t";
    std::cout << std::fixed << (double)dw.median/dv.median << "\t";
    std::cout << std::fixed << (double)tw.median/tv.median << "\t";
    std::cout << std::fixed << (double)dow.median/dv.median << "\t";
    std::cout << std::fixed << (double)tow.median/tv.median << "\n";
  }
}

NT2_TEST_CASE_TPL( small_table, (double)(float) )
{
  do_test<T>();
}

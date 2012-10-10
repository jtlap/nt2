
/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container norm"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

template<class T> struct expr_test
{
  expr_test(std::size_t n, std::size_t m, T const& min, T const& max )
      : a1(nt2::of_size(n,m)),
        a2(nt2::of_size(n,m)),
        a3(nt2::of_size(n,m))
      , N(n), M(m)
  {

  }

  void operator()()
  {
    nn = nt2::norm(a1+a2, 'I');
  }

  void reset() {}

  nt2::table<T> a1,a2,a3;
  std::size_t N,M;
  T nn;
};

template<class T> struct tabl_test
{
  tabl_test(std::size_t n, std::size_t m, T const& min, T const& max )
      : a1(nt2::of_size(n,m)), a2(nt2::of_size(n,m)), a3(nt2::of_size(n,m))
      , N(n), M(m)
  {
  }

  void operator()()
  {
    a3 = a1+a2;
    nn = nt2::norm(a3, 'I');
  }

  void reset() {}

  nt2::table<T> a1,a2, a3;
  std::size_t N,M;
  T nn;
};

template<class T> void do_test()
{
  std::cout << "Size\texpr (c/e)\texpr (s)\ttable (c/e)\ttable (s)\tG(c/e)\tG(s)\n";

  for(int N=1;N<=4096;N*=2)
  {
    std::cout.precision(3);
    std::cout << N << "^2\t";
    tabl_test<T> tt(N,N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tv.median << "\t";

    expr_test<T> vv(N,N,-.28319, .28319);
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

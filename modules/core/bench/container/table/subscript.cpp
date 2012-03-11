/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container subscript"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

namespace subscript_test {

  template<class T> struct table_2D_test
  {
    table_2D_test(std::size_t n, std::size_t m, T const& min, T const& max)
      : a0(nt2::of_size(n,m)), a1(nt2::of_size(n,m)), N(n), M(m)
    {
      for (std::size_t j = 1; j <= M; ++j)
        for (std::size_t i = 1; i <= N; ++i)
          a1(i, j) = roll<T>(min,max);
    }

    void operator()()
    {
      for (std::size_t j = 1; j <= M; j++)
        for (std::size_t i = 1; i <= N; i++)
        {
          a0(i,j) = a1(i,j);
        }
    }

    nt2::container::table<T, nt2::_2D> a0, a1;
    std::size_t N, M;
  };

  template<class T> struct vector_2D_test
  {
    vector_2D_test(std::size_t n, std::size_t m, T const& min, T const& max)
      : a0(n*m), a1(n*m), N(n), M(m)
    {
      for(std::size_t i = 0; i < M*N; ++i)
        a1[i] = roll<T>(min,max);
    }

    void operator()()
    {
      for (std::size_t j = 0; j < M; j++)
        for (std::size_t i = 0; i < N; i++)
          a0[i + j * N] = a1[i + j * N];
    }

    std::vector<T> a0, a1;
    std::size_t N, M;
  };

  template<class T> void do_2D_test()
  {
    std::cout << "Size\ttable (c/e)\ttable (s)\tvector (c/e)\tvector (s)\tG(c/e)\tG(s)\n";

    for(int N=1;N<=2048;N*=2)
    {
      std::cout.precision(3);
      std::cout << N << "^2\t";
      table_2D_test<T> tt(N,N,-.28319, .28319);
      nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
      nt2::unit::perform_benchmark( tt, 1., dv);
      nt2::unit::benchmark_result<double> tv;
      nt2::unit::perform_benchmark( tt, 1., tv);
      std::cout << std::scientific << dv.median/(double)(N*N) << "\t";
      std::cout << std::scientific << tv.median << "\t";
      vector_2D_test<T> vv(N,N,-.28319, .28319);
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

  template<class T> struct table_1D_test
  {
    table_1D_test(std::size_t n, T const& min, T const& max)
      : a0(nt2::of_size(n)), a1(nt2::of_size(n)), N(n)
    {
      for (std::size_t i = 1; i <= N; ++i)
        a1(i) = roll<T>(min,max);
    }

    void operator()()
    {
      for (std::size_t i = 1; i <= N; i++)
        a0(i) = a1(i);
    }
    
    nt2::container::table<T, nt2::_1D> a0, a1;
    std::size_t N;
  };

  template<class T> struct vector_1D_test
  {
    vector_1D_test(std::size_t n, T const& min, T const& max)
      : a0(n), a1(n), N(n)
    {
      for (std::size_t i = 0; i < N; ++i)
        a1[i] = roll<T>(min,max);
    }

    void operator()()
    {
      for (std::size_t i = 0; i < N; i++)
        a0[i] = a1[i];
    }

    std::vector<T> a0, a1;
    std::size_t N;
  };

  template<class T> void do_1D_test()
  {
    std::cout << "Size\ttable (c/e)\ttable (s)\tvector (c/e)\tvector (s)\tG(c/e)\tG(s)\n";

    for(int N=1;N<=2048;N*=2)
    {
      std::cout.precision(3);
      std::cout << N*N << "\t";
      table_1D_test<T> tt(N*N,-.28319, .28319);
      nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
      nt2::unit::perform_benchmark( tt, 1., dv);
      nt2::unit::benchmark_result<double> tv;
      nt2::unit::perform_benchmark( tt, 1., tv);
      std::cout << std::scientific << dv.median/(double)(N*N) << "\t";
      std::cout << std::scientific << tv.median << "\t";
      vector_1D_test<T> vv(N*N,-.28319, .28319);
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
}

NT2_TEST_CASE_TPL( subscript_1D, (char)(short)(float)(double) )
{
  subscript_test::do_1D_test<T>();
}

NT2_TEST_CASE_TPL( subscript_2D, (char)(short)(float)(double) )
{
  subscript_test::do_2D_test<T>();
}

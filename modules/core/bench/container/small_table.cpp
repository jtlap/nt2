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
#include <nt2/include/functions/sin.hpp>

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
    a1 = nt2::cos(a0)*nt2::cos(a0) + nt2::sin(a0)*nt2::sin(a0);
    //a1 = a0 + a2;
  }

  nt2::container::table<T,nt2::_2D> a0,a1,a2;
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
      a1[i] = std::cos(a0[i])*std::cos(a0[i]) + std::sin(a0[i])*std::sin(a0[i]);
      //a1[i] = a0[i]+ a2[i];
  }

  std::vector<T> a0,a1,a2;
  int N,M;
};

NT2_TEST_CASE( small_table )
{
  typedef double T;

  int N = 4096, M = 4096;

  std::cout << "table (simd)   : \n\t";
  double dv = nt2::unit::perform_benchmark( table_test<T>(N,M,-62.8319, 62.8319), 10.);
  std::cout << "\tcycles/element : "<< dv/(N*M) << "\n";

  std::cout << "std::vector   : \n\t";
  double dw = nt2::unit::perform_benchmark( vector_test<T>(N,M,-62.8319, 62.8319), 10.);
  std::cout << "\tcycles/element : "<< dw/(N*M) << "\n";

  std::cout << "speed-up    : " << dw/dv << "\n";
}

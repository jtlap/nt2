/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container vs C container"

#include <cstdio>
#include <cmath>

#include <nt2/table.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/tic.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/constants/one.hpp>

#include <nt2/sdk/unit/module.hpp>

using namespace nt2;
using namespace nt2::meta;

inline void raw_calc(int n, const double *a, const double *b, double *y)
{
  for (int i = 0; i < n; ++i)
  {
    double v = a[i] - b[i];
    y[i] = std::exp( (v * v) * 0.5 );
  }
}


inline void perelem_calc(const table<double>& a, const table<double>& b, table<double>& y)
{
  int n = width(a);

  for (int j = 1; j <= n; ++j)
  {
    for (int i = 1; i <= n; ++i)
    {
      double v = a(i, j) - b(i, j);
      y(i, j) = exp( (v * v) * 0.5 );
    }
  }
}

inline void percol_calc(const table<double>& a, const table<double>& b, table<double>& y)
{
  int n = width(a);

  for (int j = 1; j <= n; ++j)
  {
    y(_, j) = exp(sqr(a(_, j) - b(_, j)) * 0.5);
  }
}

NT2_TEST_CASE(c_vs_table)
{
  const int m = 2000;
  const int n = 2000;
  const int T = 10;

  table<double> a = rand(m, n);
  table<double> b = rand(m, n);
  table<double> y = zeros(m, n);

  tic();
  for (int t = 0; t < T; ++t)
    raw_calc(m * n, a.raw(), b.raw(), y.raw());
  double et0 = toc();

  tic();
  for (int t = 0; t < T; ++t)
    y = exp(sqr(a - b) * 0.5);
  double et1 = toc();

  tic();
  for (int t = 0; t < T; ++t)
    percol_calc(a, b, y);
  double et2 = toc();

  tic();
  for (int t = 0; t < T; ++t)
    perelem_calc(a, b, y);
  double et3 = toc();

  std::printf("%8s : %.6f s\n", "raw", et0);
  std::printf("%8s : %.6f s, speedup = %.2fx\n", "matrix", et1, et0 / et1);
  std::printf("%8s : %.6f s, speedup = %.2fx\n", "percol", et2, et0 / et2);
  std::printf("%8s : %.6f s, speedup = %.2fx\n", "perelem", et3, et0 / et3);
}


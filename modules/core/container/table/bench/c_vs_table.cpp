/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/tic.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/constants/one.hpp>

#include <nt2/sdk/bench/benchmark.hpp>

#include <cstdio>
#include <cmath>

NT2_EXPERIMENT(per_matrix)
{
  public:
  per_matrix( std::size_t s0, std::size_t s1 )
            : NT2_EXPRIMENT_CTOR(5,"ms")
            , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    y = nt2::exp(nt2::sqr(a - b) * 0.5);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.second/1e3;
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a = nt2::rand(d0,d1);
    b = nt2::rand(d0, d1);
    y = nt2::zeros(d0, d1);
  }

  private:
          std::size_t                   d0,d1;
  mutable nt2::container::table<double> y,a,b;
};

NT2_EXPERIMENT(per_column)
{
  public:
  per_column( std::size_t s0, std::size_t s1 )
            : NT2_EXPRIMENT_CTOR(5,"ms")
            , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    for(std::size_t j = 1; j <= d1; ++j)
    {
      y(nt2::_, j) = nt2::exp(nt2::sqr(a(nt2::_, j) - b(nt2::_, j)) * 0.5);
    }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.second/1e3;
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a = nt2::rand(d0,d1);
    b = nt2::rand(d0, d1);
    y = nt2::zeros(d0, d1);
  }

  private:
          std::size_t                   d0,d1;
  mutable nt2::container::table<double> y,a,b;
};

NT2_EXPERIMENT(per_element)
{
  public:
  per_element ( std::size_t s0, std::size_t s1 )
              : NT2_EXPRIMENT_CTOR(5,"ms")
              , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    for(std::size_t j = 1; j <= d1; ++j)
    {
      for(std::size_t i = 1; i <= d0; ++i)
      {
        double v = a(i, j) - b(i, j);
        y(i, j) = std::exp( (v * v) * 0.5 );
      }
    }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.second/1e3;
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a = nt2::rand(d0,d1);
    b = nt2::rand(d0, d1);
    y = nt2::zeros(d0, d1);
  }

  private:
          std::size_t                   d0,d1;
  mutable nt2::container::table<double> y,a,b;
};

void raw_function(double* y, double* a, double* b, std::size_t n)
{
  for(std::size_t i = 0; i < n; ++i)
  {
    double v = a[i] - b[i];
    y[i] = std::exp( (v * v) * 0.5 );
  }
}

NT2_EXPERIMENT(raw_C)
{
  public:
  raw_C( std::size_t s0, std::size_t s1 )
       : NT2_EXPRIMENT_CTOR(5,"ms")
       , d(s0*s1)
  {}

  virtual void run() const
  {
    raw_function(&y[0],&a[0],&b[0],d);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.second/1e3;
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a.resize(d);
    b.resize(d);
    y.resize(d);

    nt2::roll ( a, 0, 1 );
    nt2::roll ( b, 0, 1 );
  }

  private:
          std::size_t         d;
  mutable std::vector<double> y,a,b;
};

NT2_RUN_EXPERIMENT( raw_C       )(2000,2000);
NT2_RUN_EXPERIMENT( per_matrix  )(2000,2000);
NT2_RUN_EXPERIMENT( per_column  )(2000,2000);
NT2_RUN_EXPERIMENT( per_element )(2000,2000);

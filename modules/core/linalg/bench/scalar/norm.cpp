/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/table.hpp>
#include <nt2/include/functions/norm.hpp>

#include <nt2/sdk/bench/benchmark.hpp>

template< typename T
        , typename Tag = boost::dispatch::default_site<void>::type
        >
NT2_EXPERIMENT(test_norm)
{
  public:
  test_norm ( std::size_t s0, std::size_t s1)
            : NT2_EXPRIMENT_CTOR(1., "cycles/elements" )
            , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    nn = nt2::norm(a1, 'I');
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(d0*d1);
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a1.resize(nt2::of_size(d0,d1));
    nt2::roll ( a1, -10, 10 );
  }

  private:
          std::size_t   d0,d1;
  mutable nt2::table<T> a1;
  mutable T             nn;
};

template< typename T
        , typename Tag = boost::dispatch::default_site<void>::type
        >
NT2_EXPERIMENT(test_norm_expr)
{
  public:
  test_norm_expr( std::size_t s0, std::size_t s1)
                : NT2_EXPRIMENT_CTOR(1., "cycles/elements" )
                , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    nn = nt2::norm(a1+a1, 'I');
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(d0*d1);
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a1.resize(nt2::of_size(d0,d1));
    nt2::roll ( a1, -10, 10 );
  }

  private:
          std::size_t   d0,d1;
  mutable nt2::table<T> a1;
  mutable T             nn;
};

#define NT2_TABLE_EXP(T,N)                                     \
NT2_RUN_EXPERIMENT_TPL( test_norm     , (T)  , (1<<N , 1<<N)); \
NT2_RUN_EXPERIMENT_TPL( test_norm_expr, (T)  , (1<<N , 1<<N)); \
/**/

NT2_TABLE_EXP(double ,  1 );
NT2_TABLE_EXP(double ,  2 );
NT2_TABLE_EXP(double ,  3 );
NT2_TABLE_EXP(double ,  4 );
NT2_TABLE_EXP(double ,  5 );
NT2_TABLE_EXP(double ,  6 );
NT2_TABLE_EXP(double ,  7 );
NT2_TABLE_EXP(double ,  8 );
NT2_TABLE_EXP(double ,  9 );
NT2_TABLE_EXP(double , 10 );
NT2_TABLE_EXP(double , 11 );
NT2_TABLE_EXP(double , 12 );

NT2_TABLE_EXP(float ,  1 );
NT2_TABLE_EXP(float ,  2 );
NT2_TABLE_EXP(float ,  3 );
NT2_TABLE_EXP(float ,  4 );
NT2_TABLE_EXP(float ,  5 );
NT2_TABLE_EXP(float ,  6 );
NT2_TABLE_EXP(float ,  7 );
NT2_TABLE_EXP(float ,  8 );
NT2_TABLE_EXP(float ,  9 );
NT2_TABLE_EXP(float , 10 );
NT2_TABLE_EXP(float , 11 );
NT2_TABLE_EXP(float , 12 );

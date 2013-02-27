/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/fast_cos.hpp>
#include <nt2/include/functions/fast_sin.hpp>
#include <nt2/include/functions/sqrt.hpp>

#include <nt2/sdk/bench/benchmark.hpp>

template< typename T
        , typename Tag = boost::dispatch::default_site<void>::type
        >
NT2_EXPERIMENT(small_table)
{
  public:
  small_table ( std::size_t s0, std::size_t s1 )
              : NT2_EXPRIMENT_CTOR(1.,"cycles/elements")
              , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    a2 = nt2::sqrt(nt2::fast_cos(a0)/nt2::fast_sin(a0) + a1*a1/a0);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(d0*d1);
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a0.resize(nt2::of_size(d0,d1));
    a1.resize(nt2::of_size(d0,d1));
    a2.resize(nt2::of_size(d0,d1));

    roll ( a0, -.28319, .28319 );
    roll ( a1, -.28319, .28319 );
  }

  private:
          std::size_t               d0,d1;
          bool                      is_ref;
  mutable nt2::container::table<T>  a0,a1,a2;
};

#define NT2_TABLE_EXP(T,N)                                              \
NT2_RUN_EXPERIMENT_TPL( small_table, (T), (1        , 1<<N         ));  \
NT2_RUN_EXPERIMENT_TPL( small_table, (T), (1<<N     , 1            ))   \
/**/

NT2_TABLE_EXP(double ,  4 );
NT2_TABLE_EXP(double ,  6 );
NT2_TABLE_EXP(double ,  8 );
NT2_TABLE_EXP(double , 10 );
NT2_TABLE_EXP(double , 12 );
NT2_TABLE_EXP(double , 14 );

NT2_TABLE_EXP(float ,  4 );
NT2_TABLE_EXP(float ,  6 );
NT2_TABLE_EXP(float ,  8 );
NT2_TABLE_EXP(float , 10 );
NT2_TABLE_EXP(float , 12 );
NT2_TABLE_EXP(float , 14 );

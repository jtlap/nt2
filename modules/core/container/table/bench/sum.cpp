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
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/plus.hpp>

#include <nt2/sdk/bench/benchmark.hpp>

template< typename T, int N
        , class Tag = boost::dispatch::default_site<void>::type
        >
NT2_EXPERIMENT(sum_over)
{
  public:
  sum_over( std::size_t s0, std::size_t s1 )
          : NT2_EXPRIMENT_CTOR(1.,"cycles/operations")
          , d0(s0), d1(s1)
  {}

  virtual void run() const { a1 = nt2::sum(a0,N); }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(d0*d1);
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a0.resize(nt2::of_size(d0,d1));
    a1.resize(nt2::of_size( N==1 ? 1 : d0
                          , N==2 ? 1 : d1
                          )
                );

    for(std::size_t i=1; i<=d0*d1; ++i) a0(i) = T(1);
  }

  private:
          std::size_t                               d0,d1;
  mutable nt2::container::table<T, nt2::settings()> a0,a1;
};


#define NT2_SUM_EXP(T,D,N)                                        \
NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), (1<<N,1<<N) )          \
NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), ((1<<N)-1,(1<<N)-1 ) ) \
NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), (1   ,1<<N) )          \
NT2_RUN_EXPERIMENT_TPL( sum_over, ((T,D)), (1<<N,1   ) )          \
/**/

NT2_SUM_EXP(double , 1,  4 );
NT2_SUM_EXP(double , 1,  5 );
NT2_SUM_EXP(double , 1,  6 );
NT2_SUM_EXP(double , 1,  7 );
NT2_SUM_EXP(double , 1,  8 );
NT2_SUM_EXP(double , 1,  9 );
NT2_SUM_EXP(double , 1, 10 );
NT2_SUM_EXP(double , 1, 11 );
NT2_SUM_EXP(double , 1, 12 );

NT2_SUM_EXP(float , 1,  4 );
NT2_SUM_EXP(float , 1,  5 );
NT2_SUM_EXP(float , 1,  6 );
NT2_SUM_EXP(float , 1,  7 );
NT2_SUM_EXP(float , 1,  8 );
NT2_SUM_EXP(float , 1,  9 );
NT2_SUM_EXP(float , 1, 10 );
NT2_SUM_EXP(float , 1, 11 );
NT2_SUM_EXP(float , 1, 12 );

NT2_SUM_EXP(double , 2,  4 );
NT2_SUM_EXP(double , 2,  5 );
NT2_SUM_EXP(double , 2,  6 );
NT2_SUM_EXP(double , 2,  7 );
NT2_SUM_EXP(double , 2,  8 );
NT2_SUM_EXP(double , 2,  9 );
NT2_SUM_EXP(double , 2, 10 );
NT2_SUM_EXP(double , 2, 11 );
NT2_SUM_EXP(double , 2, 12 );

NT2_SUM_EXP(float , 2,  4 );
NT2_SUM_EXP(float , 2,  5 );
NT2_SUM_EXP(float , 2,  6 );
NT2_SUM_EXP(float , 2,  7 );
NT2_SUM_EXP(float , 2,  8 );
NT2_SUM_EXP(float , 2,  9 );
NT2_SUM_EXP(float , 2, 10 );
NT2_SUM_EXP(float , 2, 11 );
NT2_SUM_EXP(float , 2, 12 );

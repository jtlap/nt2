//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sqrt.hpp>

#include <nt2/sdk/bench/benchmark.hpp>

template< typename Container
        , typename Tag = boost::dispatch::default_site<void>::type
        >
NT2_EXPERIMENT(redundant_loads)
{
  public:
  redundant_loads ( std::size_t s0, std::size_t s1, bool status = false )
            : NT2_EXPRIMENT_CTOR(1.,status ? "cycles/elements" : "speed-up")
            , d0(s0), d1(s1)
            , is_ref(status)
  {}

  virtual void run() const
  {
    a2 = a0+a0+a0;
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    if(is_ref)
    {
      nt2::reference_timing().second = double(r.first);
      return r.first/double(d0*d1);
    }
    else
    {
      return nt2::reference_timing().first / nt2::reference_timing().second;
    }
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a0.resize(nt2::of_size((is_ref ? d0:1), (is_ref ? d1:1)));
    a2.resize(nt2::of_size((is_ref ? d0:1), (is_ref ? d1:1)));

    nt2::roll ( a0, -.28319, .28319 );
  }

  private:
          std::size_t               d0,d1;
          bool                      is_ref;
  mutable Container                 a0,a2;
};

template<typename T> NT2_EXPERIMENT(redundant_loads< std::vector<T> >)
{
  public:
  redundant_loads ( std::size_t s0, std::size_t s1)
            : NT2_EXPRIMENT_CTOR(1.,"cycles/elements")
            , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    for(std::size_t i=0; i<d0*d1; ++i) a2[i] = a0[i]+a0[i]+a0[i];
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    nt2::reference_timing() = r;
    return r.first/double(d0*d1);
  }

  virtual void info(std::ostream& os) const { os << d0 << "x" << d1; }

  virtual void reset() const
  {
    a0.resize(d0*d1);
    a2.resize(d0*d1);

    nt2::roll ( a0, -.28319, .28319 );
  }

  private:
          std::size_t               d0,d1;
          bool                      is_ref;
  mutable std::vector<T>            a0,a2;
};

#define NT2_TABLE_EXP(T,N)                                                        \
NT2_RUN_EXPERIMENT_TPL( redundant_loads, (std::vector<T>) , (1<<N , 1<<N));       \
NT2_RUN_EXPERIMENT_TPL( redundant_loads, (nt2::table<T>)  , (1<<N , 1<<N,true));  \
NT2_RUN_EXPERIMENT_TPL( redundant_loads, (nt2::table<T>)  , (1<<N , 1<<N));       \
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

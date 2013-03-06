//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/sdk/bench/benchmark.hpp>

struct _1D {};
struct _2D {};

template< typename Container
        , typename Dims
        , typename Tag = boost::dispatch::default_site<void>::type
        >
class test_subscript;

template<typename T>
NT2_EXPERIMENT((test_subscript<nt2::table<T>, _1D>))
{
  public:
  test_subscript( std::size_t s0, bool status = false )
                : NT2_EXPRIMENT_CTOR(1.,status ? "cycles/elements" : "speed-up")
                , d0(s0)
                , is_ref(status)
  {}

  virtual void run() const
  {
    for (std::size_t i=1; i <= d0; i++)
      a0(i) = a1(i);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    if(is_ref)
    {
      nt2::reference_timing().second = double(r.first);
      return r.first/double(d0);
    }
    else
    {
      return nt2::reference_timing().first / nt2::reference_timing().second;
    }
  }

  virtual void info(std::ostream& os) const { os << d0; }

  virtual void reset() const
  {
    a0.resize(nt2::of_size(d0));
    a1.resize(nt2::of_size(d0));

    nt2::roll ( a1, -100, 100 );
  }

  private:
          std::size_t               d0;
          bool                      is_ref;
  mutable nt2::table<T>             a0,a1;
};

template<typename T>
NT2_EXPERIMENT((test_subscript<nt2::table<T>, _2D>))
{
  public:
  test_subscript( std::size_t s0, std::size_t s1, bool status = false )
                : NT2_EXPRIMENT_CTOR(1.,status ? "cycles/elements" : "speed-up")
                , d0(s0), d1(s1)
                , is_ref(status)
  {}

  virtual void run() const
  {
    for (std::size_t j=1; j <= d1; j++)
      for (std::size_t i=1; i <= d0; i++)
        a0(i,j) = a1(i,j);
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
    a0.resize(nt2::of_size(d0,d1));
    a1.resize(nt2::of_size(d0,d1));

    nt2::roll ( a1, -100, 100 );
  }

  private:
          std::size_t               d0,d1;
          bool                      is_ref;
  mutable nt2::table<T>             a0,a1;
};

template<typename T>
NT2_EXPERIMENT((test_subscript<std::vector<T>, _1D>))
{
  public:
  test_subscript( std::size_t s0)
                : NT2_EXPRIMENT_CTOR(1.,"cycles/elements")
                , d0(s0)
  {}

  virtual void run() const
  {
    for(std::size_t i=0; i<d0; ++i) a0[i] = a1[i];
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    nt2::reference_timing() = r;
    return r.first/double(d0);
  }

  virtual void info(std::ostream& os) const { os << d0; }

  virtual void reset() const
  {
    a0.resize(d0);
    a1.resize(d0);

    nt2::roll ( a1, -.28319, .28319 );
  }

  private:
          std::size_t               d0;
          bool                      is_ref;
  mutable std::vector<T>            a0,a1;
};

template<typename T>
NT2_EXPERIMENT((test_subscript<std::vector<T>, _2D>))
{
  public:
  test_subscript( std::size_t s0, std::size_t s1)
                : NT2_EXPRIMENT_CTOR(1.,"cycles/elements")
                , d0(s0), d1(s1)
  {}

  virtual void run() const
  {
    for(std::size_t j=0; j<d1; ++j)
      for(std::size_t i=0; i<d0; ++i)
        a0[i+j*d0] = a1[i+j*d0];
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
    a1.resize(d0*d1);

    nt2::roll ( a1, -.28319, .28319 );
  }

  private:
          std::size_t               d0,d1;
          bool                      is_ref;
  mutable std::vector<T>            a0,a1;
};

#define NT2_TABLE_EXP(T,N)                                                      \
NT2_RUN_EXPERIMENT_TPL( test_subscript, ((std::vector<T>,_1D)) , (1<<N ));      \
NT2_RUN_EXPERIMENT_TPL( test_subscript, ((nt2::table<T>,_1D))  , (1<<N ,true)); \
NT2_RUN_EXPERIMENT_TPL( test_subscript, ((nt2::table<T>,_1D))  , (1<<N ));      \
NT2_RUN_EXPERIMENT_TPL( test_subscript, ((std::vector<T>,_2D)) , (1<<N,1<<N ));      \
NT2_RUN_EXPERIMENT_TPL( test_subscript, ((nt2::table<T>,_2D))  , (1<<N,1<<N,true)); \
NT2_RUN_EXPERIMENT_TPL( test_subscript, ((nt2::table<T>,_2D))  , (1<<N,1<<N ));      \
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

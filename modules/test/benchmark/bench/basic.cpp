//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <cmath>
#include <vector>
#include <nt2/sdk/bench/benchmark.hpp>

template<typename T> NT2_EXPERIMENT(cosinus)
{
  public:
  cosinus ( std::size_t n, double d )
            : NT2_EXPRIMENT_CTOR(n,d,"cycles/elements")
            , size(n)
  {}

  virtual void run() const
  {
    for(int i=0;i<size;++i) y[i] = std::cos(x[i]);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/size;
  }

  virtual void reset() const
  {
    x.resize(size);
    y.resize(size);
    nt2::roll(x,-3.14159/2.,3.14159/2);
    nt2::roll(y,-3.14159/2.,3.14159/2);
  }

  private:
  int       size;
  mutable   std::vector<T> x,y;
};

NT2_EXPERIMENT(empty)
{
  public:
  empty (std::size_t n, double d = 1)
            : NT2_EXPRIMENT_CTOR(n,d,"cycles/elements"), size(n)
  {}

  virtual void run() const {}
  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first / size;
  }

  private:
  std::size_t size;
};

/*
  empty is an empty test, it shoudl return 0 cycles/elements
*/
NT2_RUN_EXPERIMENT(empty)(1);
NT2_RUN_EXPERIMENT(empty)(1000);

/*
 Simple scalar AXPY benchmark to see if we catch cache misses
*/
NT2_RUN_EXPERIMENT_TPL( cosinus
                      , (float)(double)
                      , (256,3)
                      );

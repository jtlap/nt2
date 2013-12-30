//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <vector>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/globalsum.hpp>

#ifdef __ANDROID__
  #define TURBOFREQ 1.008000
#else
  #define TURBOFREQ 3.401
#endif
#define NOPS 2.0

template<typename T>
NT2_EXPERIMENT(Tdot_nt2)
{
  public:

    Tdot_nt2(std::size_t const& s)
    : NT2_EXPERIMENT_CTOR(1., "GFLOPS"),
    size(s)
    {
      X.resize(nt2::of_size(s)); Y.resize(nt2::of_size(s));
      for(std::size_t i = 1; i<=size; ++i) X(i) = Y(i) = T(i-1);
    }

    virtual void run() const
    {
      result = nt2::globalsum(X*Y);
    }
    virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return(double(size)*NOPS*TURBOFREQ/r.first);
    }

    virtual void info(std::ostream& os) const { os << size; }

    virtual void reset() const
    {
    }
  private:
    mutable T result;
    std::size_t size;
    mutable std::size_t step_size;
    mutable nt2::table<T> X, Y;
};

NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (float), (16384));

NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (16));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (32));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (64));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (128));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (256));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (512));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (1024));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (2048));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (4096));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (8192));
NT2_RUN_EXPERIMENT_TPL( Tdot_nt2, (double), (16384));

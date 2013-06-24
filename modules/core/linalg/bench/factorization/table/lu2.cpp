//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>

#include <nt2/table.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/tie.hpp>
#include "../../flops/lu.hpp"

template<typename T> struct lu_2;

template<typename T> NT2_EXPERIMENT(lu_2< nt2::table<T> >)
{
  public:
  lu_2( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    nt2::tie(L,U) = nt2::lu(input);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return (FLOPS_GETRF(h,w)/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    L = nt2::zeros(h,w, nt2::meta::as_<T>());
    U = nt2::zeros(h,w, nt2::meta::as_<T>());
    input  = nt2::rand(h,w, nt2::meta::as_<T>());
  }

  private:
  std::size_t   h,w;
  mutable nt2::table<T> input, L,U;
};

NT2_RUN_EXPERIMENT_TPL( lu_2, (nt2::table<float>)(nt2::table<double>), (4,4) );
NT2_RUN_EXPERIMENT_TPL( lu_2, (nt2::table<float>)(nt2::table<double>), (63,65) );
NT2_RUN_EXPERIMENT_TPL( lu_2, (nt2::table<float>)(nt2::table<double>), (1023,1025) );
NT2_RUN_EXPERIMENT_TPL( lu_2, (nt2::table<float>)(nt2::table<double>), (2048,2048) );

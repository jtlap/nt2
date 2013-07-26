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
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"

template<typename T> struct linsolve;

template<typename T> NT2_EXPERIMENT(linsolve< nt2::table<T> >)
{
  public:
  linsolve( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    result = nt2::linsolve(a,b);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,w))/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
  }

  private:
  std::size_t   h,w;
  mutable nt2::table<T> a,b, result;
};

NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (1023,1023) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (2048,2048) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (4000,4000) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (6000,6000) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (8000,8000) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (10000,10000) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>)(nt2::table<double>), (12000,12000) );

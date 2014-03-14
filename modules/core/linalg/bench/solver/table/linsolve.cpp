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
#include <nt2/linalg/details/utility/llspgen.hpp>

#include <nt2/table.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/ls.hpp>
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"
#include "../../flops/qr.hpp"

#include <nt2/include/functions/mcsne.hpp>
#include <iostream>

template<typename T> struct linsolve;

template<typename T> NT2_EXPERIMENT(linsolve< nt2::table<T> >)
{
  public:
  linsolve( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.0,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    // result = b;
    //  ac = a;
    nt2::ls(boost::proto::value(a),boost::proto::value(b) );
    // result = mcsne(a,b);
    // result = nt2::mtimes(a,b);
    // result = nt2::linsolve(a,b);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
     // return ((FLOPS_GETRF(h,w)+ FLOPS_DGETRS(h,1))/r.second)/1000.;
     // return ((FLOPS_DGEMM(h,w,w))/r.second)/1000.;
    return ((FLOPS_GEQRF(h,w)+ FLOPS_DGETRS(h,1))/r.second)/1000.;
    // return (FLOPS_GEQRF(h,w)+ FLOPS_DGETRS(h,1));
    // return r.second/1000000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    nr = 1;
    nt2::tie(a,x,r,b)= nt2::llspgen(h,w,nr,nr,nt2::meta::as_<T>());
    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    // a  = nt2::rand(h,w, nt2::meta::as_<T>());
    // b  = nt2::rand(w,w, nt2::meta::as_<T>());
    // a = a + nt2::transpose(a);
    // b  = nt2::rand(h,1, nt2::meta::as_<T>());
  }

  private:
  std::size_t   h,w;
  mutable std::size_t nr;
  mutable nt2::table<T> b, result;
  mutable nt2::table<T> a,x,r,ac;
};

// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (2000,200) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (500,500) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (3000,3000) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (5000,5000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (300,3000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (500,5000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (800,8000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (8000,800) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (10000,1000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (13000,3000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (15000,5000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (18000,8000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (20000,10000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>)(nt2::table<float>), (4000,4000) );

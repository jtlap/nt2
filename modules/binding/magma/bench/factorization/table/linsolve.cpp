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
#include <nt2/sdk/magma/magma.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/transpose.hpp>
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"
#include "../../flops/qr.hpp"
#include <nt2/include/functions/mcsne.hpp>
#include <nt2/include/functions/ls.hpp>

template<typename T> struct linsolve;

template<typename T> NT2_EXPERIMENT(linsolve< nt2::table<T> >)
{
  public:
  linsolve( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(5.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
     // result = b;
     // fact = a;
     // result = nt2::mcsne(a, b ) ;
    // nt2::ls(boost::proto::value(fact),boost::proto::value(result) );
    // result = nt2::linsolve(a,b);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
   return ((FLOPS_GEQRF(h,w)+ FLOPS_DGETRS(w,1))/r.second)/1000.;
    // return ((FLOPS_GEQRF(h,w)+ FLOPS_DGETRS(w,1))/r.second)/1000.;
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
    // a = a + nt2::transpose(a);
    // b  = nt2::rand(h,1, nt2::meta::as_<T>());
  }

  private:
  std::size_t   h,w;
  mutable std::size_t nr;
  mutable nt2::table<T> b, result;
  mutable nt2::table<nt2_la_int> piv;
  mutable nt2::table<T> a,x,r,fact;
};


// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (1500,750) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (4000,4000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (5000,2500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (8000,4000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (10200,5000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (13000,6500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (15000,7500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (18000,9000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (20000,10000) );



// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (1500,750) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (3020,1500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (5000,2500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (8000,4000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (10200,5000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (13000,6500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (15000,7500) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (18000,9000) );
// NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<float>), (20000,10000) );


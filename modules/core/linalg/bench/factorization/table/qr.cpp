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
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include "../../flops/qr.hpp"

template<typename T> struct qr_1;

template<typename T> NT2_EXPERIMENT(qr_1< nt2::table<T> >)
{
  public:
  qr_1( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    result = nt2::qr(input);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return (FLOPS_GEQRF(h,w)/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    input  = nt2::rand(h,w, nt2::meta::as_<T>());
  }

  private:
  std::size_t   h,w;
  mutable nt2::table<T> input, result;
};

NT2_RUN_EXPERIMENT_TPL( qr_1, (nt2::table<float>)(nt2::table<double>), (4,4) );
NT2_RUN_EXPERIMENT_TPL( qr_1, (nt2::table<float>)(nt2::table<double>), (63,65) );
NT2_RUN_EXPERIMENT_TPL( qr_1, (nt2::table<float>)(nt2::table<double>), (1023,1025) );
NT2_RUN_EXPERIMENT_TPL( qr_1, (nt2::table<float>)(nt2::table<double>), (2049,2049) );
NT2_RUN_EXPERIMENT_TPL( qr_1, (nt2::table<float>)(nt2::table<double>), (12000,12000) );


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
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include "details.hpp"


template<typename T>
NT2_EXPERIMENT(lu_1_float)
{

  public:
  lu_1_float( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    jpvt.resize(nt2::of_size(std::min(h, w), 1) );
    NT2_F77NAME(sgetrf)( &h1, &w1, input.raw(), &h1, jpvt.raw(), &i);
    result = input;
  }


  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return (FLOPS_DGETRF(h,w)/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {

    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    input  = nt2::rand(h,w, nt2::meta::as_<T>());
    h1 = static_cast<nt2_la_int>(h) ;
    w1 = static_cast<nt2_la_int>(w);

  }

  private:
  std::size_t   h,w;
  mutable nt2_la_int i,h1,w1;
  mutable nt2::table<T> input, result;
  mutable nt2::table<nt2_la_int> jpvt;
};

template<typename T>
NT2_EXPERIMENT(lu_1_double)
{

  public:
  lu_1_double( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    jpvt.resize(nt2::of_size(std::min(h, w), 1) );
    NT2_F77NAME(dgetrf)( &h1, &w1, input.raw(), &h1, jpvt.raw(), &i);
    result = input;
  }


  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return (FLOPS_DGETRF(h,w)/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {

    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    input  = nt2::rand(h,w, nt2::meta::as_<T>());
    h1 = static_cast<nt2_la_int>(h) ;
    w1 = static_cast<nt2_la_int>(w);

  }

  private:
  std::size_t   h,w;
  mutable nt2_la_int i,h1,w1;
  mutable nt2::table<T> input, result;
  mutable nt2::table<nt2_la_int> jpvt;
};

NT2_RUN_EXPERIMENT_TPL( lu_1_float, (float), (4,4) );
NT2_RUN_EXPERIMENT_TPL( lu_1_double, (double), (4,4) );
NT2_RUN_EXPERIMENT_TPL( lu_1_float, (float), (63,65) );
NT2_RUN_EXPERIMENT_TPL( lu_1_double, (double), (63,65) );
NT2_RUN_EXPERIMENT_TPL( lu_1_float, (float), (1023,1025) );
NT2_RUN_EXPERIMENT_TPL( lu_1_double, (double), (1023,1025) );
NT2_RUN_EXPERIMENT_TPL( lu_1_float, (float), (2048,2048) );
NT2_RUN_EXPERIMENT_TPL( lu_1_double, (double), (2048,2048) );

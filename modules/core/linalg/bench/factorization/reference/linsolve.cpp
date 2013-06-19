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
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include "details.hpp"


template<typename T>
NT2_EXPERIMENT(sgesv_test)
{

  public:
  sgesv_test( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    nhrs = nt2::width(b);
    jpvt.resize(nt2::of_size(h1, 1) );

    a1 = a;
    b1 = b;

    NT2_F77NAME(sgesv)( &h1, &nhrs, a.raw(), &h1, jpvt.raw(), b.raw(),&h1,&i);
  }


  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return ((FLOPS_DGETRF(h,w)+ FLOPS_DGETRS(h,w))/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
    h1 = static_cast<nt2_la_int>(h);
    w1 = static_cast<nt2_la_int>(w);

  }

  private:
  std::size_t   h,w;
  mutable nt2_la_int i,h1,w1,nhrs;
  mutable nt2::table<T> a,a1,b,b1;
  mutable nt2::table<nt2_la_int> jpvt;
};

template<typename T>
NT2_EXPERIMENT(dgesv_test)
{

  public:
  dgesv_test( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    nhrs = nt2::width(b);
    jpvt.resize(nt2::of_size(h, 1) );
    a1 = a;
    b1 = b;

    NT2_F77NAME(dgesv)( &h1, &nhrs, a.raw(), &h1, jpvt.raw(), b.raw(),&h1,&i);
  }


  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return ((FLOPS_DGETRF(h,w)+ FLOPS_DGETRS(h,w))/r.second)/1000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());
    h1 = static_cast<nt2_la_int>(h);
    w1 = static_cast<nt2_la_int>(w);

  }

  private:
  std::size_t   h,w;
  mutable nt2_la_int i,h1,w1,nhrs;
  mutable nt2::table<T> a,a1,b,b1;
  mutable nt2::table<nt2_la_int> jpvt;
};

NT2_RUN_EXPERIMENT_TPL( sgesv_test, (float), (4,4) );
NT2_RUN_EXPERIMENT_TPL( dgesv_test, (double), (4,4) );
NT2_RUN_EXPERIMENT_TPL( sgesv_test, (float), (65,65) );
NT2_RUN_EXPERIMENT_TPL( dgesv_test, (double), (65,65) );
NT2_RUN_EXPERIMENT_TPL( sgesv_test, (float), (1023,1023) );
NT2_RUN_EXPERIMENT_TPL( dgesv_test, (double), (1023,1023) );
NT2_RUN_EXPERIMENT_TPL( sgesv_test, (float), (2048,2048) );
NT2_RUN_EXPERIMENT_TPL( dgesv_test, (double), (2048,2048) );

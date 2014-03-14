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
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"

#include "details.hpp"

template<typename T>
NT2_EXPERIMENT(sgesv_test)
{
  public:
  sgesv_test( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(30.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    nhrs = nt2::width(b);
    jpvt.resize(nt2::of_size(h1, 1) );

    a1 = a;
    b1 = b;

    NT2_F77NAME(sgesv)( &h1, &nhrs, a1.raw(), &h1, jpvt.raw(), b1.raw(),&h1,&i);
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
      : NT2_EXPRIMENT_CTOR(35.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    nhrs = nt2::width(b);
    jpvt.resize(nt2::of_size(h1, 1) );

    a1 = a;
    b1 = b;

    NT2_F77NAME(dgesv)( &h1, &nhrs, a.raw(), &h1, jpvt.raw(), b.raw(),&h1,&i);
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
NT2_EXPERIMENT(dgesvx_test)
{
  public:
  dgesvx_test( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(30.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
  n  = nt2::height(a);
  nhrs = nt2::width(b);
  jpvt.resize(nt2::of_size(h1, 1) );
  x = b;
  char fact  = 'N';
  char trans = 'N';
  char equed = 'N';

  af.resize(nt2::of_size(n,n));
  r.resize(nt2::of_size(n,1));
  c.resize(nt2::of_size(n,1));
  ferr.resize(nt2::of_size(nhrs,1));
  berr.resize(nt2::of_size(nhrs,1));
  work.resize(nt2::of_size(4*n,1));
  iwork.resize(nt2::of_size(n,1));

        NT2_F77NAME(dgesvx)( &fact       , &trans
                           , &h1         , &nhrs
                           , a.raw()     , &h1
                           , af.raw()    , &h1
                           , jpvt.raw()  , &equed
                           , r.raw()     , c.raw()
                           , b.raw()     , &h1
                           , x.raw()     , &h1
                           , &rcond      , ferr.raw()
                           , berr.raw()  , work.raw()
                           , iwork.raw() , &i
                           );
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
    a  = nt2::rand(h,w, nt2::meta::as_<T>());
    b  = nt2::rand(h,1, nt2::meta::as_<T>());

    h1 = static_cast<nt2_la_int>(h);
    w1 = static_cast<nt2_la_int>(w);

  }

  private:
  std::size_t   h,w;
  mutable nt2_la_int i,h1,w1,nhrs,n;
  mutable double rcond;
  mutable nt2::table<T> a,a1,b,b1,x,af,r,c,ferr,berr,work;
  mutable nt2::table<nt2_la_int> jpvt,iwork;
};
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (200,200) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (500,500) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (800,800) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (1000,1000) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (2000,2000) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (4000,4000) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (6000,6000) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (8000,8000) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (10000,10000) );
// NT2_RUN_EXPERIMENT_TPL( dgesvx_test, (double), (12000,12000) );

NT2_RUN_EXPERIMENT_TPL( dgesv_test, (double), (1000,1000) );

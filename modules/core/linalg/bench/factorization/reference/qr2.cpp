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
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/xerbla.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include "details.hpp"

namespace nt2 { namespace ext
{



template<typename T>
NT2_EXPERIMENT(qr_2_float)
{

  public:
  qr_2_float( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {

    tau.resize(nt2::of_size(std::min(w1,h1), 1));

    NT2_F77NAME(sgeqrf)(&h1,&w1,0,&h1,0,work.main(),details::query(),&i);

    work.prepare_main();
    lwork = work.main_size();

    NT2_F77NAME(sgeqrf)(&h1,&w1,input.raw(),&h1,tau.raw(),work.main()
                       ,&lwork, &i
                       );

    R = nt2::triu(input);
    k = std::min(h1,w1);

    if(h1>w1)
    {
      char side  = 'L';
      char trans = 'N';

      NT2_F77NAME(sormqr)( &side, &trans, &h1, &w1, &k, input.raw(), &h1, tau.raw()
                            , Q.raw(), &h1, work.main(), &lwork, &i);
      call = true;
    }
    else
    {
      if (h1<w1)
      {
        nt2::table<float> local(input);
        input = nt2::expand(input,nt2::of_size(h1,h1));
      }
      NT2_F77NAME(sorgqr)(&h1, &w1 , &k, input.raw(), &h1, tau.raw(), work.main()
                         , &lwork, &i);
      call = false;
    }

  }


  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    if (call == true)
      return ( (FLOPS_DGEQRF(h,w) + FLOPS_DORMQR(h,w,k) )/r.second)/1000. ;
    else
      return ( (FLOPS_DGEQRF(h,w) + FLOPS_DORGQR(h,w,k) )/r.second)/1000.;

  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {

    Q = nt2::zeros(h,w, nt2::meta::as_<T>());
    R = nt2::zeros(h,w, nt2::meta::as_<T>());
    input  = nt2::rand(h,w, nt2::meta::as_<T>());
    h1 = static_cast<nt2_la_int>(h) ;
    w1 = static_cast<nt2_la_int>(w);

  }

  private:
  std::size_t   h,w;
  mutable details::workspace<float> work;
  mutable bool call;
  mutable nt2_la_int i,h1,w1,lwork,k;
  mutable nt2::table<T> input, Q, R, tau;
};


template<typename T>
NT2_EXPERIMENT(qr_2_double)
{

  public:
  qr_2_double( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"GFLOPS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {

    tau.resize(nt2::of_size(std::min(h1,w1), 1));

    NT2_F77NAME(dgeqrf)(&h1,&w1,0,&h1,0,work.main(),details::query(),&i);

    work.prepare_main();
    lwork = work.main_size();

    NT2_F77NAME(dgeqrf)(&h1,&w1,input.raw(),&h1,tau.raw(),work.main()
                       ,&lwork, &i
                       );

    R = nt2::triu(input);
    k = std::min(h1,w1);

    if(h1>w1)
    {
      char side  = 'L';
      char trans = 'N';
      NT2_F77NAME(dormqr)( &side, &trans, &h1, &w1, &k, input.raw(), &h1, tau.raw()
                            , Q.raw(), &h1, work.main(), &lwork, &i);
      call = true;
    }
    else
    {
      if (h1<w1)
      {
        nt2::table<double> local(input);
        input = nt2::expand(local,nt2::of_size(h1,h1));
      }
      NT2_F77NAME(dorgqr)(&h1, &w1, &k, input.raw(), &h1, tau.raw(), work.main()
                         , &lwork, &i);
      Q = input;
      call = false;
    }

  }


  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    if (call == true)
      return ( (FLOPS_DGEQRF(h,w) + FLOPS_DORMQR(h,w,k) )/r.second)/1000. ;
    else
      return ( (FLOPS_DGEQRF(h,w) + FLOPS_DORGQR(h,w,k) )/r.second)/1000.;

  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    Q = nt2::zeros(h,w, nt2::meta::as_<T>());
    R = nt2::zeros(h,w, nt2::meta::as_<T>());
    input  = nt2::rand(h,w, nt2::meta::as_<T>());
    h1 = static_cast<nt2_la_int>(h) ;
    w1 = static_cast<nt2_la_int>(w);
    lwork = -1;

  }

  private:
  std::size_t   h,w;
  mutable details::workspace<double> work;
  mutable bool call;
  mutable nt2_la_int i,h1,w1,lwork,k;
  mutable nt2::table<T> input, Q, R, tau;
};

NT2_RUN_EXPERIMENT_TPL( qr_2_float, (float), (4,4) );
NT2_RUN_EXPERIMENT_TPL( qr_2_double, (double), (4,4) );
NT2_RUN_EXPERIMENT_TPL( qr_2_float, (float), (65,65) );
NT2_RUN_EXPERIMENT_TPL( qr_2_double, (double), (65,65) );
NT2_RUN_EXPERIMENT_TPL( qr_2_float, (float), (1025,1025) );
NT2_RUN_EXPERIMENT_TPL( qr_2_double, (double), (1025,1025) );
NT2_RUN_EXPERIMENT_TPL( qr_2_float, (float), (2049,2049) );
NT2_RUN_EXPERIMENT_TPL( qr_2_double, (double), (2049,2049) );
}}



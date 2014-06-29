//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/lu.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/of_size.hpp>
#include "../../flops/qr.hpp"
#include "details.hpp"
#include <nt2/linalg/details/utility/f77_wrapper.hpp>
#include <nt2/linalg/details/utility/workspace.hpp>
#include <nt2/include/functions/triu.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/gflops.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;

template<typename T> struct qr3_float_nt2
{
  qr3_float_nt2(std::size_t n)
              :  size_(n)
              , Q(of_size(n,n))
              , R(of_size(n,n))
  {
    lwork = -1;
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    m = h1 = w1 = size();

    tau.resize(nt2::of_size(std::min(m,m), 1));

    NT2_F77NAME(sgeqp3)(&h1,&w1,0,&m,0,0,work.main(),nt2::details::query(),&info);

    work.prepare_main();
    jpvt = nt2::zeros(m,1,nt2::meta::as_<nt2_la_int>());
    lwork = work.main_size();

    NT2_F77NAME(sgeqp3)(&h1,&w1,input.data(),&m,jpvt.data(),tau.data(),work.main()
                       ,&lwork, &info
                       );

    R = nt2::triu(input);
    k = std::min(h1,w1);

    if(h1>w1)
    {
      char side  = 'L';
      char trans = 'N';

      NT2_F77NAME(sormqr)( &side, &trans, &h1, &w1, &k, input.data(), &h1, tau.data()
                            , Q.data(), &h1, work.main(), &lwork, &info);
      call = true;
    }
    else
    {
      if (h1<w1)
      {
        nt2::table<float> local(input);
        input = nt2::expand(input,nt2::of_size(h1,h1));
      }
      NT2_F77NAME(sorgqr)(&h1, &w1 , &k, input.data(), &h1, tau.data(), work.main()
                         , &lwork, &info);
      call = false;
    }

    d = nt2::numel(jpvt);
    P = nt2::zeros(d, nt2::meta::as_<T>());

    for(nt2_la_int i = 1; i <= d; ++i)
      (P)(jpvt(i),i) = 1;
  }


  friend std::ostream& operator<<(std::ostream& os, qr3_float_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return FLOPS_GEQRF(size_,size_) ; }

private:
  bool call;
  std::size_t size_;
  nt2::details::workspace<float> work;
  nt2_la_int info,m,lwork,h1,w1,k,d;
  nt2::table<T> input, Q,R,P, tau;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( qr3_float_nt2, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< qr3_float_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

template<typename T> struct qr3_double_nt2
{
  qr3_double_nt2(std::size_t n)
              :  size_(n)
              , Q(of_size(n,n))
              , R(of_size(n,n))
  {
    lwork = -1;
    input  = nt2::rand(n,n, nt2::meta::as_<T>());
  }

  void operator()()
  {
    m = h1 = w1 = size();

    tau.resize(nt2::of_size(std::min(m,m), 1));

    NT2_F77NAME(dgeqp3)(&h1,&w1,0,&m,0,0,work.main(),nt2::details::query(),&info);

    work.prepare_main();
    jpvt = nt2::zeros(m,1,nt2::meta::as_<nt2_la_int>());
    lwork = work.main_size();

    NT2_F77NAME(dgeqp3)(&h1,&w1,input.data(),&m,jpvt.data(),tau.data(),work.main()
                       ,&lwork, &info
                       );

    R = nt2::triu(input);
    k = std::min(h1,w1);

    if(h1>w1)
    {
      char side  = 'L';
      char trans = 'N';

      NT2_F77NAME(dormqr)( &side, &trans, &h1, &w1, &k, input.data(), &h1, tau.data()
                            , Q.data(), &h1, work.main(), &lwork, &info);
      call = true;
    }
    else
    {
      if (h1<w1)
      {
        nt2::table<double> local(input);
        input = nt2::expand(input,nt2::of_size(h1,h1));
      }
      NT2_F77NAME(dorgqr)(&h1, &w1 , &k, input.data(), &h1, tau.data(), work.main()
                         , &lwork, &info);
      call = false;
    }

    d = nt2::numel(jpvt);
    P = nt2::zeros(d, nt2::meta::as_<T>());

    for(nt2_la_int i = 1; i <= d; ++i)
      (P)(jpvt(i),i) = 1;

  }

  friend std::ostream& operator<<(std::ostream& os, qr3_double_nt2<T> const& p)
  {
    return os << "(" << p.size() << ")";
  }

  std::size_t size() const { return size_; }
  std::size_t flops() const { return (FLOPS_GEQRF(size_,size_)); }

private:
  bool call;
  std::size_t size_;
  nt2::details::workspace<double> work;
  nt2_la_int info,m,k,lwork,h1,w1,d;
  nt2::table<T> input, Q,R,P, tau;
  nt2::table<nt2_la_int> jpvt;
};

NT2_REGISTER_BENCHMARK_TPL( qr3_double_nt2, (double) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 10);

  run_during_with< qr3_double_nt2<T> > ( 1.
                                ,  geometric(size_min,size_max,size_step)
                                , gflops<stats::median_>()
                                );
}

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
#include "../../flops/solve.hpp"
#include "../../flops/lu.hpp"


#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/colon.hpp>

#include <limits>

#include "details.hpp"

template<typename T>
NT2_EXPERIMENT(dgesvx_test)
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

    NT2_F77NAME(dgesv)( &h1, &nhrs, a.raw(), &h1, jpvt.raw(), b.raw(),&h1,&i);


    //iterative refinement
    epsilon = nt2::eps(nt2::meta::as_<T>());
    char trans = 'N';
    // std::fill(work.raw()+n+1,work.raw()+2n+2,b(1,1));
    // NT2_F77NAME(dgemv)(&trans, &h1, &w1, &mone, a.raw(), &h1, x.raw(), &one, one, work.raw()+n+1,&one)
    nt2_la_int one = 1;
    nt2_la_int mone = -1;

    safe1 = std::numeric_limits<double>::min() * (static_cast<double>(h1+1) );
    safe2 = safe1/epsilon;
    do
    {
      /// Compute residual R = B - A * X
      res = b( nt2::_ ,1);
      NT2_F77NAME(dgemv)(&trans, &h1, &w1, &mone, a1.raw(), &h1, x.raw(), &one, one, res.raw(),&one)


      for(iter=1; iter<=h1;iter++){
        work(iter) = nt2::abs(b(i,1));
      }

      for(k=1;k<=n;k++)
      {
        xk = nt2::abs(x(k,1));
        for(iter=1;iter <=n;iter++)
        {
          work(iter) += abs(a(iter,k))*xk;
        }
      }

      for(iter=1;iter<=n;iter++)
      {
       if(work(iter) > safe2 ) s = nt2::max(s, nt2::abs(res(iter)) ) / work(iter);
       else s = nt2::max(s, nt2::abs(res(iter)) + safe1 ) / (work(iter) + safe1 );
      }
      berr(1) = s;

      ///Solve the new system  Ad = R
      NT2_F77NAME(dgetrs)(&trans ,&h1, &one, a.raw(), &h1, jpvt.raw(), res.raw(), &h1, &i);
      ///add correction  x = x +d
      for(iter=1;iter<=n;iter++) x(iter,1) += res(iter);


    }while( berr(1) > epsilon && 2*berr(1) < 3 && count <itermax )



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
  std::size_t   h,w,i;
  mutable double epsilon,safe1,safe2;
  mutable nt2_la_int i,h1,w1,nhrs,iter;
  mutable nt2::table<T> a,a1,b,b1;
  mutable nt2::table<T> ferr,berr,res,work;
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

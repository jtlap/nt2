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
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/inv.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/mtimes.hpp>


template<typename T> struct linsolve;

template<typename T> NT2_EXPERIMENT(linsolve< nt2::table<T> >)
{
  public:
  linsolve( std::size_t h_, std::size_t w_)
      : NT2_EXPRIMENT_CTOR(1.,"SECONDS")
      , h(h_), w(w_)
  {}

  virtual void run() const
  {
    a = A(nt2::_ , 1);
    B(nt2::_,1) = 1;
    tb = nt2::trans(B);
    b = mtimes(tb,a);
    B = mtimes(tb,B);
    a = nt2::inv(B);
    result = mtimes(a,b);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
     return r.second/1000000.;
  }

  virtual void info(std::ostream& os) const
  {
    os << "(" << h << "x" << w << ")";
  }

  virtual void reset() const
  {
    A = nt2::rand(h,w, nt2::meta::as_<T>());
    // A = nt2::cons<T>(nt2::of_size(3,3),1,4,7,2,3,8,5,6,9);
    B = A;
    result = nt2::zeros(h,w, nt2::meta::as_<T>());
    b  = nt2::zeros(h,w, nt2::meta::as_<T>());
  }

  private:
  std::size_t   h,w;
  mutable nt2::table<T> B,b, tb, result;
  mutable nt2::table<T> A, a ;
};


NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (3,3) );
NT2_RUN_EXPERIMENT_TPL( linsolve, (nt2::table<double>), (1000,1000) );


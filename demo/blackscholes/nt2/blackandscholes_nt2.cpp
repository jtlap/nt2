//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/fastnormcdf.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 {
  namespace tag
  {
    struct blackandscholes_ : ext::elementwise_<blackandscholes_> { typedef ext::elementwise_<blackandscholes_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::blackandscholes_, blackandscholes, 5)

  namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::blackandscholes_, tag::cpu_
                              , (A0)(A1)(A2)(A3)(A4)
                              , (generic_< arithmetic_<A0> >)
                                (generic_< arithmetic_<A1> >)
                                (generic_< arithmetic_<A2> >)
                                (generic_< arithmetic_<A3> >)
                                (generic_< arithmetic_<A4> >)
                              )
    {
      typedef A0 result_type;
      NT2_FUNCTOR_CALL(5)
      {
        A0 da   = nt2::sqrt(a2);
        A0 tmp1 = nt2::log(a0/a1);
        A0 tmp2 = nt2::sqr(a4);
        A0 tmp4 = nt2::fma(tmp2,nt2::Half<A0>(),a3);
        A0 tmp3 = (tmp4*a2)/(a4*da);
        A0 ed   = nt2::exp(-a3*a2);
        A0 d1   = tmp1 + tmp3;
        A0 d2   = nt2::fma(-a4,da,d1);
        A0 fd1  = nt2::fastnormcdf(d1);
        A0 fd2  = nt2::fastnormcdf(d2);
        return a0*fd1 -a1 * ed * fd2;
      }
    };
  }
}

template<typename T> NT2_EXPERIMENT(blackandscholes_exp)
{
public:
  typedef T value_type;
  blackandscholes_exp( std::size_t const& n)
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , size_(n)
  {
    Sa.resize(nt2::of_size(size_));
    Xa.resize(nt2::of_size(size_));
    Ta.resize(nt2::of_size(size_));
    ra.resize(nt2::of_size(size_));
    va.resize(nt2::of_size(size_));
    R.resize(nt2::of_size(size_));

    for(int i = 1; i <= size_; ++i) Sa(i)=Xa(i)=Ta(i)=ra(i)=va(i)= value_type(i);
  }

  virtual void run () const
  {
    R = nt2::blackandscholes(Sa, Xa, Ta, ra, va);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(size_);
  }

  virtual void info(std::ostream& os) const { os << size_; }

  virtual void reset() const
  {}

 private:
  mutable nt2::table<value_type> Sa, Xa, Ta, ra, va, R;
  std::size_t size_;
};
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (16));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (32));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (64));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (128));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (256));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (512));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (1024));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (2048));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (20480));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (204800));
NT2_RUN_EXPERIMENT_TPL( blackandscholes_exp, (float), (1024*1024));

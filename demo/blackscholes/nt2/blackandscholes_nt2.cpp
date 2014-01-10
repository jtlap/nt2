//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/unit/details/prng.hpp>

#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>

#include <nt2/sdk/bench/protocol/max_iteration.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>

#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>

#include <nt2/sdk/bench/stat/average.hpp>
#include <nt2/sdk/bench/stat/median.hpp>
#include <nt2/sdk/bench/stat/min.hpp>
#include <nt2/sdk/bench/stat/max.hpp>

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <nt2/table.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/fnms.hpp>
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
#include <nt2/include/functor.hpp>
#include <nt2/sdk/bench/benchmark.hpp>

#include <vector>
#include <iostream>

using namespace nt2::bench;
using namespace nt2;

namespace nt2
{
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
        A0 d2   = nt2::fnms(a4,da,d1);
        A0 fd1  = nt2::fastnormcdf(d1);
        A0 fd2  = nt2::fastnormcdf(d2);
        return nt2::fnms(a1*ed, fd2, a0*fd1);
      }
    };
  }
}

template<typename T> struct blackandscholes_simd
{
  blackandscholes_simd(std::size_t n)
                    :  size_(n)
  {
    Sa.resize(nt2::of_size(size_));
    Xa.resize(nt2::of_size(size_));
    Ta.resize(nt2::of_size(size_));
    ra.resize(nt2::of_size(size_));
    va.resize(nt2::of_size(size_));
    R.resize(nt2::of_size(size_));

    for(std::size_t i = 1; i <= size_; ++i)
      Sa(i) = Xa(i) = Ta(i) = ra(i) = va(i) = T(i);
  }

  void operator()()
  {
    R = nt2::blackandscholes(Sa, Xa, Ta, ra, va);
  }

  friend std::ostream& operator<<(std::ostream& os, blackandscholes_simd<T> const& p)
  {
    return os << "(" << p.size()<< ")";
  }

  std::size_t size() const { return size_ ; }

  private:
  nt2::table<T> Sa, Xa, Ta, ra, va, R;
  std::size_t size_;
};

NT2_REGISTER_BENCHMARK_TPL( blackandscholes_simd, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 2);

  run_during_with< blackandscholes_simd<float> > ( 1.
                                          , geometric(size_min,size_max,size_step)
                                          , cycles_per_element<stat::median_>()
                                          );
}

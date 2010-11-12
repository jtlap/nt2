/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_UNIT_DETAILS_UNARY_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_UNIT_DETAILS_UNARY_BENCHMARK_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <algorithm>
#include <nt2/include/timing.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/store.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/memory/allocator.hpp>

template<class T0,class Dummy,class Func, class MN0, class MX0>
void timing_test( Func callee, size_t size
                , MN0 min0, MX0 max0
                , const char* name = NULL )
{
  typedef T0                                      r_in0;
  typedef typename nt2::meta::scalar_of<T0>::type t_in0;

  // output value
  typedef typename std::tr1::result_of<Func(r_in0)>::type  out_t;
  static out_t out;

  // Input samples
  static std::vector<t_in0, nt2::memory::allocator<t_in0> >  in0(size);

  // Filling samples randomly
  for(size_t i=0; i<size; ++i) in0[i] = roll<t_in0>(min0,max0);

  std::cout << name << "(" << nt2::type_id<r_in0>().c_str() << ")"
            << " in "
            << "[" << min0 << ", "<< max0<<"[ = "
            << std::flush;

  std::vector<double> timings;
  double c(0.),t(0.);

  do
  {
    nt2::tic();
    {
      nt2::ctic();
      for(size_t i=0; i<size/nt2::meta::cardinal_of<r_in0>::value; i++)
      {
        out = callee(nt2::load<r_in0>(&in0[0],i));
      }
      c = nt2::ctoc(false) / double(size);
    }
    t += nt2::toc(false);
    timings.push_back(c);
  } while(t < NT2_TEST_DURATION);

  std::sort(timings.begin(),timings.end());
  std::cout << timings[timings.size()/2] << " cycles/value" << std::endl;
}

#endif

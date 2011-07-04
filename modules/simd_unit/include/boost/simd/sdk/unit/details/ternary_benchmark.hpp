/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_UNIT_DETAILS_TERNARY_BENCHMARK_HPP_INCLUDED
#define BOOST_SIMD_SDK_UNIT_DETAILS_TERNARY_BENCHMARK_HPP_INCLUDED

#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/simd/include/timing.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/simd/sdk/details/type_id.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

template<class T0,class T1, class T2
        ,class Dummy,class Func
        , class MN0, class MX0, class MN1, class MX1, class MN2, class MX2
        >
void timing_test( Func callee, size_t size
                , MN0 min0, MX0 max0
                , MN1 min1, MX1 max1
                , MN2 min2, MX2 max2
                , const char* name = NULL )
{
  typedef T0                                      r_in0;
  typedef T1                                      r_in1;
  typedef T2                                      r_in2;
  typedef typename boost::simd::meta::scalar_of<T0>::type t_in0;
  typedef typename boost::simd::meta::scalar_of<T1>::type t_in1;
  typedef typename boost::simd::meta::scalar_of<T2>::type t_in2;

  // output value
  typedef typename boost::simd::meta::result_of<Func(r_in0,r_in1,r_in2)>::type out_t;
  static out_t                                                        out;

  // Input samples
  static std::vector<t_in0, boost::simd::memory::allocator<t_in0> >  in0(size);
  static std::vector<t_in1, boost::simd::memory::allocator<t_in1> >  in1(size);
  static std::vector<t_in2, boost::simd::memory::allocator<t_in1> >  in2(size);

  // Filling samples randomly
  for(size_t i=0; i<size; ++i)
  {
    in0[i] = roll<t_in0>(min0,max0);
    in1[i] = roll<t_in1>(min1,max1);
    in2[i] = roll<t_in2>(min2,max2);
  }

  std::cout << name << "("
                    << boost::simd::type_id<r_in0>().c_str()
            << ", " << boost::simd::type_id<r_in1>().c_str()
            << ", " << boost::simd::type_id<r_in2>().c_str()
            << ") " << std::flush;

  std::vector<double> timings;
  double c(0.),t(0.);

  static const size_t c0 = boost::simd::meta::cardinal_of<r_in0>::value;
  static const size_t c1 = boost::simd::meta::cardinal_of<r_in1>::value;
  static const size_t c2 = boost::simd::meta::cardinal_of<r_in2>::value;
  static const size_t nb1 =  (c0 < c1) ? c1 : c0; 
  static const size_t nb  =  (c2 < nb1) ? nb1 : c2;  

  do
  {
    boost::simd::tic();
    {
      boost::simd::ctic();
      for(size_t i=0; i<size/nb; i++)
      {
        out = callee( boost::simd::load<r_in0>(&in0[0],i)
                    , boost::simd::load<r_in1>(&in1[0],i)
                    , boost::simd::load<r_in2>(&in2[0],i)
                    );
      }
      c = boost::simd::ctoc(false) / double(size);
    }
    t += boost::simd::toc(false);
    timings.push_back(c);
  } while(t < BOOST_SIMD_TEST_DURATION);

  std::sort(timings.begin(),timings.end());
  std::cout << timings[timings.size()/2] << " cycles/value\n" << std::flush;
}

#endif

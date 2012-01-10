//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_PERFORM_BENCHMARK_HPP_INCLUDED
#define NT2_SDK_UNIT_PERFORM_BENCHMARK_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include <nt2/include/timing.hpp>

namespace nt2 { namespace unit
{
  template<class RandAccessIter> inline
  nt2::details::cycles_t median(RandAccessIter begin, RandAccessIter end)
  {
    std::size_t size = end - begin;
    std::size_t middleIdx = size/2;
    RandAccessIter target = begin + middleIdx;
    std::nth_element(begin, target, end);

    if(size % 2) return *target;
    else
    {
      nt2::details::cycles_t a = *target;
      RandAccessIter targetNeighbor= target-1;
      std::nth_element(begin, targetNeighbor, end);
      return (a+*targetNeighbor)/nt2::details::cycles_t(2);
    }
  }

  template<class Test> inline
  nt2::details::cycles_t perform_benchmark(Test test, double duration)
  {
    std::vector<nt2::details::cycles_t> cycles;
    double c(0.),t(0.),vt(0.);   
    nt2::details::cycles_t vc;

    do
    {
      vt = nt2::details::now();
      {
        vc = nt2::details::read_cycles();
        test();
        vc = nt2::details::read_cycles() - vc;
      }
      vt = nt2::details::now() - vt;
      t += vt;
      cycles.push_back(vc);
    } while(t < duration);
    
    return median(cycles.begin(),cycles.end());
  }
} }

#endif

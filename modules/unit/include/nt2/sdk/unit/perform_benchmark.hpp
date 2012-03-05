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

  template <typename T> 
  struct benchmark_res_t
  {
    benchmark_res_t(): median(0.){}
    std::vector<T> data;
    T median;
  };

  template<class RandAccessIter, typename T> inline
  void median(RandAccessIter begin, RandAccessIter end, T& res)
  {
    std::size_t size = end - begin;
    std::size_t middleIdx = size/2;
    RandAccessIter target = begin + middleIdx;
    std::nth_element(begin, target, end);

    if(size % 2) res = *target;
    else
    {
      T a = *target;
      RandAccessIter targetNeighbor= target-1;
      std::nth_element(begin, targetNeighbor, end);
      res =  (a+*targetNeighbor)/T(2);
    }
  }

  template<class Test, typename T> inline
  void perform_benchmark(Test test, double duration, benchmark_res_t<T>& res )
  {
    std::vector<T> cycles;
    double t(0.),vt(0.);
    T vc;
    
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
      res.data = cycles;
      median(cycles.begin(),cycles.end(), res.median);
  }

  template<class Test> inline
  void perform_benchmark(Test test, double duration, benchmark_res_t<double>& res )
  {
    std::vector<double> time;
    double t(0.),vt(0.);
    double vc;
    
      do
        {
          vt = nt2::details::now();
          {
            vc = nt2::details::now();
            test();
            vc = nt2::details::now() - vc;
          }
          vt = nt2::details::now() - vt;
          t += vt;
          time.push_back(vc);
        } while(t < duration);
      res.data = time;
      median(time.begin(),time.end(), res.median);
  }

} }

#endif

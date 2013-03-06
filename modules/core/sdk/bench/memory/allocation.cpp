//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 allocation bench"

#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/fixed_allocator.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <iostream>
#include <vector>

template<class Allocator> NT2_EXPERIMENT(allocation_test)
{
  public:

  typedef typename Allocator::pointer pointer;

  allocation_test(int n) : NT2_EXPRIMENT_CTOR(1.,"cycles/elements"), N(n)
  {
    a0.reserve(n);
  }

  ~allocation_test() { reset(); }

  virtual void run() const
  {
    a0.push_back(alloc.allocate(N));
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(N);
  }

  virtual void info(std::ostream& os) const { os << N; }

  virtual void reset() const
  {
    for(std::size_t n=0;n<a0.size();++n) alloc.deallocate(a0[n],N);
    a0.clear();
  }

  private:
  mutable Allocator alloc;
  mutable std::vector<pointer> a0;
  int N;
};

#define NT2_ALLOCATION_EXP(T,N)                             \
NT2_RUN_EXPERIMENT_TPL( allocation_test                          \
                      , (std::allocator<T>)                 \
                        (boost::simd::memory::allocator<T>) \
                        (nt2::memory::fixed_allocator<T>)   \
                      , (1 <<  N)                           \
                      )                                     \
/**/

NT2_ALLOCATION_EXP(double, 0);
NT2_ALLOCATION_EXP(double, 4);
NT2_ALLOCATION_EXP(double, 8);
NT2_ALLOCATION_EXP(double,16);

NT2_ALLOCATION_EXP(float, 0);
NT2_ALLOCATION_EXP(float, 4);
NT2_ALLOCATION_EXP(float, 8);
NT2_ALLOCATION_EXP(float,16);

NT2_ALLOCATION_EXP(char, 0);
NT2_ALLOCATION_EXP(char, 4);
NT2_ALLOCATION_EXP(char, 8);
NT2_ALLOCATION_EXP(char,16);

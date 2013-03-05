//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 array_buffer bench"

#include <nt2/sdk/memory/array_buffer.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <vector>

template<class Buffer> NT2_EXPERIMENT(static_buffer_test)
{
  public:
  static_buffer_test(std::size_t sz)
        : NT2_EXPRIMENT_CTOR(1.,"cycles"), up(sz)
  {}

  ~static_buffer_test() { pump[rand() % up] = data[rand() % up]; }

  virtual void run() const
  {
    for(std::size_t i = 0; i < up; ++i) data[i] = data2[i];
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(up);
  }

  virtual void info(std::ostream& os) const { os << up; }

  private:
  std::size_t     up;
  mutable Buffer  data, data2;
  static  Buffer  pump;
};

template<class Buffer> Buffer buffer_test<Buffer>::pump;

#define NT2_BUFFER_EXP(T,N)                                                      \
NT2_RUN_EXPERIMENT_TPL( buffer_test                                              \
                      , ((nt2::memory::array_buffer<T,boost::mpl::size_t<N> >))  \
                        ((boost::array<T,N>))                                    \
                        (T[N])                                                   \
                      , (N)                                                      \
                      )                                                          \
/**/

NT2_BUFFER_EXP(double , 1024);
NT2_BUFFER_EXP(float  , 1024);
NT2_BUFFER_EXP(int    , 1024);
NT2_BUFFER_EXP(short  , 1024);
NT2_BUFFER_EXP(char   , 1024);

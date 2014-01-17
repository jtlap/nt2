//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
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

#include <nt2/sdk/bench/setup/arithmetic.hpp>

#include <nt2/sdk/bench/stats/average.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/stats/min.hpp>
#include <nt2/sdk/bench/stats/max.hpp>
#include <cmath>

using namespace nt2::bench;

// Experiment are simple functor
struct some_task : experiment
{
  some_task(int) {}
  void operator()() { sleep(1); }
};

NT2_REGISTER_BENCHMARK( duration )
{
  run_during<some_task>( 3., absolute_time<stats::median_>() );
}

NT2_REGISTER_BENCHMARK( iteration )
{
  run_over<some_task>( 1, absolute_time<stats::median_>() );
  run_over<some_task>( 2, absolute_time<stats::median_>() );
  run_over<some_task>( 3, absolute_time<stats::median_>() );
  run_over<some_task>( 5, absolute_time<stats::median_>() );
}

// can even be template functor
template<typename T> struct init_data : experiment
{
  init_data(int) {}
  void operator()() { data_ = T(0); }
  private:
  T data_;
};

NT2_REGISTER_BENCHMARK_TPL( templates, (int)(short) )
{
  run_during< init_data<T> >( 3.
                            , absolute_time<stats::min_>()
                            , absolute_time<stats::average_>()
                            , absolute_time<stats::median_>()
                            , absolute_time<stats::max_>()
                            );
}

// can even be stateful
template<typename T> struct process_cosinus
{
  process_cosinus(std::size_t n) : size_(n), data_(n), result_(n)
  {
    nt2::roll(data_,-3,+3);
  }

  void operator()()
  {
    for(std::size_t i=0;i<size_;++i)
      result_[i] = std::cos(data_[i]);
  }

  std::size_t size() const { return size_; }

  private:
  std::size_t     size_;
  std::vector<T>  data_, result_;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, process_cosinus<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( stateful, (double)(float) )
{
  run_during_with< process_cosinus<T> > ( 1.
                                        , arithmetic( args("min",100)
                                                    , args("max",1000)
                                                    , args("step",50)
                                                    )
                                        , cycles_per_element<stats::median_>()
                                        );
}

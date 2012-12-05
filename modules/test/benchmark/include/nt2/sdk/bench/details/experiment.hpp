//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_EXPERIMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_EXPERIMENT_HPP_INCLUDED

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/bench/details/tick.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/median.hpp>

#include <iomanip>
#include <iostream>

namespace nt2 { namespace details
{
  /// CRTP experiment class
  template<class Experiment, class Tick> struct experiment : unit_test
  {
    experiment ( double dur, test_suite const* x )
              : unit_test(x,0,0), duration(dur)
    {}

    virtual ~experiment() {}

    /// CRTP Derived access
    Experiment const* task() const
    {
      return static_cast<Experiment const*>(this);
    }

    /// CRTP Derived member delegation
    void    call()  const { task()->call();  }
    void    reset() const { task()->reset(); }
    double  size()  const { return static_cast<double>(task()->size());  }

    /// Benchmark process
    virtual void process() const
    {
      typedef boost::accumulators::stats< boost::accumulators::tag::mean
                                        , boost::accumulators::tag::median
                                        >                               stats_t;
      boost::accumulators::accumulator_set<double, stats_t>  acc;

      std::cout << std::setiosflags(std::ios::fixed)
                << std::setw(20) << std::left << nt2::type_id<Experiment>()
                << std::setw(10) << std::right << task()->size();

            double  t(0.);
     const  double  sz(size());

      do
      {
        double vt = nt2::details::now();
        {
          double vc = Tick::call();
          call();
          acc((Tick::call() - vc)/sz);
        }
        vt = nt2::details::now() - vt;
        t += vt;
        reset();
      } while(t < duration);

      std::cout << std::setiosflags(std::ios::fixed)
                << std::setprecision(2) << std::setw(20) << std::right
                << std::scientific
                << boost::accumulators::mean(acc)
                << Tick::unit();

      std::cout << std::setiosflags(std::ios::fixed)
                << std::setprecision(2) << std::setw(20) << std::right
                << std::scientific
                << boost::accumulators::median(acc)
                << Tick::unit()
                << std::endl;

      details::unit_test::advance();
    }

    private:
    double      duration;
  };
} }

/*!
 @brief Constructor of an Experiment
**/
#define NT2_EXPERIMENT_CTOR(Type, Tick, Duration)           \
::nt2::details::experiment<Type,::nt2::details::Tick##_ >   \
                          ( Duration                        \
                          , &nt2::details::main_bench_suite \
                          )                                 \
/**/

/*!
 @brief Registration of an Experiment
**/
#define NT2_EXPERIMENT(Type,Tick)                                       \
class Type : ::nt2::details::experiment<Type,::nt2::details::Tick##_ >  \
/**/

#endif

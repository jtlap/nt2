//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_DETAILS_BASE_EXPERIMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_DETAILS_BASE_EXPERIMENT_HPP_INCLUDED

#include <nt2/sdk/bench/config.hpp>
#include <nt2/sdk/unit/details/unit_test.hpp>
#include <nt2/sdk/timing/now.hpp>
#include <boost/dispatch/attributes.hpp>
#include <string>

namespace nt2
{
  typedef std::pair<nt2::cycles_t, nt2::microseconds_t> benchmark_result_t;

  namespace details
  {
    class BOOST_SYMBOL_VISIBLE base_experiment : public unit_test
    {
      public:
      NT2_TEST_BENCHMARK_DECL base_experiment();

      NT2_TEST_BENCHMARK_DECL
      base_experiment ( double dur
                      , const std::string& i
                      , const std::string& n
                      , const std::string& u
                      , test_suite const* x
                      );

      NT2_TEST_BENCHMARK_DECL void process() const;

      virtual BOOST_DISPATCH_NOTHROW
      void    run() const = 0;

      virtual BOOST_DISPATCH_NOTHROW
      double  compute(benchmark_result_t const& r) const { return -1; }

      virtual BOOST_DISPATCH_NOTHROW
      void    reset() const {}

      using unit_test::advance;

      protected:
      std::size_t size;
      double      duration;
      std::string name, unit, info;
    };
  }
}

#endif

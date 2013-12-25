//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_STAT_MEDIAN_HPP_INCLUDED
#define NT2_SDK_BENCH_STAT_MEDIAN_HPP_INCLUDED

#include <boost/accumulators/statistics/median.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace nt2 { namespace bench { namespace stat
{
  /*!
    @brief Median statistic

    Used as a Metric parameter, median_ make the metric computes the
    median value of its samples.

    @note The median algorithm requires a minimal amount of samples to be
    correct. currently, this minimum is set to 5 and any experiment providing
    less than this amount of samples will make the benchmark terminates with a
    failure. In this case, it is advised to modify the benchmark code or
    parameters so that enough samples are taken.
  **/
  struct median_
  {
    /// @brief Samples processing function
    template<typename Samples> static inline double evaluate(Samples const& d)
    {
      if( std::size_t n = boost::accumulators::count(d) < 5 )
      {
        std::cerr << "Only " << n << " samples for median computing "
                  << "while at least 5 are required.\n";

        std::exit(EXIT_FAILURE);
      }

      return boost::accumulators::median(d);
    }

    /// @brief Statistics display
    static inline std::string unit() { return " (med)"; }
  };
} } }

#endif

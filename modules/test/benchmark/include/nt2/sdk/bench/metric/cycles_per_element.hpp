//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_BENCH_METRIC_CYCLES_PER_ELEMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_METRIC_CYCLES_PER_ELEMENT_HPP_INCLUDED

#include <nt2/sdk/bench/details/measure.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <string>

namespace nt2 { namespace bench
{
  /*!
    @brief CPU cycles metric

    This metric extract cycles based informations from a
    set of timing samples and return a measure in CPU cycles.

    @tparam Stat Statistic to compute over the provided samples
  **/
  template<typename Stat> struct cycles_per_element
  {
    /// @brief Evaluation of the metric in CPU cycles
    template<typename Experiment> inline
    double operator() ( Experiment const& e
                      , std::string const& name
                      , details::times_set const&
                      , details::cycles_set const& c
                      ) const
    {
      double m = Stat::evaluate(c) / e.size();
      details::measures_map[details::identify_result(name,e,*this)] = m;
      return m;
    }

    /// @brief Metric display
    inline std::string unit() const
    {
      return "cpe" + Stat::unit();
    }
  };
} }

#endif

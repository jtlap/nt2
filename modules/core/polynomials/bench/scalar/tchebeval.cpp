//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

#include <nt2/include/functions/tchebeval.hpp>
#include <vector>

using namespace nt2::bench;

template<typename T>
struct tchebeval_
{
  tchebeval_( std::size_t n ) : size_(n), in(size_),out(size_)
  {
    nt2::roll(in,-10.,10.);
    coeff[0] = T(2); coeff[1] = T(3); coeff[2] = T(4);
  }

  void operator()()
  {
    for(std::size_t i=0;i<size_;++i)
      out[i] = nt2::tchebeval(in[i], coeff);
  }

  std::size_t size() const { return size_; }

  friend std::ostream& operator<<(std::ostream& os, tchebeval_<T> const& p)
  {
    return os << "(" << p.size_ << ")";
  }

  private:
  std::size_t       size_;
  std::vector<T>    in,out;
  boost::array<T,3> coeff;
};

NT2_REGISTER_BENCHMARK_TPL( tchebeval_, (float)(double) )
{
  std::size_t s = args("size", 1024);

  run_during_with< tchebeval_<T> > ( 3.
                                , fixed(s)
                                , cycles_per_element<stats::median_>()
                                );
}

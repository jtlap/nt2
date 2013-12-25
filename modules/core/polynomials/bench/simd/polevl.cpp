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
#include <nt2/sdk/bench/stat/median.hpp>

#include <nt2/include/functions/polevl.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <vector>

using namespace nt2::bench;

template<typename T>
struct polevl_
{
  typedef boost::simd::native<T,NT2_SIMD_DEFAULT_EXTENSION> vT;

  polevl_( std::size_t n ) : size_(n), in(size_),out(size_)
  {
    nt2::roll(in,-10.,10.);
    coeff[0] = T(2); coeff[1] = T(3); coeff[2] = T(4);
  }

  void operator()()
  {
    for(std::size_t i=0;i<size_;++i)
    {
      boost::simd::
      aligned_store ( nt2::polevl(boost::simd::aligned_load<vT>(&in[i]),coeff)
                    , &out[i]
                    );
    }
  }

  std::size_t size() const { return size_; }

  friend std::ostream& operator<<(std::ostream& os, polevl_<T> const& p)
  {
    return os << "(" << p.size_ << ")";
  }

  private:
  std::size_t                                size_;
  boost::array<T,3>                          coeff;
  std::vector<T,boost::simd::allocator<T> >  in,out;
};

NT2_REGISTER_BENCHMARK_TPL( polevl_, (float)(double) )
{
  std::size_t s = args("size", 1024);

  run_during_with< polevl_<T> > ( 3.
                                , fixed(s)
                                , cycles_per_element<stat::median_>()
                                );
}


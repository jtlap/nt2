//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
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

#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>

#include <nt2/sdk/bench/stats/average.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/stats/min.hpp>
#include <nt2/sdk/bench/stats/max.hpp>

#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/fastnormcdf.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/fnms.hpp>
#include <boost/simd/include/functions/sqrt.hpp>
#include <boost/simd/include/functions/sqr.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/memory/allocator.hpp>

#include <vector>
#include <iostream>

using namespace nt2::bench;
using namespace nt2;

template <class A0>
BOOST_FORCEINLINE A0 blackandscholes(A0 const &a0, A0 const &a1, A0 const &a2, A0 const &a3, A0 const &a4)
{
  A0 da   = boost::simd::sqrt(a2);
  A0 tmp1 = nt2::log(a0/a1);
  A0 tmp2 = boost::simd::sqr(a4);
  A0 tmp4 = boost::simd::fma(tmp2,nt2::Half<A0>(),a3);
  A0 tmp3 = (tmp4*a2)/(a4*da);
  A0 ed   = nt2::exp(-a3*a2);
  A0 d1   = tmp1 + tmp3;
  A0 d2   = boost::simd::fnms(a4,da,d1);
  A0 fd1  = nt2::fastnormcdf(d1);
  A0 fd2  = nt2::fastnormcdf(d2);
  return boost::simd::fnms(a1*ed, fd2, a0*fd1);
}

template<typename T> struct blackandscholes_simd
{
  blackandscholes_simd(std::size_t n)
                    :  size_(n)
  {
    Sa.resize(size_);
    Xa.resize(size_);
    Ta.resize(size_);
    ra.resize(size_);
    va.resize(size_);
    R.resize(size_);

    for(i = 0; i <size_; ++i)
      Sa[i] = Xa[i] = Ta[i] = ra[i] = va[i] = T(i+1);
  }

  void operator()()
  {
    using boost::simd::pack;
    using boost::simd::native;
    using boost::simd::aligned_store;
    using boost::simd::aligned_load;

    typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> type;
    step_size_=boost::simd::meta::cardinal_of<type>::value;
    i=0;

    while (size_-i>=step_size_)
    {
      type Sa_tmp = aligned_load<type>(&Sa[i]);
      type Xa_tmp = aligned_load<type>(&Xa[i]);
      type Ta_tmp = aligned_load<type>(&Ta[i]);
      type ra_tmp = aligned_load<type>(&ra[i]);
      type va_tmp = aligned_load<type>(&va[i]);
      aligned_store(blackandscholes(Sa_tmp, Xa_tmp, Ta_tmp, ra_tmp, va_tmp), &R[i]);
      i += step_size_;
    }
    for (; i<size_; i++)
      R[i] += blackandscholes(Sa[i], Xa[i], Ta[i], ra[i], va[i]);
  }

  friend std::ostream& operator<<(std::ostream& os, blackandscholes_simd<T> const& p)
  {
    return os << "(" << p.size()<< ")";
  }

  std::size_t size() const { return size_ ; }

  private:
  std::vector<T, boost::simd::allocator<T> > Sa, Xa, Ta, ra, va, R;
  std::size_t step_size_, size_, i, j;
};

NT2_REGISTER_BENCHMARK_TPL( blackandscholes_simd, (float) )
{
  std::size_t size_min = args("size_min", 16);
  std::size_t size_max = args("size_max", 4096);
  std::size_t size_step = args("size_step", 2);

  run_during_with< blackandscholes_simd<float> > ( 1.
                                          , geometric(size_min,size_max,size_step)
                                          , cycles_per_element<stats::median_>()
                                          );
}

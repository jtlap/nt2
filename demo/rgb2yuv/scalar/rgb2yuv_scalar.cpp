//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/sdk/bench/benchmark.hpp>
#include <fstream>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include  <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/arithmetic/functions/muls.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/sum.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/memory/allocator.hpp>

using namespace nt2;

template<typename K, typename L>
BOOST_FORCEINLINE void rgb2yuv_work(const K& r, const K& g, const K& b, L *y, L *u, L *v)
{
  *y = 0.299f*r + 0.587f*g + 0.114f*b;
  *u = 0.492f*(b - *y);
  *v = 0.877f*(r - *y);
}

template<typename T>
NT2_EXPERIMENT(rgb2yuv_scalar)
{
  public :
    rgb2yuv_scalar(int h, int w)
    : NT2_EXPERIMENT_CTOR(1,"cycles/elements"), height(h), width(w), size(h*w)
  {
    y.resize(size);
    u.resize(size);
    v.resize(size);
    r.resize(size);
    g.resize(size);
    b.resize(size);
    for(int i=0; i<size; i++)
      r[i] = g[i] = b[i] = y[i] = u[i] = v[i] = T(i);
  }

  virtual void info(std::ostream& os) const { os <<size; }

  BOOST_FORCEINLINE virtual void run() const
  {
    std::size_t size = r.size();

    #pragma simd
    for(std::size_t it = 0; it < size; it++)
      rgb2yuv_work(r[it], g[it], b[it], &y[it], &u[it], &v[it]);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(size);
  }

  virtual void reset()
  {
  }

  private:
    int height;
    int width;
    int size;
    std::vector<T,boost::simd::allocator<T> > r;
    std::vector<T,boost::simd::allocator<T> > g;
    std::vector<T,boost::simd::allocator<T> > b;
    mutable std::vector<T,boost::simd::allocator<T> > y;
    mutable std::vector<T,boost::simd::allocator<T> > u;
    mutable std::vector<T,boost::simd::allocator<T> > v;
};

NT2_RUN_EXPERIMENT_TPL(rgb2yuv_scalar,(float)(double),(37,1));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_scalar,(float)(double),(50,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_scalar,(float)(double),(1000,500));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_scalar,(float)(double),(312,43));

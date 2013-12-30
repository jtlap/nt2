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
  using boost::simd::aligned_store;
  K tmp_y = K(0.299f)*r + K(0.587f)*g + K(0.114f)*b;
  aligned_store(tmp_y, y);
  aligned_store(K(0.492f)*(b - tmp_y), u);
  aligned_store(K(0.877f)*(r - tmp_y), v);
}

template<typename T>
NT2_EXPERIMENT(rgb2yuv_simd)
{
  public :
    rgb2yuv_simd(int h, int w)
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
    using boost::simd::pack;
    using boost::simd::aligned_load;
    using boost::simd::sum;

    typedef pack<T> type;
    std::size_t size       = r.size();
    std::size_t step_size  = boost::simd::meta::cardinal_of<type>::value;
    std::size_t aligned_sz = size & ~(step_size-1);
    std::size_t it         = 0;

    for(std::size_t m=aligned_sz; it != m; it+=step_size)
    {
      type x1 = aligned_load< type >(&r[it]);
      type x2 = aligned_load< type >(&g[it]);
      type x3 = aligned_load< type >(&b[it]);

      rgb2yuv_work(x1, x2, x3, &y[it], &u[it], &v[it]);
    }

    for(std::size_t m=size; it != m; it++)
    {
      rgb2yuv_work(r[it], g[it], b[it], &y[it], &u[it], &v[it]);
    }
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

NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(32,32));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(64,64));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(128,128));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(256,256));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(512,512));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(1024,1024));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(2048,2048));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv_simd,(float),(4196,4196));

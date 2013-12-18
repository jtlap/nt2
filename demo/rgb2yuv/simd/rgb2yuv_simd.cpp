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

#define vec std::vector<K,boost::simd::allocator<K> >

//typedef std::vector<K,boost::simd::allocator<K> > vec;

template<typename K>
BOOST_FORCEINLINE void rgb2yuv_work(const vec& r, const vec& g, const vec& b, vec& y, vec& u, vec& v)
{
  using boost::simd::pack;
  using boost::simd::aligned_load;
  using boost::simd::aligned_store;
  using boost::simd::sum;

  typedef pack<K> type;
  type tmp_y;
  std::size_t size       = r.size();
  std::size_t step_size  = boost::simd::meta::cardinal_of<type>::value;
  std::size_t aligned_sz = size & ~(step_size-1);
  std::size_t it         = 0;

  for(std::size_t m=aligned_sz; it != m; it+=step_size)
  {
    type x1 = aligned_load< type >(&r[it]);
    type x2 = aligned_load< type >(&g[it]);
    type x3 = aligned_load< type >(&b[it]);

    tmp_y   = K(0.299f)*x1 + K(0.587f)*x2 + K(0.114f)*x3;

    aligned_store(tmp_y, &y[it]);
    aligned_store(K(0.492f)*(x3 - tmp_y), &u[it]);
    aligned_store(K(0.877f)*(x1 - tmp_y), &v[it]);
  }

  for(std::size_t m=size; it != m; it++)
  {
    y[m] = 0.299f*r[it] + 0.587f*g[m] + 0.114f*b[it];
    u[m] = 0.492f*(b[it]-y[it]);
    v[m] = 0.877f*(r[it]-y[it]);
  }
}

template<typename T>
NT2_EXPERIMENT(rgb2yuv)
{
  public :
    rgb2yuv(int h, int w)
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
    rgb2yuv_work(r, g, b, y, u, v);
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

NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(37,1));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(50,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(1000,500));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(312,43));

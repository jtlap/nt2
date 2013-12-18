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

using namespace nt2;

#define vec std::vector<K>

//typedef std::vector<K,boost::simd::allocator<K> > vec;
template<typename K>
BOOST_FORCEINLINE void rgb2yuv_work(const vec& r, const vec& g, const vec& b, vec& y, vec& u, vec& v)
{
  std::size_t size = r.size();
  #pragma simd
  for(std::size_t i=0; i < size; i++)
  {
    y[i] = 0.299f*r[i] + 0.587f*g[i] + 0.114f*b[i];
    u[i] = 0.492f*(b[i]-y[i]);
    v[i] = 0.877f*(r[i]-y[i]);
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

    for(std::size_t i=0; i<size; i++)
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
  {}

  std::size_t height, width, size;
  mutable std::vector<T> r, g ,b ,y ,u ,v;
};

NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(37,1));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(50,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(1000,500));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(312,43));

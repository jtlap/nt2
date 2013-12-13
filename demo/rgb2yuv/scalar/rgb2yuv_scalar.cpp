//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/sdk/bench/benchmark.hpp>
#include <fstream>

using namespace nt2;

template<typename T>
NT2_EXPERIMENT(rgb2yuv)
{
  public :
    rgb2yuv(int h, int w)
    : NT2_EXPERIMENT_CTOR(1,"cycles/elements"), height(h), width(w), size(h*w)
  {
    y  = (T*)malloc(size*sizeof(T));
    u  = (T*)malloc(size*sizeof(T));
    v  = (T*)malloc(size*sizeof(T));
    r  = (T*)malloc(size*sizeof(T));
    g  = (T*)malloc(size*sizeof(T));
    b  = (T*)malloc(size*sizeof(T));

    for(int i=0; i<size; i++)
      r[i] = g[i] = b[i] = y[i] = u[i] = v[i] = T(i);
  }

  virtual void info(std::ostream& os) const { os <<size; }

  BOOST_FORCEINLINE virtual void run() const
  {
    #pragma simd
    for(int i=0; i < size; i++)
      {
        y[i]=0.299f*r[i] + 0.587f*g[i] + 0.114f*b[i];
        u[i]=0.492f*(b[i]-y[i]);
        v[i]=0.877f*(r[i]-y[i]);
      }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(size);
  }

  virtual void reset()
  {
    free(r);
    free(g);
    free(b);
    free(y);
    free(u);
    free(v);
  }

  private:
    int height;
    int width;
    int size;
    T* r;
    T* g;
    T* b;
    T* y;
    T* u;
    T* v;
};

NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float),(1337,1337));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float),(50,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float),(100,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float),(500,10));

NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(double),(100,100));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(double),(50,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(double),(100,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(double),(500,10));


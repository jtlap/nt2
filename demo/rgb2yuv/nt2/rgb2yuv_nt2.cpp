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
#include <nt2/table.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/sum.hpp>

using namespace nt2;
template<typename T>
NT2_EXPERIMENT(rgb2yuv)
{
  public :
    typedef T value_type;
    rgb2yuv(int h, int w)
    : NT2_EXPERIMENT_CTOR( 1,"cycles/elements"), height(h), width(w), size(h*w)
  {
    y.resize(nt2::of_size(size));
    u.resize(nt2::of_size(size));
    v.resize(nt2::of_size(size));
    r.resize(nt2::of_size(size));
    g.resize(nt2::of_size(size));
    b.resize(nt2::of_size(size));

    for(int i=1; i<=size; i++)
      r(i) = g(i) = b(i) = y(i) = u(i) = v(i) = T(i);
  }
  virtual void info(std::ostream& os) const { os <<size; }

  BOOST_FORCEINLINE virtual void run() const
  {
    y = T(0.299f)*r + T(0.587f)*g + T(0.114f)*b;
    u = T(0.492f)*(b - y);
    v = T(0.877f)*(r - y);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(size);
  }

  virtual void reset() const
  {
  }

  private:
    int height;
    int width;
    int size;
    mutable nt2::table<value_type> y, u, v;
    nt2::table<value_type> r, g, b;
};

NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(100,100));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(50,50));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(1000,500));
NT2_RUN_EXPERIMENT_TPL(rgb2yuv,(float)(double),(312,43));

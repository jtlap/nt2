//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/polynomials/include/functions/plevl.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <nt2/sdk/bench/benchmark.hpp>

template<typename T> NT2_EXPERIMENT(plevl_bench)
{
  public:
  typedef typename boost::simd::meta::scalar_of<T>::type base_t;

  plevl_bench(std::size_t s) : NT2_EXPERIMENT_CTOR(1,"cycles/elements"), size(s)
  {
    coeff[0] = base_t(2); coeff[1] = base_t(3); coeff[2] = base_t(4);
  }

  virtual void run() const
  {
    for(int i=0;i<size;i+=T::static_size)
      boost::simd::aligned_store(nt2::plevl(boost::simd::aligned_load<T>(&in[i]), coeff),&out[i]);
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(size);
  }

  virtual void info(std::ostream& os) const { os << size; }

  virtual void reset() const
  {
    in.resize(size);
    out.resize(size);
    nt2::roll(in,-10,10);
  }

  private:
  int       size;
  mutable   std::vector<base_t,boost::simd::allocator<base_t> > in,out;
  boost::array<base_t,3>        coeff;
};

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef boost::simd::native<float,ext_t> vf_t;
typedef boost::simd::native<double,ext_t> vd_t;

NT2_RUN_EXPERIMENT_TPL( plevl_bench, (vf_t)(vd_t), (1024) );

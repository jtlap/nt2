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
#include <nt2/sdk/bench/benchmark.hpp>

template<typename T> NT2_EXPERIMENT(plevl_bench)
{
  public:
  plevl_bench(std::size_t s) : NT2_EXPRIMENT_CTOR(1,"cycles/elements"), size(s)
  {
    coeff[0] = T(2); coeff[1] = T(3); coeff[2] = T(4);
  }

  virtual void run() const
  {
    for(int i=0;i<size;++i) out[i] = nt2::plevl(in[i], coeff);
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
  mutable   std::vector<T>  in,out;
  boost::array<T,3>         coeff;
};

NT2_RUN_EXPERIMENT_TPL( plevl_bench, (float)(double), (1024) );

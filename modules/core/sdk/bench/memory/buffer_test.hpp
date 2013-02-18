/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BUFFER_TEST_HPP_INCLUDED
#define BUFFER_TEST_HPP_INCLUDED

#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/include/functions/as_size.hpp>
#include <nt2/core/container/table/semantic.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

#include <nt2/sdk/bench/benchmark.hpp>
#include <iostream>
#include <vector>

template<class Buffer>
struct  buffer_test
      : public nt2::details::base_experiment
{
  public:
  buffer_test(std::size_t sz)
        : NT2_EXPRIMENT_CTOR(1.,"cycles/elements")
        , up(sz), data(sz), data2(sz)
  {}

  virtual void run() const
  {
    for(std::size_t i = 0; i < up; ++i) data[i] = data2[i];
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(up);
  }

  virtual void info(std::ostream& os) const { os << up; }

  private:
  std::size_t               up;
  mutable Buffer data, data2;
};

template<class T>
struct  buffer_test< nt2::memory::container<T,nt2::settings()> >
      : public nt2::details::base_experiment
{
  public:
  typedef nt2::memory::container<T,nt2::settings()> buffer_t;

  buffer_test(std::size_t sz)
        : NT2_EXPRIMENT_CTOR(1.,"cycles/elements")
        , up(sz), data(), data2(nt2::as_size(sz))
  {}

  virtual void run() const
  {
    for(std::size_t i = 0; i < up; ++i) data[i] = data2[i];
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(up);
  }

  virtual void info(std::ostream& os) const { os << up; }

  private:
  std::size_t     up;
  mutable buffer_t  data, data2;
};

#endif

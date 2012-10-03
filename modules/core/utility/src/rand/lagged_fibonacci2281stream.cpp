/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/core/utility/config.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace nt2
{
  void lagged_fibonacci2281stream_::seed(std::size_t s)
  {
    generator_.seed(s);
  }

  void lagged_fibonacci2281stream_::randn(double* data, std::size_t i0, std::size_t i1)
  {
    boost::random::normal_distribution<double> dist;
    for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
  }

  void lagged_fibonacci2281stream_::randn(float*  data, std::size_t i0, std::size_t i1)
  {
    boost::random::normal_distribution<float> dist;
    for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
  }

  void lagged_fibonacci2281stream_::rand(double* data, std::size_t i0, std::size_t i1)
  {
    boost::random::uniform_real_distribution<double> dist;
    for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
  }

  void lagged_fibonacci2281stream_::rand(float*  data, std::size_t i0, std::size_t i1)
  {
    boost::random::uniform_real_distribution<float> dist;
    for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
  }

  lagged_fibonacci2281stream_::~lagged_fibonacci2281stream_()
  {
  }

  nt2::randstream_* lagged_fibonacci2281stream()
  {
    static nt2::lagged_fibonacci2281stream_ instance;
    return &instance;
  }
}

//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_RANDSTREAM_HPP_INCLUDED
#define NT2_CORE_UTILITY_RANDSTREAM_HPP_INCLUDED

#include <nt2/core/utility/config.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/lagged_fibonacci.hpp>

namespace nt2
{
  class randstream_
  {
    public:
    virtual void rand(double* data, std::size_t i0, std::size_t i1) = 0;
    virtual void rand(float*  data, std::size_t i0, std::size_t i1) = 0;
    virtual void randn(double* data, std::size_t i0, std::size_t i1) = 0;
    virtual void randn(float*  data, std::size_t i0, std::size_t i1) = 0;

    virtual void seed(std::size_t s) = 0;
    virtual ~randstream_();
  };

  class mt19937stream_ : public randstream_
  {
    public:
    virtual void seed(std::size_t s);
    virtual void rand(double* data, std::size_t i0, std::size_t i1);
    virtual void rand(float*  data, std::size_t i0, std::size_t i1);
    virtual void randn(double* data, std::size_t i0, std::size_t i1);
    virtual void randn(float*  data, std::size_t i0, std::size_t i1);

    virtual ~mt19937stream_();

    private:
    boost::random::mt19937 generator_;
  };

  class lagged_fibonacci2281stream_ : public randstream_
  {
    public:
    virtual void seed(std::size_t s);
    virtual void rand(double* data, std::size_t i0, std::size_t i1);
    virtual void rand(float*  data, std::size_t i0, std::size_t i1);
    virtual void randn(double* data, std::size_t i0, std::size_t i1);
    virtual void randn(float*  data, std::size_t i0, std::size_t i1);

    virtual ~lagged_fibonacci2281stream_();

    private:
    boost::random::lagged_fibonacci2281 generator_;
  };

  nt2::randstream_* mt19937stream();
  nt2::randstream_* lagged_fibonacci2281stream();

  extern nt2::randstream_* current_randstream;

  NT2_CORE_UTILITY_DECL void randstream(const char* choice);
  NT2_CORE_UTILITY_DECL void randstream(const char* choice, int s);
}

#endif


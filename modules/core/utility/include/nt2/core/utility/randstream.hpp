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

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/lagged_fibonacci.hpp>
#include <boost/random/uniform_real_distribution.hpp>

//==============================================================================
// TODO: Split this into .cpp later
//==============================================================================
namespace nt2
{
  class randstream_
  {
    public:
    virtual void rand(double* data, std::size_t i0, std::size_t i1) = 0;
    virtual void rand(float*  data, std::size_t i0, std::size_t i1) = 0;
    virtual void seed(std::size_t s) = 0;
    virtual ~randstream_() {}
  };

  class mt19937stream_ : public randstream_
  {
    public:
    virtual void seed(std::size_t s) { generator_.seed(s); }

    virtual void rand(double* data, std::size_t i0, std::size_t i1)
    {
      boost::random::uniform_real_distribution<double> dist;
      for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
    }

    virtual void rand(float*  data, std::size_t i0, std::size_t i1)
    {
      boost::random::uniform_real_distribution<float> dist;
      for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
    }

    virtual ~mt19937stream_() {}

    private:
    boost::random::mt19937 generator_;
  };

  class lagged_fibonacci2281stream_ : public randstream_
  {
    public:

    virtual void seed(std::size_t s) { generator_.seed(s); }

    virtual void rand(double* data, std::size_t i0, std::size_t i1)
    {
      boost::random::uniform_real_distribution<double> dist;
      for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
    }

    virtual void rand(float*  data, std::size_t i0, std::size_t i1)
    {
      boost::random::uniform_real_distribution<float> dist;
      for(std::size_t i=i0;i<i1;++i) data[i] = dist(generator_);
    }

    virtual ~lagged_fibonacci2281stream_() {}

    private:
    boost::random::lagged_fibonacci2281 generator_;
  };

  nt2::randstream_* mt19937stream()
  {
    static nt2::mt19937stream_ instance;
    return &instance;
  }

  nt2::randstream_* lagged_fibonacci2281stream()
  {
    static nt2::lagged_fibonacci2281stream_ instance;
    return &instance;
  }

  nt2::randstream_* current_randstream = mt19937stream();

  void randstream(const char* choice)
  {
    if(strcmp(choice,"mt19937ar") == 0)
    {
      current_randstream = mt19937stream();
    }
    else if(strcmp(choice,"mlfg6331_64") == 0)
    {
      current_randstream = lagged_fibonacci2281stream();
    }
  }

  void randstream(const char* choice, int s)
  {
    randstream(choice);
    current_randstream->seed(s);
  }
}

#endif


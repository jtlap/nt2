//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_MT19937STREAM_HPP_INCLUDED
#define NT2_CORE_UTILITY_MT19937STREAM_HPP_INCLUDED

#include <nt2/core/utility/config.hpp>
#include <nt2/core/utility/randstream.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace nt2
{
  class mt19937stream_ : public randstream_
  {
    public:
    virtual void rand (double* data, std::size_t i0, std::size_t i1);
    virtual void rand (float*  data, std::size_t i0, std::size_t i1);
    virtual void randn(double* data, std::size_t i0, std::size_t i1);
    virtual void randn(float*  data, std::size_t i0, std::size_t i1);
    virtual void seed (std::size_t s);

    virtual ~mt19937stream_();

    private:
    boost::random::mt19937 generator_;
  };

  nt2::randstream_* mt19937stream();
}

#endif


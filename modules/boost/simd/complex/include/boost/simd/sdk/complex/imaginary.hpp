//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_COMPLEX_IMAGINARY_HPP_INCLUDED
#define BOOST_SIMD_SDK_COMPLEX_IMAGINARY_HPP_INCLUDED

#include <boost/simd/sdk/complex/details/imaginary/meta.hpp>
#include <boost/simd/sdk/complex/details/imaginary/native.hpp>

namespace boost { namespace simd
{
  template<class T>
  struct imaginary
  {
    typedef T type;
    T value;
    
    imaginary() {}
    explicit imaginary(T const& value_) : value(value_)
    {
    }
    
    T&       operator()()       { return value; }
    T const& operator()() const { return value; }
  };
} }

#endif

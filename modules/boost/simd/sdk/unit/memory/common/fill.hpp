//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef FILL_HPP_INCLUDED
#define FILL_HPP_INCLUDED

#include <boost/simd/sdk/simd/logical.hpp>

template<typename Type> struct fill
{
  inline void operator()(Type& v, std::size_t i, int m = 0) const
  {
    v = Type(1+i+m);
  }

  template<typename SOARef>
  inline void operator()(SOARef v, std::size_t i, int m = 0) const
  {
    v = Type(1+i+m);
  }
};

template<typename Type> struct fill< boost::simd::logical<Type> >
{
  inline void operator()(boost::simd::logical<Type>& v, std::size_t i, int m = 0) const
  {
    v = boost::simd::logical<Type>((i+m)%2);
  }

  template<typename SOARef>
  inline void operator()(SOARef v, std::size_t i, int m = 0) const
  {
    v = boost::simd::logical<Type>((i+m)%2);
  }
};

#endif

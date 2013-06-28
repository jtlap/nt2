//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef SIMD_FILL_HPP_INCLUDED
#define SIMD_FILL_HPP_INCLUDED

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include "../common/fill.hpp"

template<typename Type, typename X> struct fill< boost::simd::native<Type,X> >
{
  void operator()(boost::simd::native<Type,X>& v, std::size_t n, int m = 0) const
  {
    std::size_t sz = boost::simd::native<Type,X>::static_size;
    for(std::size_t i=0;i<sz;++i) fill<Type>()(v[i],n*sz+i+m);
  }
};

template<typename Type, std::size_t N> struct fill< boost::simd::pack<Type,N> >
{
  void operator()(boost::simd::pack<Type,N>& v, std::size_t n, int m = 0) const
  {
    for(std::size_t i=0;i<N;++i) fill<Type>()(v[i],n*N+i+m);
  }
};

#endif

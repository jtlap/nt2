//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_AS_ARITHMETIC_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_AS_ARITHMETIC_HPP_INCLUDED
#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>

namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

namespace boost { namespace simd { namespace meta
{
  template<class T> struct as_arithmetic                  { typedef T type; };
  template<class T> struct as_arithmetic< logical<T> >    { typedef T type; };

  template<class T, class X> 
  struct  as_arithmetic< native<T,X> >  
  {
    typedef native<typename as_arithmetic<T>::type,X> type;
  };

  template<class T, std::size_t Cardinal>
  struct  as_arithmetic< pack<T,Cardinal> >
  {
    typedef pack<typename as_arithmetic<T>::type,Cardinal> type;
  };
} } }

#endif

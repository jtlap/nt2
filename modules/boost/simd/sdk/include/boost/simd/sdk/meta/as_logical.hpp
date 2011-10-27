//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_AS_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_AS_LOGICAL_HPP_INCLUDED

#include <boost/simd/sdk/simd/logical.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T> struct as_logical               { typedef logical<T> type; };
  template<class T> struct as_logical< logical<T> > { typedef logical<T> type; };
  
  template<class T, class X> 
  struct  as_logical< native<T,X> >  
  {
    typedef native<typename as_logical<T>::type,X> type;
  };
} } }

#endif

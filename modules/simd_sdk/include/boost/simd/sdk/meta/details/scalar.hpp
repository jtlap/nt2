//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_DETAILS_SCALAR_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_DETAILS_SCALAR_HPP_INCLUDED

#include <boost/simd/sdk/meta/details/generic.hpp>

namespace boost { namespace simd {  namespace meta
{
  template<class T> struct scalar_ : scalar_< typename T::parent >
  {
    typedef scalar_< typename T::parent > parent;
    typedef T                             base;
  };

  template<class T>
  struct  scalar_< unspecified_<T> >
        : generic_< typename property_of<T>::type >
  {
    typedef generic_< typename property_of<T>::type > parent;
    typedef unspecified_<T>                           base;
  };
} } }

#endif

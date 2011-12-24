//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_COMPLEX_DETAILS_IMAGINARY_META_HPP_INCLUDED
#define BOOST_SIMD_SDK_COMPLEX_DETAILS_IMAGINARY_META_HPP_INCLUDED

#include <boost/simd/sdk/complex/meta/real_of.hpp>
#include <boost/simd/sdk/complex/hierarchy.hpp>
#include <boost/dispatch/meta/property_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace simd
{
  template<class T>
  struct imaginary;
} }

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct real_of< imaginary<T> >
  {
    typedef T type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Origin>
  struct property_of< simd::imaginary<T>, Origin >
  {
    typedef imaginary_< typename property_of<T, Origin>::type > type;
  };
  
  template<class T, class Origin>
  struct hierarchy_of< simd::imaginary<T>, Origin >
  {
    typedef scalar_< imaginary_< typename property_of<T, Origin>::type > > type;
  };
} } }

namespace boost
{
  template<class T>
  struct is_floating_point< simd::imaginary<T> > : is_floating_point<T>
  {
  };
}

#endif

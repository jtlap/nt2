//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_COMPLEX_META_AS_IMAGINARY_HPP_INCLUDED
#define BOOST_SIMD_SDK_COMPLEX_META_AS_IMAGINARY_HPP_INCLUDED

#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/mpl/apply.hpp>

namespace std
{
  template<class T>
  struct complex;
}

namespace boost { namespace simd
{
  template<class T>
  struct imaginary;
} }

namespace boost { namespace simd { namespace details
{
  template<class T, class F>
  struct as_imaginary
   : mpl::apply1<F, imaginary<T> >
  {
  };
  
  template<class T, class F>
  struct as_imaginary< std::complex<T>, F >
   : mpl::apply1<F, imaginary<T> >
  {
  };
  
  template<class T, class F>
  struct as_imaginary< imaginary<T>, F >
   : mpl::apply1<F, imaginary<T> >
  {
  };
} } }

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct as_imaginary
    : details::as_imaginary< typename dispatch::meta::
                             primitive_of<T>::type
                           , typename dispatch::meta::
                             factory_of<T>::type
                           >
  {
  };
} } }

#endif

/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_FUSION_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_FUSION_HPP_INCLUDED

#include <boost/fusion/adapted/boost_array.hpp>

namespace boost { namespace fusion {
  ////////////////////////////////////////////////////////////////////////////
  // Fusion tag overload - native::vector works like boost::array
  // so we reuse all Fusion adapter from boost::array
  ////////////////////////////////////////////////////////////////////////////
  namespace traits
  {
    template<class Scalar, class Extension>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
    struct tag_of<nt2::simd::native<Scalar,Extension>, void >
#else
    struct tag_of<nt2::simd::native<Scalar, Extension> >
#endif
    { typedef boost_array_tag type; };
  }
} }

#endif

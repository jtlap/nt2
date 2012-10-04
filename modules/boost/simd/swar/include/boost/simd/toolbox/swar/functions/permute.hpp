//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_PERMUTE_HPP_INCLUDED

/*!
  @file
**/

#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag permute_ of functor permute
     *        in namespace boost::simd::tag for toolbox boost.simd.swar
    **/
    struct permute_ : ext::unspecified_<permute_> { typedef ext::unspecified_<permute_> parent; };
  }

  template<class T,class A0>
  BOOST_FORCEINLINE
  typename  boost::dispatch::meta
          ::call<tag::permute_( A0 const&, boost::dispatch::meta::as_<T>)>::type
  permute(A0 const& a0)
  {
    typename boost::dispatch::make_functor<tag::permute_, A0>::type callee;
    return callee(a0,boost::dispatch::meta::as_<T>());
  }
} }

#endif



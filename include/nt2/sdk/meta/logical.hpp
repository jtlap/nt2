/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_LOGICAL_HPP_INCLUDED
#define NT2_SDK_META_LOGICAL_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// logical<T>::type is bool if T is anything but SIMD type in which case it is the SIMD type itself
// The rationale is to provide an easy way to write common code for SIMD and scalar in various
// situations of selection or test.
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/is_scalar.hpp>

namespace nt2
{
  namespace details
  {
    template<class T,class C> struct logical_impl  { typedef T type; };
    template<class T >        struct logical_impl < T,boost::mpl::true_ > { typedef bool type; }; 
  }
  namespace meta
  {
    template<class T>
    struct  logical
      : details::logical_impl < typename strip<T>::type
                              , typename meta::is_scalar<T>::type
                              > {};
  }
}

#endif

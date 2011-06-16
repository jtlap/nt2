/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_CATEGORY_HPP_INCLUDED
#define NT2_SDK_SIMD_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Basic category registration
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// SIMD types tag
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class T,class X> struct simd_ : simd_< typename T::parent, X >
  {
    typedef simd_< typename T::parent, X > parent;
    typedef typename T::origin            origin;
  };

  template<class T,class X>
  struct  simd_< unspecified_<T>, X >
        : generic_< typename unspecified_<T>::origin >
  {
    typedef generic_< typename unspecified_<T>::origin >  parent;
    typedef typename unspecified_<T>::origin              origin;
  };
} }

#endif

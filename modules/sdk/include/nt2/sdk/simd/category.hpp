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
namespace nt2
{
  namespace tag { template<class T,class X> struct simd_ {}; }

  //////////////////////////////////////////////////////////////////////////////
  // simd types hierarchy
  //////////////////////////////////////////////////////////////////////////////
  namespace meta
  {
    template<class T,class X> struct simd_ : simd_<typename T::parent,X>
    {
      typedef simd_<typename T::parent,X>     parent;
      typedef tag::simd_<typename T::type,X>  type;
    };

    template<class T,class X> struct simd_< unknown_<T>,X > : unknown_<T> {};
  }
}

#endif

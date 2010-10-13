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
#include <nt2/sdk/meta/category.hpp>
#include <nt2/sdk/meta/category_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Use this macro to put a type in the SIMD familly
////////////////////////////////////////////////////////////////////////////////
#define NT2_CATEGORY_SIMD_FAMILY 2

////////////////////////////////////////////////////////////////////////////////
// Family tags for call/validate writings
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag
{
  struct simd_ {};
} }

////////////////////////////////////////////////////////////////////////////////
// simd_ metafunction for building a SIMD category
// Why using simd(T,X) instead of a tempalte tempalte parameters ?
// Mostly because it's easier to extend and seems faster to compile
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class T, class X,std::size_t R>
  struct  simd_
        : nt2::tag::category<simd_<T,X,R>,NT2_CATEGORY_SIMD_FAMILY,R>
  {
    typedef nt2::tag::simd_ tag(T,X);
  };
} }

#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_CONSTANT_SPLAT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_SPLAT_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/constant/category.hpp>

////////////////////////////////////////////////////////////////////////////////
// Tag for splat functor
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace tag { struct splat_ {}; } }

////////////////////////////////////////////////////////////////////////////////
// splat function
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  template<class T, class A0> inline
  typename meta::enable_call<tag::splat_(A0, meta::as_<T>)>::type
  splat(A0 const& a0)
  {
    functor<tag::splat_> callee;
    return callee(a0, meta::as_<T>() );
  }
}

#include <nt2/sdk/constant/details/splat.hpp>

#endif

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

#include <nt2/include/functor.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>

namespace nt2 { namespace functors
{
  template<class T> struct splat_ {};

  //////////////////////////////////////////////////////////////////////////////
  // We only splat scalar values into T
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Category, class Info>
  struct  validate< splat_<T>, Category, Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct  result<This(A0)> : meta::is_scalar<A0> {};
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // splat category is given by T
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Info, class A0>
  struct categorize<functors::splat_<T>,Info,A0>
  {
    typedef typename meta::category_of<T>::type::tag type;
  };
} }

namespace nt2
{
  template<class T, class A0> inline
  typename meta::enable_call<functors::splat_<T>(A0)>::type
  splat(A0 const& a0)
  {
    NT2_FUNCTION_BODY(functors::splat_<T>,1)
  }
}

#include <nt2/sdk/constant/details/splat.hpp>

#endif

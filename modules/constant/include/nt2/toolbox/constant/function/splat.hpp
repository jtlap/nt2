//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 
#ifndef NT2_TOOLBOX_CONSTANT_FUNCTION_SPLAT_HPP_INCLUDED
#define NT2_TOOLBOX_CONSTANT_FUNCTION_SPLAT_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/toolbox/constant/specific/constant.hpp>
#include <nt2/toolbox/constant/include.hpp>

namespace nt2
{
  namespace tag
  {
    struct splat_  {};
  }
  
  template<class T, class A0> inline
  typename meta::enable_call<tag::splat_(A0, meta::as_<T>)>::type
  splat(A0 const& a0)
  {
    typename make_functor<tag::splat_, A0>::type callee;
    return callee(a0, meta::as_<T>() );
  }
}

#include <nt2/toolbox/constant/function/scalar/splat.hpp>
#include NT2_CONSTANT_INCLUDE(splat.hpp)

#endif

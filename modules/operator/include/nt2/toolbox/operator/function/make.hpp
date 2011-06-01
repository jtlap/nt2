//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_MAKE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_MAKE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/toolbox/operator/include.hpp>
#include <nt2/sdk/meta/as.hpp>

namespace nt2
{
  namespace tag
  {
    struct make_ {};
  }
    
    #define M0(n)                                                                          \
    template<class T, BOOST_PP_ENUM_PARAMS(n, class A)> inline                             \
    typename meta::enable_call<tag::make_(BOOST_PP_ENUM_PARAMS(n, A), meta::as_<T>)>::type \
    make(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                                      \
    {                                                                                      \
      typename make_functor<tag::make_, T>::type callee;                                   \
      return callee(BOOST_PP_ENUM_PARAMS(n, a), meta::as_<T>());                           \
    }
    
  M0( 1)
  M0( 2)
  M0( 4)
  M0( 8)
  M0(16)
  M0(32)
#if NT2_MAX_ARITY >= 64
  M0(64)
#endif

  #undef M0
}

#include <nt2/toolbox/operator/function/scalar/make.hpp>
#include <nt2/toolbox/operator/function/simd/all/make.hpp>

#endif

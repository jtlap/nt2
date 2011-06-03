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
  
  #define NT2_PP_REPEAT_POWER_OF_2(m, data)                                                \
  m( 1,  1, data)                                                                          \
  m( 2,  2, data)                                                                          \
  m( 4,  4, data)                                                                          \
  m( 8,  8, data)                                                                          \
  m(16, 16, data)                                                                          \
  m(32, 32, data)                                                                          \
  m(64, 64, data)
    
  /* We specialize functor directly due to arity limitations, and we only dispatch on the target.
   * We also avoid having to dispatch return type deduction, and we cast all arguments to the scalar
   * matching the target. */
  template<class Site>
  struct functor<tag::make_, Site>
  {
    template<class Sig>
    struct result;
    
    #define M1(z,n,t) static_cast<typename meta::scalar_of<typename Target::type>::type>(a##n)
    
    #define M0(z,n,t)                                                                      \
    template<class This, BOOST_PP_ENUM_PARAMS(n, class A), class Target>                   \
    struct result<This(BOOST_PP_ENUM_PARAMS(n, A), Target)>                                \
      : meta::strip<Target>::type                                                          \
    {                                                                                      \
    };                                                                                     \
                                                                                           \
    template<BOOST_PP_ENUM_PARAMS(n, class A), class Target>                               \
    typename Target::type                                                                  \
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a), Target const&) const           \
    {                                                                                      \
      typename meta::dispatch_call<tag::make_(Target), Site>::type callee;                 \
      return callee(BOOST_PP_ENUM(n, M1, ~));                                              \
    }
    
    NT2_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
    #undef M1
  };
    
  #define M0(z,n,t)                                                                        \
  template<class T, BOOST_PP_ENUM_PARAMS(n, class A)> inline                               \
  T make(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                                      \
  {                                                                                        \
    typename make_functor<tag::make_, T>::type callee;                                     \
    return callee(BOOST_PP_ENUM_PARAMS(n, a), meta::as_<T>());                             \
  }

  NT2_PP_REPEAT_POWER_OF_2(M0, ~)
  #undef M0
}

#include <nt2/toolbox/operator/function/scalar/make.hpp>
#include <nt2/toolbox/operator/function/simd/all/make.hpp>

#endif

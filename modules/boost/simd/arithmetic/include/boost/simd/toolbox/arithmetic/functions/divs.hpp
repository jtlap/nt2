//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_DIVS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd {
  namespace tag
  {
    struct divs_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, divs, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, saturated_div, 2) 
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divs_, rdivide, 2)
  
  template<class A0, class A1>
  BOOST_DISPATCH_FORCE_INLINE
  typename dispatch::meta::call<tag::divs_(A0, A1)>::type
  ldivide(A0 const& a0, A1 const& a1)
  {
    return dispatch::make_functor<tag::divs_, A0>::type()(a1, a0);
  }
  
  template<class A0, class A1>
  BOOST_DISPATCH_FORCE_INLINE
  typename dispatch::meta::call<tag::divs_(A0, A1)>::type
  ldiv(A0 const& a0, A1 const& a1)
  {
    return dispatch::make_functor<tag::divs_, A0>::type()(a1, a0);
  }
  
} }

#endif

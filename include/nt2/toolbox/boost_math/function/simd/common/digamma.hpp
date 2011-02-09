//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

namespace nt2 { namespace functors
{
  /////////////////////////////////////////////////////////////////////////////
  // Compute digamma(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Dummy>
  struct call<boost_math::digamma_,
              tag::simd_<tag::arithmetic_,Extension),Dummy>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    // see documentation http://nt2.lri.fr/extension/custom_function.html
    // for writing the functor implementation code 
    // with or without type dispatching

  };
} }

      
#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_AT_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_AT_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/is_scalar.hpp>

namespace nt2 { namespace functors
{
  template<class Extension, class Info>
  struct validate<at_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;

    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
         : boost::mpl::and_ < meta::is_scalar<typename meta::strip<A1>::type>
                            , meta::is_integral<typename meta::strip<A1>::type>
                            > {};
  };

  template<class Extension, class Info>
  struct call<at_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0, A1)>
          : meta::scalar_of<typename meta::strip<A0>::type>
    {};

    NT2_FUNCTOR_CALL(2) { return a0[a1]; }
  };
} }

#endif

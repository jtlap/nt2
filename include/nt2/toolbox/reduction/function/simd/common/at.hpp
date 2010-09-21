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
#include <nt2/include/functions/put_first.hpp>
#include <nt2/include/functions/first.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<at_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)> : boost::mpl::true_ {};

    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
         : boost::mpl::and_ < meta::is_scalar<A1>
                            , meta::is_integral<A1>
                            > {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute at(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<at_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::scalar_of<A0> {};
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> : meta::scalar_of<A0> {};

    NT2_FUNCTOR_CALL(2) { return first(put_first(a0, a1)); }
    NT2_FUNCTOR_CALL(1) { return a0[Idx];    }

  };
} }

      
#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SUCCESSOR_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>

#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/bitinteger.hpp>
#include <nt2/include/functions/bitfloating.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/sdk/constant/real.hpp>

namespace nt2 { namespace functors
{

  template<class Info>
  struct validate<successor_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : boost::mpl::true_ {};

    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::is_integral<A1> {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute successor(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<successor_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0> {};
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1)
    {
      return is_inf(a0) || is_nan(a0) ? Nan<A0>()  : bitfloating(oneplus(bitinteger(a0)));
    }
    NT2_FUNCTOR_CALL(2)
    {
       return is_inf(a0) || is_nan(a0) ? Nan<A0>()  : bitfloating(bitinteger(a0)+a1);
    }

  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<successor_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0> {};
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(1){ return oneplus(a0); }
    NT2_FUNCTOR_CALL(2){ return a0+a1;       }
  };

} }

#endif
/// Revised by jt the 15/11/2010
/// No restore -- hand modifications

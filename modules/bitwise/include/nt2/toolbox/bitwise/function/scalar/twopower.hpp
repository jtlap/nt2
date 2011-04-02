//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_TWOPOWER_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_TWOPOWER_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/sdk/meta/strip.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::twopower_, tag::cpu_,
                          (A0),
                          (arithmetic_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::twopower_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return (is_ltz(a0))?Zero<A0>():(One<A0>()<<a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::twopower_, tag::cpu_,
                          (A0),
                          (unsigned_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::twopower_(tag::unsigned_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :std::tr1::result_of<meta::arithmetic(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
       return One<A0>()<<a0;
    }
  };
} }

#endif
// modified by jt the 26/12/2010
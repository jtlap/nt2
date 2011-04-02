//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FLOOR_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_FLOOR_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/selsub.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/sdk/constant/digits.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::floor_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::floor_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::floor_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::floor_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      const A0 d0 = nt2::round2even(a0);
      return selsub(gt(d0,a0),d0,One<A0>());
    }
  };
} }

#endif
// modified by jt the 26/12/2010

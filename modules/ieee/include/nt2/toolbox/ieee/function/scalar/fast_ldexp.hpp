//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_FAST_LDEXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_FAST_LDEXP_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_ldexp_, tag::cpu_,
                            (A0)(A1),
                            (integer_<A0>)(integer_<A1>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_ldexp_(tag::integer_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
       return (a1>=0)?(a0<<a1):(a0>>a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_ldexp_, tag::cpu_,
                            (A0)(A1),
                            (real_<A0>)(integer_<A1>)
                           )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::fast_ldexp_(tag::real_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0, A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename meta::as_integer<A0, unsigned>::type int_type;

//       static int_type const nmb = Nbmantissabits<A0>();
//       static int_type const n1  = ((2*(Maxexponent<A0>()-1)+3) << nmb);

      // clear exponent in x
      A0 const x(b_andnot(a0, Ldexpmask<A0>()));
      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<A0>(), a0);
      e += int_type(a1) << Nbmantissabits<A0>();
      return b_or(x, e);
    }
  };
} }

#endif
// modified by jt the 26/12/2010
// manualy modified by jt the 29/12/2010

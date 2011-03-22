//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#include <nt2/sdk/meta/from_bits.hpp>
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/digits.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitfloating_, tag::cpu_,
                             (A0),
                             (arithmetic_<A0>)
                            )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitfloating_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> { typedef typename meta::as_real<A0>::type type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type           rtype;
      typedef typename meta::from_bits<rtype>::type       type;
      typedef typename meta::from_bits<rtype>::bits_type  bits_type;
      type that = { a0 >= Zero<A0>()
                  ? bits_type(a0)
                  : bits_type((1LL << (8*sizeof(A0)-1))-a0)
                  };
      // TOVERIFY PERFS
      return that.value;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::bitfloating_, tag::cpu_,
                             (A0),
                             (unsigned_<A0>)
                            )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::bitfloating_(tag::unsigned_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> { typedef typename meta::as_real<A0>::type type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type rtype;
      typename meta::from_bits<rtype, signed>::type  that =  {a0};
      return that.value;
    }
  };
} }

#endif
// modified by jt the 26/12/2010

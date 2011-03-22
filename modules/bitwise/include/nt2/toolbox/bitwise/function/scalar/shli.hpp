//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SHLI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SHLI_HPP_INCLUDED
#include <nt2/sdk/meta/as_bits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                      (A0)(A1),
                      (arithmetic_<A0>)(arithmetic_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
       struct result<This(A0,A1)> : meta::strip <A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_bits<A0>::type type;
      type that = {a0};
      that.bits <<= a1;
      return that.value;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shli_, tag::cpu_,
                      (A0)(A1),
                      (real_<A0>)(real_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shli_(tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
       struct result<This(A0,A1)> : meta::strip <A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_bits<A0>::type type;
      type that = {a0};
      that.bits <<= a1;
      return that.value;
    }
  };
} }

#endif
// modified by jt the 26/12/2010
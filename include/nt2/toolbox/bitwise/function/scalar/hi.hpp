//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_HI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_HI_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/downgrade.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::hi_, tag::cpu_,
                    (A0),
                    (arithmetic_<A0>)
                   )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::hi_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      meta::downgrade<typename meta::as_integer<A0,unsigned>::type >{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type type;
      BOOST_STATIC_CONSTANT(type, shift = sizeof(type)*4);
      BOOST_STATIC_CONSTANT(type, pattern = type(type(-1)<<shift));

      return b_and(pattern, a0) >> shift;
    }

  };
} }

#endif
// modified by jt the 26/12/2010

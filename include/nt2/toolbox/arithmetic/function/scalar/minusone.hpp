//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MINUSONE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MINUSONE_HPP_INCLUDED
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/constant/digits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::minusone_, tag::cpu_,
                          (A0),
                          (fundamental_<A0>)
                         )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::minusone_(tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> {
      typedef typename meta::strip<A0>::type sA0; 
      typedef typename std::tr1::result_of<meta::arithmetic(sA0)>::type tmp;
      typedef typename meta::as_signed<tmp>::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::strip<A0>::type sA0; 
      return a0-One<sA0>();
    }

  };
} }

#endif
// modified by jt the 26/12/2010

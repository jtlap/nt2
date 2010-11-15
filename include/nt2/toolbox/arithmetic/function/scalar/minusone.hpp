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


namespace nt2 { namespace functors
{

  //  no special validate for minusone

  /////////////////////////////////////////////////////////////////////////////
  // Compute minusone(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<minusone_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> {
      typedef typename boost::result_of<meta::arithmetic(A0)>::type tmp;
      typedef typename meta::as_signed<tmp>::type type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return a0-One<A0>();
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010

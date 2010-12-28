//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_SPLATTED_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_SPLATTED_FIRST_HPP_INCLUDED


namespace nt2 { namespace functors
{

  //  no special validate for splatted_first

  /////////////////////////////////////////////////////////////////////////////
  // Compute splatted_first(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<splatted_first_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> {typedef A0 type; };

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010

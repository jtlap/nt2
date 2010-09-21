//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_CUMSUM_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_CUMSUM_HPP_INCLUDED


namespace nt2 { namespace functors
{

  //  no special validate for cumsum

  /////////////////////////////////////////////////////////////////////////////
  // Compute cumsum(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<cumsum_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1) { return a0; }
  };
} }


      
#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_PUT_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SCALAR_PUT_FIRST_HPP_INCLUDED
#include <nt2/sdk/details/ignore_unused.hpp>


namespace nt2 { namespace functors
{

  //  no special validate for put_first

  /////////////////////////////////////////////////////////////////////////////
  // Compute put_first(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<put_first_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0, A1)> {typedef A0 type; };  

    NT2_FUNCTOR_CALL(2)
    {
      details::ignore_unused(a1); 
      return a0; 
    }
  };
} }


      
#endif

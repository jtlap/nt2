//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_BOOLEAN_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_BOOLEAN_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>


namespace nt2 { namespace functors
{

  //  no special validate for boolean

  /////////////////////////////////////////////////////////////////////////////
  // Compute boolean(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<boolean_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>: boost::result_of<meta::arithmetic(A0)>{}; 

    NT2_FUNCTOR_CALL(1)
    {
      return a0?One<A0>():Zero<A0>(); 
    }
  };
} }


      
#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEGATION_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_NEGATION_HPP_INCLUDED

#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_gez.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for negation

  /////////////////////////////////////////////////////////////////////////////
  // Compute negation(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<negation_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A1,
      (2, (unsigned_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,   unsigned_)
    {
        return is_nez(a1)*a0;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      return is_nez(a1)*(is_gez(a1)?a0:-a0);
    }
  };
} }


      
#endif

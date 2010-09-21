//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMAINDER_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REMAINDER_HPP_INCLUDED
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/negate.hpp>
#include <nt2/include/functions/idivfix.hpp>


namespace nt2 { namespace functors
{

  //  no special validate for remainder

  /////////////////////////////////////////////////////////////////////////////
  // Compute remainder(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<remainder_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      type a = nt2::abs(a0);
      type b = nt2::abs(a1);
      return b ? nt2::negate(a-nt2::idivfix(a, b)*b, a) : a;
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type type;
      type a = nt2::abs(a0);
      type b = nt2::abs(a1);
      return b ? nt2::negate(a-nt2::idivfix(a, b)*b, a) : a;
    }
  };
} }


      
#endif

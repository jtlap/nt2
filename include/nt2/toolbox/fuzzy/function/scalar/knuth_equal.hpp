//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_KNUTH_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_KNUTH_EQUAL_HPP_INCLUDED
#include <nt2/sdk/details/ignore_unused.hpp>

#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/exponent.hpp>
#include <nt2/include/functions/maxnummag.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for knuth_equal

  /////////////////////////////////////////////////////////////////////////////
  // Compute knuth_equal(const A0& a0, const A1& a1, const A2& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<knuth_equal_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)>{typedef bool type; }; 

    NT2_FUNCTOR_CALL_DISPATCH(
      3,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(3,       real_)
    {
      return abs(a0-a1) <= fast_ldexp(a2, exponent(maxnummag(a0, a1)));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(3, arithmetic_)
    {
      details::ignore_unused(a2); 
      return iseq(a0, a1);
    }
  };
} }


      
#endif

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_UNORD_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_UNORD_HPP_INCLUDED
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
#include <nt2/include/functions/is_nan.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for is_unord

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_unord(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<is_unord_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      A0,
      (2, (real_,arithmetic_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(2,       real_)
    {
       return is_nan(a0) || is_nan(a1);
    }
    NT2_FUNCTOR_CALL_EVAL_IF(2, arithmetic_)
    {
      details::ignore_unused(a0);
      details::ignore_unused(a1);
      return False<A0>();
    }
  };
} }


      
#endif

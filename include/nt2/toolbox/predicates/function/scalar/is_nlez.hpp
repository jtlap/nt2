//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NLEZ_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NLEZ_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/is_nan.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for is_nlez

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_nlez(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<is_nlez_,tag::scalar_(tag::arithmetic_),Info>
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , A0
                              , (2, (real_,arithmetic_))
                              )

    NT2_FUNCTOR_CALL_EVAL_IF(1,       real_)
    {
       return ((a0 >  Zero<A0>()) || isnan(a0));
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1, arithmetic_)
    {
      return (a0 >  Zero<A0>());
    }
  };
} }


      
#endif

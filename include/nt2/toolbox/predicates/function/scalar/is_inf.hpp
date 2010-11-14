//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_INF_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_INF_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

#include <nt2/include/functions/abs.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for is_inf

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_inf(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_inf_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
       return nt2::abs(a0) == Inf<A0>();
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_inf_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0); 
      return false; 
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010

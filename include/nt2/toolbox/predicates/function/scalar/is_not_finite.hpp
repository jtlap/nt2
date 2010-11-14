//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NOT_FINITE_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_NOT_FINITE_HPP_INCLUDED
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

#include <nt2/include/functions/is_nan.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for is_not_finite

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_not_finite(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_not_finite_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
      {
	return nt2::is_nan(a0-a0);
      }

  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_not_finite_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      details::ignore_unused(a0);
      return False<A0>();
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010

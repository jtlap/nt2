//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_POSITIVE_HPP_INCLUDED
#define NT2_TOOLBOX_PREDICATES_FUNCTION_SCALAR_IS_POSITIVE_HPP_INCLUDED
#include <nt2/sdk/meta/as_bits.hpp>
#include <nt2/sdk/constant/digits.hpp>


namespace nt2 { namespace functors
{

  //  no special validate for is_positive

  /////////////////////////////////////////////////////////////////////////////
  // Compute is_positive(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_positive_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, signed>::type t0 = {a0};
      return t0.bits >= 0;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<is_positive_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return a0 >= Zero<A0>();
    }
  };

} }

#endif
/// Revised by jt the 13/11/2010

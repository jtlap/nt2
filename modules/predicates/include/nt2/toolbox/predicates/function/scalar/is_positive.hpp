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



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_positive_, tag::cpu_,
                             (A0),
                             (arithmetic_<A0>)
                            )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_positive_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return a0 >= Zero<A0>();
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::is_positive_, tag::cpu_,
                             (A0),
                             (real_<A0>)
                            )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::is_positive_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    typedef bool result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, signed>::type t0 = {a0};
      return t0.bits >= 0;
    }
  };
} }

#endif
// modified by jt the 26/12/2010
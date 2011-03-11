//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
#include <nt2/toolbox/predicates/include/is_invalid.hpp>
#include <cmath>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::atan2_, tag::cpu_,
                       (A0)(A1),
                       (arithmetic_<A0>)(arithmetic_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::atan2_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename NT2_RETURN_TYPE(2)::type rtype;
	if (is_invalid(a0) && is_invalid(a1)) return Nan<rtype>(); 
        return std::atan2(rtype(a0),rtype(a1));
    }

  };
} }

#endif
// modified by jt the 26/12/2010

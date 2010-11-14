//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_TANH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_TANH_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/expm1.hpp>

#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/sign.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for tanh

  /////////////////////////////////////////////////////////////////////////////
  // Compute tanh(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<tanh_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      type x = nt2::abs(a0);
      if (x > 1.836840028483855e+01) return nt2::sign(a0); 
      type tmp1=nt2::expm1(-(x+x));
      type tmp2=-tmp1/(Two<type>()+tmp1);
      return b_xor(tmp2, bitofsign(a0));
    }

  };
} }

#endif
/// Revised by jt the 13/11/2010

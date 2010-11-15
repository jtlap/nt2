//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_LDEXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_LDEXP_HPP_INCLUDED
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for ldexp

  /////////////////////////////////////////////////////////////////////////////
  // Compute ldexp(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ldexp_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename NT2_CALL_RETURN_TYPE(2)::type result_type;
      typedef typename meta::as_integer<result_type, unsigned>::type          int_type;

      //  static int_type const nmb = Nbmantissabits<result_type>();
      //      static int_type const n1  = ((2*(Maxexponent<result_type>()-1)+3) << nmb);

      // clear exponent in x
      result_type const x(b_andnot(a0, Ldexpmask<A0>()));

      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<result_type>(), a0);
      e += int_type(a1) << Nbmantissabits<result_type>(); //nmb;
      if (is_nez(a0)&&is_finite(a0)) return  b_or(x, e);
      return a0; 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ldexp_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
        return (a1>0)?(a0<<a1):(a0>>a1); 
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010

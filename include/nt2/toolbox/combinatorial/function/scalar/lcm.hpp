//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_LCM_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_LCM_HPP_INCLUDED

#include <nt2/include/functions/rdivide.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/gcd.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/is_inf.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for lcm

  /////////////////////////////////////////////////////////////////////////////
  // Compute lcm(const A0& a0, const A1& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<lcm_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      if (!a0&&!a1)   return Zero<rtype>();
      bool i0 = is_inf(a0);
      bool i1 = is_inf(a1);
      if(i0&&i1) return Nan<rtype>(); 
      if (i0) return nt2::abs(a1);
      if (i1) return nt2::abs(a0);
      return nt2::abs(trunc(a0)*rdiv(a1,gcd(a0,a1)));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<lcm_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : 
      boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype; 
      if (!a0&&!a1)   return Zero<rtype>(); 
      return nt2::abs(a0*rdivide(a1,gcd(a0,a1)));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010

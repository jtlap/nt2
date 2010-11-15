//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_POSMIN_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_COMMON_POSMIN_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>


namespace nt2 { namespace functors
{
  //  no special validate for posmin

  /////////////////////////////////////////////////////////////////////////////
  // Compute posmin(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<posmin_,tag::simd_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
     template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type stype;
      typedef typename meta::as_integer<stype, signed>::type type; 
    };
    

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type type; 
      int p = 0;
      type m = a0[0]; 
      for(size_t i=1; i < meta::cardinal_of<A0>::value; i++)// TODO UNROLL
	{
	  if (m > a0[i]){m = a0[i]; p = i; }
	}
      return p; 
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010

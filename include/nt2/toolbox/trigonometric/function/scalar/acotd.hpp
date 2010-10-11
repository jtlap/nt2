//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ACOTD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ACOTD_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/atand.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for acotd

  /////////////////////////////////////////////////////////////////////////////
  // Compute acotd(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct call<acotd_,tag::scalar_(tag::arithmetic_),Info>
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : boost::result_of<meta::floating(A0)>{}; 

      NT2_FUNCTOR_CALL(1) {
	const bool iiinf = isinf(a0); 
	if((a0 < 0) && iiinf) return A0(180);
	if(iiinf) return Zero<A0>(); 
	return Ninety<A0>()-atand(a0);
      }

     };
} }


      
#endif

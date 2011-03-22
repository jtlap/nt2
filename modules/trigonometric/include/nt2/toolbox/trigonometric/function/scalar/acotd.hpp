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
#include <nt2/include/functions/tofloat.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::acotd_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::acotd_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
      template<class Sig> struct result;
      template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};

      NT2_FUNCTOR_CALL(1)
	{
	  A0 s = bitofsign(a0);
	  if(!a0)  return b_or(Ninety<A0>(), s);
	  if(is_inf(a0)) return b_or(Zero<A0>(), s);
	  return b_or(Ninety<A0>()-atand(abs(a0)), s);
	}

  };
} }

NT2_REGISTER_DISPATCH(tag::acotd_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::acotd_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : std::tr1::result_of<meta::floating(A0)>{};
      
    NT2_FUNCTOR_CALL(1)
      {
	typedef typename NT2_RETURN_TYPE(1)::type type; 
	if(!a0)  return Zero<A0>();
	return nt2::acotd(type(a0));
      }
      
  };  
} }

#endif
// modified by jt the 26/12/2010

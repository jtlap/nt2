//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_SIGNGAM_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_SIGNGAM_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/floor.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for signgam

  /////////////////////////////////////////////////////////////////////////////
  // Compute signgam(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<signgam_,tag::scalar_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
	typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
        if (is_lez(a0))
	  {
	    if (is_flint(a0))
	      return Nan<type>();
	    else
	      return One<type>()-is_odd(floor(a0))*Two<A0>(); 
	  }
	else
	  return One<type>();
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010

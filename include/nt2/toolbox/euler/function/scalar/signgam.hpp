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
#include <nt2/include/functions/is_inf.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::signgam_, tag::cpu_,
                         (A0),
                         (fundamental_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::signgam_(tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      bool isinfa0 =  is_inf<A0>(a0); 
      if (is_lez(a0))
	{
	  if (is_flint(a0)||isinfa0)
	    return Nan<type>();
	  else
	    return One<type>()-is_odd(floor(a0))*Two<A0>();
	}
      else if (is_nan(a0)) return a0; 
      return One<type>();
    }

  };
} }

#endif
// modified by jt the 26/12/2010

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_GAMMALN_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_GAMMALN_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <boost/math/tr1.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gammaln_, tag::cpu_,
                         (A0),
                         (fundamental_<A0>)
                        )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gammaln_(tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (a0 < Zero<A0>()) return Nan<A0>();
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return boost::math::tr1::lgamma(type(a0));
    }

  };
} }

#endif
// modified by jt the 26/12/2010
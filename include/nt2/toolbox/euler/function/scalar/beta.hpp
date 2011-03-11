//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_BETA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_BETA_HPP_INCLUDED
#include <boost/math/special_functions.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::beta_, tag::cpu_,
                      (A0)(A1),
                      (fundamental_<A0>)(fundamental_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::beta_(tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return boost::math::beta(type(a0), type(a1));
    }

  };
} }

#endif
// modified by jt the 26/12/2010
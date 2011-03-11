//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SELSUB_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_SELSUB_HPP_INCLUDED



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::selsub_, tag::cpu_,
                        (A0)(A1)(A2),
                        (fundamental_<A0>)(fundamental_<A1>)(fundamental_<A2>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::selsub_(tag::fundamental_,tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)> :
      std::tr1::result_of<meta::arithmetic(A1,A2)>{};

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      if (a0) return type(a1)-type(a2); else return type(a1);
    }

  };
} }

#endif
// modified by jt the 26/12/2010
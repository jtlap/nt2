//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_ASECH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_ASECH_HPP_INCLUDED

#include <nt2/include/functions/acosh.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asech_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asech_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      if (is_eqz(a0)) return Inf<type>();
      if (a0 ==  One<A0>()) return Zero<type>();
      return Nan<type>(); 
    }

  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asech_, tag::cpu_,
                       (A0),
                       (real_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asech_(tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      typedef typename NT2_RETURN_TYPE(1)::type type;
      if (a0 > One<A0>() || a0 < Zero<A0>()) return Nan<A0>();
      if (a0 == Zero<A0>()) return Inf<A0>();
      return acosh(rec(a0)); 
//      type t = minusone(rec(a0));
//       if (t < 16*Sqrteps<A0>()){
// 	return sqrt(Two<A0>()*t)*(oneplus(t/12+3*sqr(t)/160)); //1 + t /12 + 3 * t*t / 160
//       }
//       return nt2::log1p(t+nt2::sqrt((t+t)+sqr(t)));
    }
  }; 
} }
  
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asech_, tag::cpu_,
                       (A0),
                       (float_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asech_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      typedef typename NT2_RETURN_TYPE(1)::type type;
      if (a0 > One<A0>() || a0 < Zero<A0>()) return Nan<A0>();
      if (a0 == Zero<A0>()) return Inf<A0>();
      A0 tmp =  oneminus(a0);
      if (tmp <= 0.01f) {
	A0 f = 1.0f+tmp*(0.41666665982f+tmp*(0.26875436672f+tmp*(0.19711170102f+tmp* 0.16913685372f))); 
	return f*nt2::sqrt(2.0f*tmp);
      }
      return acosh(rec(a0)); 

    }
  }; 
} }
#endif
// modified by jt the 26/12/2010

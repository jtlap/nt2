//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_ANP_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_ANP_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/is_ngez.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/exp.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::anp_, tag::cpu_,
                     (A0)(A1),
                     (fundamental_<A0>)(fundamental_<A1>)
                    )

<<<<<<< HEAD
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<anp_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename boost::result_of<meta::floating(A0, A1)>::type type;
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      if (is_ngez(a0)||is_ngez(a1)||is_nan(a1)||is_nan(a0)) return Nan<type>();
      if (is_inf(a0)) return Inf<rtype>(); 
      if (lt(a0,a1)||!a0) return Zero<rtype>();
      const type n = oneplus(round2even(a0));
      const type p = round2even(a1);
      return (rtype)round2even(exp(gammaln(n)-gammaln(n-p)));
    }
  }; 
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<anp_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
=======
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::anp_(tag::fundamental_,tag::fundamental_),
              tag::cpu_, Dummy> : callable
>>>>>>> functor2
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename boost::result_of<meta::floating(A0, A1)>::type type;
<<<<<<< HEAD
      typedef typename NT2_CALL_RETURN_TYPE(2)::type rtype;
      if (is_ngez(a0)||is_ngez(a1)) return Nan<type>();
      if (lt(a0,a1)||!a0) return Zero<type>();
=======
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      if (is_ngez(a0)||is_ngez(a1)) return (rtype)Nan<type>();
      if (lt(a0,a1)) return (rtype)Zero<type>();
>>>>>>> functor2
      const type n = oneplus(round2even(a0));
      const type p = round2even(a1);
      return (rtype)round2even(exp(gammaln(n)-gammaln(n-p)));
    }

  };
} }

#endif
// modified by jt the 26/12/2010

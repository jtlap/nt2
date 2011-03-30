//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_CNP_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_CNP_HPP_INCLUDED
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/is_ngez.hpp>
#include <nt2/include/functions/is_inf.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cnp_, tag::cpu_,
                     (A0)(A1),
                     (arithmetic_<A0>)(arithmetic_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cnp_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename std::tr1::result_of<meta::floating(A0, A1)>::type type;
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      if (is_inf(a1)) return (rtype)Nan<type>(); 
      if (is_ngez(a0)||is_ngez(a1)) return (rtype)Nan<type>();
      if (a0 < a1) return (rtype) Zero<type>();
      if (eq(a0,a1)) return (rtype)One<type>(); 
      const type n = oneplus(round2even(a0));
      const type p = oneplus(round2even(a1));
      return (rtype)round2even(exp(gammaln(n)-gammaln(p)-gammaln(oneplus(n-p))));
    }
  };
} }

#endif
// modified by jt the 26/12/2010

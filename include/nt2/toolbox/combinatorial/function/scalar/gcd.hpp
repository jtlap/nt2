//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_GCD_HPP_INCLUDED
#define NT2_TOOLBOX_COMBINATORIAL_FUNCTION_SCALAR_GCD_HPP_INCLUDED

#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/is_not_finite.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/rem.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gcd_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(integer_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gcd_(tag::integer_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type a(a0);
      type b(a1);
      while (is_nez(b)) {
	const type  r = a % b;
	a = b;
	b = r;
      }
      return a;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::gcd_, tag::cpu_,
                     (A0)(A1),
                     (real_<A0>)(real_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::gcd_(tag::real_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::arithmetic(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type a(a0);
      type b(a1);
      if (!b) return a;
      if (is_not_finite(a+b)||!is_flint(a)||!is_flint(b)) return Nan <type>();
      while (b) {
      type  r  = rem(a, b);
      a = b;
      b = r;
      }
      return a;
    }
  };
} }

#endif
// modified by jt the 26/12/2010

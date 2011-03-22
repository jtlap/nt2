//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_LEGENDRE_HPP_INCLUDED
#define NT2_TOOLBOX_POLYNOMIALS_FUNCTION_SIMD_COMMON_LEGENDRE_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/abs.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::legendre_, tag::cpu_,
                          (A0)(A1)(X),
                          ((integer_<A0>))
                           ((simd_<arithmetic_<A1>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::legendre_(tag::integer_,
                             tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return legendre(a0, tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::legendre_, tag::cpu_,
                          (A0)(A1)(X),
                          ((integer_<A0>))
                           ((simd_<real_<A1>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::legendre_(tag::integer_,
                             tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      A1 p0 = One<A1>();
      if(a0 == 0) return p0;
      A1 p1 = a1;
      A1 p;
      A1 vc =  One<A1>();
      uint32_t c = 1;
      while(c < a0)
            {
              p = p0;
              p0 = p1;
        A1 vcp1 =  oneplus(vc);
        p1 = ((vc + vcp1)*a1 * p0 - vc * p) /vcp1;
              vc = vcp1;
              ++c;
            }
      return b_or(p1, gt(abs(a1), One<A1>()));
    }
  };
} }

#endif
// modified by jt the 05/01/2011

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_DIGAMMA_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/selsub.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/tanpi.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/toolbox/polynomials/function/scalar/impl/poleval.hpp>
#include <nt2/toolbox/euler/function/scalar/constants.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::digamma_, tag::cpu_,
                          (A0)(X),
                          ((simd_<arithmetic_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::digamma_(tag::simd_(tag::arithmetic_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::digamma(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::digamma_, tag::cpu_,
                          (A0)(X),
                          ((simd_<real_<A0>,X>))
                         );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::digamma_(tag::simd_(tag::real_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      //
      // This handles reflection of negative arguments, and all our
      // error handling, then forwards to the T-specific approximation.
      //
      A0 result = Zero<A0>();
      A0 x = a0;
      A0 test = is_lez(a0);
      uint32_t nb, nb1;
      if( (nb = nbtrue(test)) > 0)
      {
        x = sel(test, oneminus(a0), a0);
        A0 remainder = x - floor(x);
          remainder =  selsub(gt(remainder,Half<A0>()),remainder,One<A0>());
        result = b_and(b_andnot(Pi<A0>()/tanpi(remainder),is_eqz(remainder)), test);
        // we are ready to increment result that was
        // Pi<A0>()/tanpi(remainder) if a0 < 0  and remainder != 0
        // Nan<A0>                   if a0 < 0  and remainder == 0
        // 0                         in any other cases
      }
      A0 r1, r2;
      test = gt(x, Digammalargelim<A0>());
      if(nb = nbtrue(test))
      { // If we're above the lower-limit for the asymptotic expansion then use it:
        r1 = b_and(digamma_imp_large(x, sA0()), test)+result;
        if (nb >= meta::cardinal_of<A0>::value) return r1;
      }
      // If x > 2 reduce to the interval [1,2]:
      A0 cond;
      while(any(cond = gt(x, Two<A0>())))
      {
        x      -= b_and(One<A0>(), cond);
        result += b_and(rec(x), cond);
      }
      // If x < 1 use shift to > 1:
      if(any(cond = lt(x, One<A0>())))
      {
        result = sel(cond, -rec(x), result);
        x      += b_and(One<A0>(), cond);
      }
      r2 = b_andnot(digamma_imp_1_2(x, sA0()), test)+result;
      if (nb == 0) return r2;
      return sel(test, r1, r2);
    }
  };
} }

#endif
// modified by jt the 05/01/2011
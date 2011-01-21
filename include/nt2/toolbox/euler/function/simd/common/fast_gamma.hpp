//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_FAST_GAMMA_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SIMD_COMMON_FAST_GAMMA_HPP_INCLUDED
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/bitwise_ornot.hpp>
#include <nt2/include/functions/nbtrue.hpp>
#include <nt2/toolbox/euler/function/scalar/constants.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_gamma_, tag::cpu_,
                             (A0)(X),
                             ((simd_<arithmetic_<A0>,X>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_gamma_(tag::simd_(tag::arithmetic_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return fast_gamma(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::fast_gamma_, tag::cpu_,
                             (A0)(X),
                             ((simd_<real_<A0>,X>))
                            );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::fast_gamma_(tag::simd_(tag::real_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 sgngam = One<A0>(); //positive
      A0 r =  Nan<A0>(), r2=  Nan<A0>();
      A0 q =  abs(a0);
      A0 x = a0;
      A0 test0 = gt(q, Fastgammalargelim<A0>());
      int32_t nb = 0;
      if (nb = nbtrue(test0) > 0)
      {
        A0 negative = is_ltz(a0);
        A0 s =  stirling(q);
        int32_t nb1 = 0;
        A0 r1;
        if (nb1 = nbtrue(negative) > 0)
          {
            A0 p = floor(q);
            A0 test1 = is_equal(p, q); //must return Nan<A0>();
            sgngam = negif(is_even(p), sgngam);
            A0 z = q - p;
            A0 test2 = lt(z, Half<A0>() );
            p = seladd(test2, p, One<A0>());
            z = sel(test2, q - p, z);
            z = q*sinpi(z);
            A0 test3 = is_eqz(z);
            z =  nt2::abs(z);
            r1 = sgngam*Pi<A0>()/(z * s );
            if (nb1 >= meta::cardinal_of<A0>::value) return r1;
          }
        r2 = sel(negative, r1, s);
      }
      if (nb >= meta::cardinal_of<A0>::value) return r2;
      //      std::cout << "r2 "<< r2 << std::endl;
      A0 y2 =  other(test0, x); // computation result if ~test0
      r = sel(test0, r2, y2);
      //     r &= b_or(y2, test0);
      return r|is_nan(a0);

    }
  };
} }

#endif
// modified by jt the 05/01/2011
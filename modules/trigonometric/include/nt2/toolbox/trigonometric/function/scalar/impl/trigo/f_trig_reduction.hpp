//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/sdk/meta/logical.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/trigo/f_pio2_reducing.hpp>
#include <nt2/include/functions/inrad.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/is_nlt.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template< class A0
              , class unit_tag
              , class precision_tag
              , class base_A0 = typename meta::scalar_of<A0>::type
              >
      struct trig_reduction;

      // This class exposes the public static members:
      // replacement_needed:    to provide a condition to go back standard (for example libc) computations is needed
      // replacement_available: true if such a replacement exists
      // cos_replacement
      // sin_replacement
      // tan_replacement
      // cot_replacement
      // sincos_replacement:    placeholders for call to possibly existing standard replacement functions
      // reduce:                to provide range reduction
      //
      // unit_tag allows to choose statically the scaling  among radian_tag, pi_tag, degree_tag
      // meaning that the cosa function will (for example) define respectively
      // x-->cos(x)          (radian_tag),
      // x-->cos(p*x)        (pi_tag)
      // x-->cos((pi/180)*x) (degree_tag)
      //
      // precision_tag allows to choose policies among accuracy and speed
      // are defined:
      //   accu_tag
      //   fast_tag
      // fast_tag doe not mean that functions are returning stupid values
      //    but that some ulps can be lost.
      // accu_tag does not mean that functions are ever slow,  but that they are
      //    generally a little slower than with fast_tag and much slower in peculiar
      //    cases (especially very big values of input)
      //
      // for each trigonometric function, xxx
      //   accu_xxx_s
      //   fast_xxx_
      //   xxx_
      // NT2 functors are provided.
      // By default xxx_ calls are with fast_tag,  but this can be modified by a pair compiler options
      //   NT2_IS_ACCU
      //   NT2_IS_FAST

      // trigonometric reduction strategies in the [-pi/4, pi/4] range.
      // these reductions are used in the accurate and fast
      // trigonometric functions with different policies

      template<class A0>
      struct trig_reduction < A0, radian_tag, trig_tag, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::logical<A0>::type               logic;

        static inline logic replacement_needed(const A0& a0)
        {
          return gt(a0,single_constant<A0,0x43490fdb>());
        }

        static inline logic replacement_available()       { return True<A0>(); }
        static inline logic isalreadyreduced(const A0&a0) { return le(a0,Pio_4<A0>()); }

        static inline logic ismedium (const A0&a0)  { return le(a0,single_constant<A0,0x43490fdb>()); }
        static inline logic issmall  (const A0&a0)  { return le(a0,single_constant<A0,0x427b53d1>()); }

        static inline A0 cos_replacement(const A0& a0)
        {
          return fallback<FALLBACK_TAG>::cos(a0);
        }

        static inline A0 sin_replacement(const A0& a0)
        {
          return fallback<FALLBACK_TAG>::sin(a0);
        }

        static inline A0 tan_replacement(const A0& a0)
        {
          return fallback<FALLBACK_TAG>::tan(a0);
        }

        static inline A0 cot_replacement(const A0& a0)
        {
          return rec(std::tan(a0));
        }

        static inline void sincos_replacement(const A0& a0, A0&s, A0&c)
        {
          //::sincosf(a0, &s, &c);
        }
        static inline logic cot_invalid(const A0& x) { return is_invalid(x); }
        static inline logic tan_invalid(const A0& x) { return is_invalid(x); }

        static inline int_type reduce(const A0& x, A0& xr, A0& xc)
        {
          // x is always positive here
          if (all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
          {
            return pio2_reducing<A0>::noreduction(x, xr, xc);
          }
          else if (all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
          {
            return pio2_reducing<A0>::cephes_reduction(x, xr, xc);
          }
          else if (all(ismedium(x))) // all of x are in [0, 2^7*pi/2],  fdlibm medium way
          {
            return pio2_reducing<A0>::fdlibm_medium_reduction(x, xr, xc);
          }
          else  // all of x are in [0, inf],  standard big way
          {
            // This is never taken
            return pio2_reducing<A0>::fdlibm_big_reduction(x, xr, xc);
          }
        }
      };


      template<class A0>
      struct trig_reduction<A0,degree_tag,trig_tag,float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::logical<A0>::type            logic;

        static inline logic replacement_needed(const A0& a0)
        {
          return is_nlt(a0,single_constant<A0,0x4b7fffff>()); //16777215.0f
        }

        static inline logic replacement_available() { return True<A0>(); }

        static inline A0 cos_replacement(const A0& a0)
        {
          return std::cos(inrad(a0));
        }

        static inline A0 sin_replacement(const A0& a0)
        {
          return std::sin(inrad(a0));
        }

        static inline A0 tan_replacement(const A0& a0)
        {
          return std::tan(inrad(a0));
        }

        static inline A0 cot_replacement(const A0& a0)
        {
          return rec(std::tan(inrad(a0)));
        }

        static inline void sincos_replacement(const A0& a0, A0&s, A0&c)
        {
          //::sincosf(inrad(a0), &s, &c);
        }
        static inline logic cot_invalid(const A0& x) { return is_invalid(x)|is_flint(x/C_180<A0>()); }
        static inline logic tan_invalid(const A0& x) { return is_invalid(x)|is_flint((x-Ninety<A0>())/C_180<A0>()); }

        static inline int_type reduce(const A0& x, A0& xr, A0& xc)
        {
          A0 xi = round2even(x*single_constant<A0,0x3c360b61>()); //  1.111111111111111e-02f
          A0 x2 = x - xi * Ninety<A0>();//90.0f
          xr =  x2*single_constant<A0,0x3c8efa35>(); //0.0174532925199432957692f
          xc = Zero<A0>();
          return toint(xi);
        }
      };

       template < class A0> struct trig_reduction < A0, pi_tag, trig_tag, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::logical<A0>::type            logic;

        ////////////////////////////////////////////////////////////////////////
        // floats x greater than 2^23 are integers so
        // sin(pi*x) and tan(pi*x) are thus 0
        // cos(pi*x) is thus (-1)^x
        // cotpi*x) is thus Nan
        ////////////////////////////////////////////////////////////////////////
        static inline logic replacement_needed(const A0& a0)
        {
          return b_andnot(gt(a0,single_constant<A0,0x4b000000>()), is_invalid(a0)); //2^23
          // TODO: isn't it a registered constant ^
        }

        static inline logic replacement_available() { return True<A0>(); }

        static inline A0 cos_replacement(const A0& a0)
        {
          return One<A0>()-(is_odd(a0)<<1); // TODO << 1 is maybe bad in SSEx
        }

        static inline A0 sin_replacement(const A0& )  { return Zero<A0>(); }
        static inline A0 tan_replacement(const A0& )  { return Zero<A0>(); }
        static inline A0 cot_replacement(const A0& )  { return Nan<A0>();  }

        static inline void sincos_replacement(const A0& a0, A0&s, A0&c)
        {
          c = cos_replacement(a0);
          s = sin_replacement(a0);
        }
        static inline logic cot_invalid(const A0& x) { return is_invalid(x)|is_flint(x); }
        static inline logic tan_invalid(const A0& x) { return is_invalid(x); }

        static inline int_type reduce(const A0& x,  A0& xr, A0&xc)
        {
          A0 xi = round2even(x*Two<A0>());
          A0 x2 = x - xi * Half<A0>();
          xr = x2*Pi<A0>();
          xc = Zero<A0>();
          return toint(xi);
        }
      };
    }
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_trig_reduction.hpp
// /////////////////////////////////////////////////////////////////////////////

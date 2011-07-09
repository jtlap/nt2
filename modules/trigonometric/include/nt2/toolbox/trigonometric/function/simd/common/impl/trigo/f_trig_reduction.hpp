//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_IMPL_TRIGO_F_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/sdk/meta/logical.hpp>
#include <nt2/include/functions/rem_pio2_medium.hpp>
#include <nt2/include/functions/rem_pio2_cephes.hpp>
#include <nt2/include/functions/rem_pio2_straight.hpp>
#include <nt2/include/functions/rem_pio2.hpp>
#include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo/f_pio2_reducing.hpp>
#include <nt2/toolbox/arithmetic/include/toint.hpp>
#include <nt2/include/functions/inrad.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/is_not_less.hpp>
#include <nt2/include/functions/is_not_greater.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_flint.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
//#include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo/d_pio2_reducing.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
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

      // trigonometric reduction strategies to the [-pi/4, pi/4] range.
      // these reductions are used in the accurate and fast
      // trigonometric functions with different policies

      template<class A0, class mode>
      struct trig_reduction < A0, radian_tag, trig_tag, tag::simd_type, mode, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::logical<A0>::type               logic;
        static inline logic isalreadyreduced(const A0&a0) { return is_ngt(a0, Pio_4<A0>()); }

	//	static inline logic isnotsobig(const A0&a0) { return le(a0,single_constant<A0,0x49490fe0>()); } 
        static inline logic ismedium (const A0&a0)  { return le(a0,single_constant<A0,0x43490fdb>()); }
        static inline logic issmall  (const A0&a0)  { return le(a0,single_constant<A0,0x427b53d1>()); }
        static inline logic islessthanpi_2  (const A0&a0)  { return le(a0,Pio_2<A0>()); }
        static inline bool conversion_allowed(){
	  typedef typename meta::upgrade<A0>::type uA0;
	  return boost::mpl::not_<boost::is_same<A0,uA0> >::value; 
	}

         static inline logic cot_invalid(const A0& x) { return False<A0>()/*is_invalid(x)*/; }
         static inline logic tan_invalid(const A0& x) { return False<A0>()/*is_invalid(x)*/; }

        static inline int_type reduce(const A0& x, A0& xr, A0& xc){ return inner_reduce(x, xr, xc, mode()); }
      private:
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const big&)
        {
          // x is always positive here
          if (all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
	    {
	      xr = x;
	      xc = Zero<A0>();
	      return Zero<int_type>(); 
	    }
          else if (all(islessthanpi_2(x))) // all of x are in [pi/4, pi/2],  straight algorithm is sufficient for 1 ulp
	      return rem_pio2_straight(x, xr, xc);
          else if (all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
	      return rem_pio2_cephes(x, xr, xc);
          else if (all(ismedium(x))) // all of x are in [0, 2^7*pi/2],  fdlibm medium way
	      return rem_pio2_medium(x, xr, xc);
	  else if (conversion_allowed())//if (all(isnotsobig(x))) // all of x are in [0, 2^18*pi],  conversion to double is used to reduce
	    {
	      typedef typename meta::upgrade<A0>::type uA0;
	      typedef typename meta::upgrade<int_type>::type uint_type; 
	      typedef trig_reduction< uA0, radian_tag, trig_tag, tag::simd_type, mode, double> aux_reduction; 
	      uA0 ux1, ux2, uxr1, uxr2, uxc1, uxc2;
	      nt2::split(x, ux1, ux2);
	      uint_type n1 = aux_reduction::reduce(ux1, uxr1, uxc1);
	      uint_type n2 = aux_reduction::reduce(ux2, uxr2, uxc2);
	      xr = nt2::group(uxr1, uxr2);
	      nt2::split(xr, ux1, ux2);
	      xc = nt2::group((uxr1-ux1)+uxc1, (uxr2-ux2)+uxc2);
	      return nt2::group(n1, n2); 
	    }
	  else  // all of x are in [0, inf],  standard big way
 	      return rem_pio2(x, xr, xc);
        }

	static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const medium&)
        {
          // x is always positive here
          if (all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
	    {
	      xr = x;
	      xc = Zero<A0>();
	      return Zero<int_type>(); 
	    }
          else if (all(islessthanpi_2(x))) // all of x are in [pi/4, pi/2],  straight algorithm is sufficient for 1 ulp
	      return rem_pio2_straight(x, xr, xc);
          else if (all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
	      return rem_pio2_cephes(x, xr, xc);
          else // correct only if all of x are in [0, 2^7*pi/2],  fdlibm medium way
	      return rem_pio2_medium(x, xr, xc);
        }
	static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const small&)
        {
          // x is always positive here
          if (all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
	    {
	      xr = x;
	      xc = Zero<A0>();
	      return Zero<int_type>(); 
	    }
          else if (all(islessthanpi_2(x))) // all of x are in [pi/4, pi/2],  straight algorithm is sufficient for 1 ulp
	      return rem_pio2_straight(x, xr, xc);
          else //  correct only if all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
	      return rem_pio2_cephes(x, xr, xc);
         }

      };


      template<class A0>
      struct trig_reduction<A0,degree_tag,trig_tag, tag::simd_type,big, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::logical<A0>::type            logic;

//         static inline logic replacement_needed(const A0& a0)
//         {
//           return is_nlt(a0,single_constant<A0,0x4b7fffff>()); //16777215.0f
//         }

//         static inline logic replacement_available() { return True<A0>(); }

//         static inline A0 cos_replacement(const A0& a0)
//         {
//           return std::cos(inrad(a0));
//         }

//         static inline A0 sin_replacement(const A0& a0)
//         {
//           return std::sin(inrad(a0));
//         }

//         static inline A0 tan_replacement(const A0& a0)
//         {
//           return std::tan(inrad(a0));
//         }

//         static inline A0 cot_replacement(const A0& a0)
//         {
//           return rec(std::tan(inrad(a0)));
//         }

//         static inline void sincos_replacement(const A0& a0, A0&s, A0&c)
//         {
//           //::sincosf(inrad(a0), &s, &c);
//         }
        static inline logic cot_invalid(const A0& x) { return /*is_invalid(x)|*/(is_nez(x)&is_flint(x/C_180<A0>())); }
        static inline logic tan_invalid(const A0& x) { return /*is_invalid(x)|*/is_flint((x-Ninety<A0>())/C_180<A0>()); }

        static inline int_type reduce(const A0& x, A0& xr, A0& xc)
        {
          A0 xi = round2even(x*single_constant<A0,0x3c360b61>()); //  1.111111111111111e-02f
          A0 x2 = x - xi * Ninety<A0>();//90.0f    
          xr =  x2*single_constant<A0,0x3c8efa35>(); //0.0174532925199432957692f
          xc = Zero<A0>();
          return toint(xi);
        }
      };

       template < class A0>
       struct trig_reduction < A0, pi_tag, trig_tag, tag::simd_type, big, float>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::logical<A0>::type            logic;

        ////////////////////////////////////////////////////////////////////////
        // floats x greater than 2^23 are integers so
        // sin(pi*x) and tan(pi*x) are thus 0
        // cos(pi*x) is thus (-1)^x
        // cotpi*x) is thus Nan
        ////////////////////////////////////////////////////////////////////////
//         static inline logic replacement_needed(const A0& a0)
//         {
//           return b_andnot(gt(a0,single_constant<A0,0x4b000000>()), is_invalid(a0)); //2^23
//           // TODO: isn't it a registered constant ^
//         }

//         static inline logic replacement_available() { return True<A0>(); }

//         static inline A0 cos_replacement(const A0& a0)
//         {
//           return One<A0>()-(is_odd(a0)<<1); // TODO << 1 is maybe bad in SSEx
//         }

//         static inline A0 sin_replacement(const A0& )  { return Zero<A0>(); }
//         static inline A0 tan_replacement(const A0& )  { return Zero<A0>(); }
//         static inline A0 cot_replacement(const A0& )  { return Nan<A0>();  }

//         static inline void sincos_replacement(const A0& a0, A0&s, A0&c)
//         {
//           c = cos_replacement(a0);
//           s = sin_replacement(a0);
//         }
        static inline logic cot_invalid(const A0& x) { return /*is_invalid(x)|*/(is_nez(x)&is_flint(x)); }
        static inline logic tan_invalid(const A0& x) { return /*is_invalid(x)|*/is_flint(x-Half<A0>()) ; }

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

/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/functions/simd/is_invalid.hpp>
#include <nt2/include/functions/simd/inrad.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/constants/false.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      // trigonometric reduction strategies in the [-pi/4, pi/4] range.
      // these reductions are used in the accurate and fast
      // trigonometric functions with different policies
      template < class A0, class mode>
      struct trig_reduction < A0, radian_tag, tag::simd_type, mode, double>
      {
      typedef typename meta::as_logical<A0>::type bA0;
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::scalar_of<int_type>::type   sint_type;

        static inline bA0 isalreadyreduced(const A0&a0){ return le(a0, Pio_4<A0>()); }
        static inline bA0 ismedium (const A0&a0){return le(a0,double_constant<A0,0x412921fb54442d18ll>()); }
        static inline bA0 issmall  (const A0&a0){return le(a0,double_constant<A0,0x404f6a7a2955385ell>()); }
        static inline bA0 islessthanpi_2  (const A0&a0)  { return le(a0,Pio_2<A0>()); }
        static inline bA0 cot_invalid(const A0& ) { return False<bA0>(); }
        static inline bA0 tan_invalid(const A0& ) { return False<bA0>(); }
        static inline int_type reduce(const A0& x, A0& xr, A0& xc){ return inner_reduce(x, xr, xc, mode()); }
      private:
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const big_&)
        {
          const A0 x = x_n;
          // x is always positive here
          if (nt2::all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>();
            }
          else if (nt2::all(islessthanpi_2(x))) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
            return rem_pio2_straight(x, xr, xc);
          else if (nt2::all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
            return rem_pio2_cephes(x, xr, xc);
          else if (nt2::all(ismedium(x))) // all of x are is in [0, 2^18*pi],  fdlibm medium_ way
            return rem_pio2_medium(x, xr, xc);
          else  // all of x are in [0, inf],  standard big_ way
            return rem_pio2(x, xr, xc);
        }

        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const medium_&)
        {
          const A0 x = x_n;
          // x is always positive here
          if (nt2::all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>();
            }
          else if (nt2::all(islessthanpi_2(x))) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
            return rem_pio2_straight(x, xr, xc);
          else if (nt2::all(issmall(x))) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
            return rem_pio2_cephes(x, xr, xc);
          else  // correct only if all of x are is in [0, 2^18*pi],  fdlibm medium_ way
            return rem_pio2_medium(x, xr, xc);
        }

        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const small_&)
        {
          const A0 x = x_n;
          // x is always positive here
          if (nt2::all(isalreadyreduced(x))) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>();
            }
          else if (nt2::all(islessthanpi_2(x))) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
            {
              return rem_pio2_straight(x, xr, xc);
            }
          else  // correct only if all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
            {
              return rem_pio2_cephes(x, xr, xc);
            }
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const direct_small_&)
        {
          const A0 x = x_n;
          return rem_pio2_cephes(x, xr, xc);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const direct_medium_&)
        {
          const A0 x = x_n;
          return rem_pio2_medium(x, xr, xc);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const direct_big_&)
        {
          const A0 x = x_n;
          return rem_pio2_big(x, xr, xc);
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const clipped_pio4_&)
        {
          const A0 x = x_n;
          xr = sel(isalreadyreduced(nt2::abs(x)), x, Nan<A0>());
          xc = Zero<A0>();
          return Zero<int_type>();
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const clipped_small_&)
        {
          const A0 x = x_n;
          xr = sel(issmall(nt2::abs(x)), x, Nan<A0>());
          return inner_reduce(xr, xr, xc, small_());
        }
        static inline int_type inner_reduce(const typename A0::native_type x_n, A0& xr, A0& xc, const clipped_medium_&)
        {
          const A0 x = x_n;
          xr = sel(ismedium(nt2::abs(x)), x, Nan<A0>());
          return inner_reduce(xr, xr, xc, medium_());
        }
      };

      template < class A0>
      struct trig_reduction < A0, degree_tag,  tag::simd_type, big_, double >
      {
       typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::as_integer<A0, signed>::type  int_type;
        typedef typename meta::scalar_of<int_type>::type    sint_type;

        static inline bA0 cot_invalid(const A0& x) { return (logical_and(is_nez(x), is_even(x/_90<A0>()))); }
        static inline bA0 tan_invalid(const A0& x) { return is_odd(x/_90<A0>()); }
        static inline int_type reduce(const typename A0::native_type x_n, A0& xr, A0& xc)
        {
          const A0 x = x_n;
          A0 xi = round(x*double_constant<A0,0x3f86c16c16c16c17ll>());//1.111111111111111e-02 1/90
          A0 x2 = x - xi * _90<A0>();
          xr =  x2*double_constant<A0,0x3f91df46a2529d39ll>();//0.0174532925199432957692
          xc = Zero<A0>();
          return toint(xi);
        }
      };

      template < class A0>
      struct trig_reduction < A0, pi_tag,  tag::simd_type, big_, double>
      {
        typedef typename meta::as_logical<A0>::type bA0;
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::scalar_of<int_type>::type    sint_type;

        static inline bA0 cot_invalid(const A0& x) { return logical_and(is_nez(x), is_flint(x)); }
        static inline bA0 tan_invalid(const A0& x) { return is_flint(x-Half<A0>()); }
        static inline int_type reduce(const typename A0::native_type x_n,  A0& xr, A0&xc)
        {
          const A0 x = x_n;
          A0 xi = round(x*Two<A0>());
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
// End of d_trig_reduction.hpp
// /////////////////////////////////////////////////////////////////////////////

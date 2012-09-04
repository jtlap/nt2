/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/is_invalid.hpp>
#include <nt2/include/functions/simd/inrad.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/pio_2.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      // trigonometric reduction strategies in the [-pi/4, pi/4] range.
      // these reductions are used in the accurate and fast
      // trigonometric functions with different policies
      template < class A0,  class mode>
      struct trig_reduction < A0, radian_tag,  tag::not_simd_type, mode, double>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::scalar_of<int_type>::type   sint_type;

        static inline bool isalreadyreduced(const A0&a0){ return le(a0, Pio_4<A0>()); }
        static inline bool ismedium (const A0&a0){return le(a0,double_constant<A0,0x412921fb54442d18ll>()); }
        static inline bool issmall  (const A0&a0){return le(a0,double_constant<A0,0x404f6a7a2955385ell>()); }
        static inline bool islessthanpi_2  (const A0&a0)  { return le(a0,Pio_2<A0>()); }
        static inline bool cot_invalid(const A0& ) { return false; }
        static inline bool tan_invalid(const A0& ) { return false; }
        static inline int_type reduce(const A0& x, A0& xr, A0& xc){ return inner_reduce(x, xr, xc, mode()); }
      private:
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const nt2::big&)
        {
          // x is always positive here
          if (isalreadyreduced(x)) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>(); 
            }
          else if (islessthanpi_2(x)) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
            return rem_pio2_straight(x, xr, xc);
          else if (issmall(x)) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
            return rem_pio2_cephes(x, xr, xc);
          else if (ismedium(x)) // all of x are is in [0, 2^18*pi],  fdlibm medium way
            return rem_pio2_medium(x, xr, xc);
          else  // all of x are in [0, inf],  standard big way
            return rem_pio2(x, xr, xc);
        }

        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const nt2::medium&)
        {
          // x is always positive here
          if (isalreadyreduced(x)) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>(); 
            }
          else if (islessthanpi_2(x)) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
            return rem_pio2_straight(x, xr, xc);
          else if (issmall(x)) // all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
            return rem_pio2_cephes(x, xr, xc);
          else  // correct only if all of x are is in [0, 2^18*pi],  fdlibm medium way
            return rem_pio2_medium(x, xr, xc);
        }
      
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const nt2::small_&)
        {
          // x is always positive here
          if (isalreadyreduced(x)) // all of x are in [0, pi/4], no reduction
            {
              xr = x;
              xc = Zero<A0>();
              return Zero<int_type>(); 
            }
          else if (islessthanpi_2(x)) // all of x are in [0, pi/2],  straight algorithm is sufficient for 1 ulp
            return rem_pio2_straight(x, xr, xc);
          else  // correct only if all of x are in [0, 20*pi],  cephes algorithm is sufficient for 1 ulp
            return rem_pio2_cephes(x, xr, xc);
        }
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const direct_small&)
        {
          return rem_pio2_cephes(x, xr, xc);
        }
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const direct_medium&)
        {
          return rem_pio2_medium(x, xr, xc);
        }
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const direct_big&)
        {
          return rem_pio2(x, xr, xc);
        }
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const clipped_pio4&)
        {
          xr = select(isalreadyreduced(nt2::abs(x)), x, Nan<A0>());
          xc = Zero<A0>();
          return Zero<int_type>(); 
        }
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const clipped_small&)
        {
          xr = select(issmall(nt2::abs(x)), x, Nan<A0>());
          return inner_reduce(xr, xr, xc, small_()); 
        }
        static inline int_type inner_reduce(const A0& x, A0& xr, A0& xc, const clipped_medium&)
        {
          xr = select(ismedium(nt2::abs(x)), x, Nan<A0>());
          return inner_reduce(xr, xr, xc, medium()); 
        }
      };


      template < class A0>
      struct trig_reduction < A0, degree_tag,  tag::not_simd_type, big, double >
      {
        typedef typename meta::as_integer<A0, signed>::type  int_type;
        typedef typename meta::scalar_of<int_type>::type    sint_type;

        static inline bool cot_invalid(const A0& x) { return (is_nez(x)&is_even(x/_180<A0>())); }
        static inline bool tan_invalid(const A0& x) { return is_flint((x-_90<A0>())/_180<A0>()); }
        static inline int_type reduce(A0 x, A0& xr, A0& xc)
        {
          A0 xi = round2even(x*double_constant<A0,0x3f86c16c16c16c17ll>());//1.111111111111111e-02
          A0 x2 = x - xi * _90<A0>();//90.0f
          xr =  x2*double_constant<A0,0x3f91df46a2529d39ll>();//0.0174532925199432957692
          xc = Zero<A0>();
          return toint(xi);
        }
      };
      
      template < class A0>
      struct trig_reduction < A0, pi_tag,  tag::not_simd_type, big, double>
      {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        typedef typename meta::scalar_of<int_type>::type    sint_type;

        static inline bool cot_invalid(const A0& x) { return (is_nez(x)&is_flint(x)); }
        static inline bool tan_invalid(const A0& x) { return is_flint(x-Half<A0>()); }
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
// End of d_trig_reduction.hpp
// /////////////////////////////////////////////////////////////////////////////

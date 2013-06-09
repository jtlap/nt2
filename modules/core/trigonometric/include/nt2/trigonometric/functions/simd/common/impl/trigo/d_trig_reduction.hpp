//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/simd/rem_pio2_medium.hpp>
#include <nt2/include/functions/simd/rem_pio2_cephes.hpp>
#include <nt2/include/functions/simd/rem_pio2_straight.hpp>
#include <nt2/include/functions/simd/rem_pio2.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/if_else_allbits.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_not_greater.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/_90.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>

namespace nt2 { namespace details { namespace internal
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

    static inline bA0 is_0_pio4_reduced(const A0&a0) { return boost::simd::is_ngt(a0, nt2::Pio_4<A0>()); }
    static inline bA0 is_0_pio2_reduced(const A0&a0) { return boost::simd::is_ngt(a0, nt2::Pio_2<A0>()); }
    static inline bA0 is_0_20pi_reduced(const A0&a0) { return boost::simd::is_ngt(a0, _20_pi<A0>()); }
    static inline bA0 is_0_mpi_reduced (const A0&a0) { return boost::simd::is_ngt(a0, Medium_pi<A0>()); }  //2^18pi
    static inline bA0 cot_invalid(const A0& ) { return nt2::False<bA0>(); }
    static inline bA0 tan_invalid(const A0& ) { return nt2::False<bA0>(); }
    static inline int_type reduce(const A0& x, A0& xr){ return inner_reduce(x, xr); }
  private:
    static inline int_type inner_reduce(const A0 & x_n, A0& xr)
    {
      A0 xx = x_n;
      if (mode::clipped)
      {
        if (mode::range == r_0_pio4)          xx = if_else_nan(is_0_pio4_reduced(xx), xx);
        else if (mode::range == r_0_20pi)     xx = if_else_nan(is_0_20pi_reduced(xx), xx);
        else if (mode::range == r_0_mpi)      xx = if_else_nan(is_0_mpi_reduced(xx),  xx);
      }

      switch (mode::start)
      {
      case  r_0_pio4 :
        if(nt2::all(is_0_pio4_reduced(xx)) || mode::range == r_0_pio4)
        {
          xr = xx; return Zero<int_type>();
        }
      case  r_0_pio2 :
        if(nt2::all(is_0_pio2_reduced(xx)))
        {
          return rem_pio2_straight(xx, xr);
        }
      case  r_0_20pi :
        if(nt2::all(is_0_20pi_reduced(xx)) || mode::range == r_0_20pi)
        {
          return rem_pio2_cephes(xx, xr);
        }
      case  r_0_mpi :
        if(nt2::all(is_0_mpi_reduced(xx)) || mode::range == r_0_mpi)
        {
          return rem_pio2_medium(xx, xr);
        }
      case  r_0_inf :
        return rem_pio2(xx, xr);
      }
    }
  };

  template < class A0>
  struct trig_reduction < A0, degree_tag,  tag::simd_type, big_, double >
  {
    typedef typename meta::as_logical<A0>::type bA0;
    typedef typename meta::as_integer<A0, signed>::type  int_type;
    typedef typename meta::scalar_of<int_type>::type    sint_type;

    static inline bA0 cot_invalid(const A0& x) { return (nt2::logical_and(nt2::is_nez(x), nt2::is_even(x/_90<A0>()))); }
    static inline bA0 tan_invalid(const A0& x) { return nt2::is_odd(x/_90<A0>()); }
    static inline int_type reduce(const typename A0::native_type x_n, A0& xr)
    {
      const A0 x = x_n;
      A0 xi = round2even(x*double_constant<A0,0x3f86c16c16c16c17ll>());//1.111111111111111e-02 1/90
      A0 x2 = x - xi * nt2::_90<A0>();
      xr =  x2*double_constant<A0,0x3f91df46a2529d39ll>();//0.0174532925199432957692
      return nt2::toint(xi);
    }
  };

  template < class A0>
  struct trig_reduction < A0, pi_tag,  tag::simd_type, big_, double>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;
    typedef typename meta::scalar_of<int_type>::type    sint_type;

    static inline bA0 cot_invalid(const A0& x) { return nt2::logical_and(nt2::is_nez(x), nt2::is_flint(x)); }
    static inline bA0 tan_invalid(const A0& x) { return nt2::is_flint(x-nt2::Half<A0>()); }
    static inline int_type reduce(const typename A0::native_type x_n,  A0& xr)
    {
      const A0 x = x_n;
      A0 xi = nt2::round2even(x*nt2::Two<A0>());
      A0 x2 = x - xi * nt2::Half<A0>();
      xr = x2*nt2::Pi<A0>();
      return nt2::toint(xi);
    }
  };
} } }


#endif

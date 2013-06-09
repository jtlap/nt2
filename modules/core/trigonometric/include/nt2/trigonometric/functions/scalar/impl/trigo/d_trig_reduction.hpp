//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_D_TRIG_REDUCTION_HPP_INCLUDED

#include <nt2/include/functions/rem_pio2_medium.hpp>
#include <nt2/include/functions/rem_pio2_cephes.hpp>
#include <nt2/include/functions/rem_pio2_straight.hpp>
#include <nt2/include/functions/rem_pio2.hpp>
#include <nt2/include/functions/is_even.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/inrad.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/is_not_greater.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/_20_pi.hpp>
#include <nt2/include/constants/oneo_90.hpp>
#include <nt2/include/constants/medium_pi.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>

namespace nt2 { namespace details { namespace internal
{
  // trigonometric reduction strategies in the [-pi/4, pi/4] range.
  // these reductions are used in the accurate and fast
  // trigonometric functions with different policies
  template < class A0,  class style, class mode>
  struct trig_reduction < A0, radian_tag, style, mode, double>
  {
    typedef typename meta::as_logical<A0>::type              bA0;
    typedef typename meta::as_integer<A0, signed>::type int_type;

    static inline bA0 is_0_pio4_reduced(const A0&a0) { return boost::simd::is_ngt(a0, nt2::Pio_4<A0>()); }
    static inline bA0 is_0_pio2_reduced(const A0&a0) { return boost::simd::is_ngt(a0, nt2::Pio_2<A0>()); }
    static inline bA0 is_0_20pi_reduced(const A0&a0) { return boost::simd::is_ngt(a0, _20_pi<A0>()); }
    static inline bA0 is_0_mpi_reduced (const A0&a0) { return boost::simd::is_ngt(a0, Medium_pi<A0>()); }  //2^18pi
    static inline bA0 cot_invalid(const A0& ) { return nt2::False<bA0>(); }
    static inline bA0 tan_invalid(const A0& ) { return nt2::False<bA0>(); }
    static inline int_type reduce(const A0& x, A0& xr){ return inner_reduce(x, xr); }
  private:
    static inline int_type inner_reduce(const A0& x, A0& xr)
    {
      A0 xx = x;
      if (mode::clipped)
      {
        if (mode::range == r_0_pio4)          xx = if_else_nan(is_0_pio4_reduced(x), x);
        else if (mode::range == r_0_20pi)     xx = if_else_nan(is_0_20pi_reduced(x), x);
        else if (mode::range == r_0_mpi)      xx = if_else_nan(is_0_mpi_reduced(x), x);
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


  template < class A0, class style>
  struct trig_reduction < A0, degree_tag, style, big_, double >
  {
    typedef typename meta::as_logical<A0>::type               bA0;
    typedef typename meta::as_integer<A0, signed>::type  int_type;

    static inline bA0 cot_invalid(const A0& x) { return logical_and(is_nez(x), is_even(x/_180<A0>())); }
    static inline bA0 tan_invalid(const A0& x) { return is_flint((x-_90<A0>())/_180<A0>()); }

    static inline int_type reduce(A0 x, A0& xr)
    {
      A0 xi = round2even(x*nt2::Oneo_90<A0>());
      A0 x2 = x - xi * _90<A0>();
      xr =  nt2::inrad(x2);
      return toint(xi);
    }
  };

  template < class A0, class style>
  struct trig_reduction < A0, pi_tag, style, big_, double>
  {
    typedef typename meta::as_logical<A0>::type               bA0;
    typedef typename meta::as_integer<A0, signed>::type  int_type;

    static inline bA0 cot_invalid(const A0& x) { return logical_and(is_nez(x), is_flint(x)); }
    static inline bA0 tan_invalid(const A0& x) { return is_flint(x-Half<A0>()); }
    static inline int_type reduce(const A0& x,  A0& xr)
    {
      A0 xi = round2even(x*Two<A0>());
      A0 x2 = x - xi * Half<A0>();
      xr = x2*Pi<A0>();
      return toint(xi);
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/bitwise_notand.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/sdk/simd/tags.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>


namespace nt2 { namespace details { namespace internal
{
  template < class A0,
             class unit_tag,
             class style,
             class base_A0 = typename meta::scalar_of<A0>::type
  >
  struct invtrig_base{};

  template < class A0 >
  struct invtrig_base<A0,radian_tag,tag::not_simd_type, float>
  {
    static inline A0 asin(const  A0& a0)
    {
      A0 sign, x, z;
      x = nt2::abs(a0);
      sign = nt2::bitofsign(a0);
      if ((x < single_constant<A0,0x38d1b717>())) return a0;
      if ((x >  nt2::One<A0>())) return nt2::Nan<A0>();
      bool bx_larger_05    = (x > nt2::Half<A0>());
      if (bx_larger_05)
      {
        z = nt2::Half<A0>()*nt2::oneminus(x);
        x =  nt2::sqrt(z);
      }
      else
      {
        z = nt2::sqr(x);
      }
      A0 z1 = nt2::fma(z,  single_constant<A0,0x3d2cb352>(),
                       single_constant<A0,0x3cc617e3>());
      z1 = nt2::fma(z1, z, single_constant<A0,0x3d3a3ec7>());
      z1 = nt2::fma(z1, z, single_constant<A0,0x3d9980f6>());
      z1 = nt2::fma(z1, z, single_constant<A0,0x3e2aaae4>());
      z1 = nt2::fma(z1, z*x, x);
      if(bx_larger_05)
      {
        z1 = z1+z1;
        z1 = nt2::Pio_2<A0>()-z1;
      }
      return bitwise_xor(z1, sign);
    }

    static inline A0 acos(const  A0& a0)
    {
      if (a0 < nt2::Mhalf<A0>())
        return nt2::Pi<A0>()-asin( nt2::sqrt(nt2::oneplus(a0)*nt2::Half<A0>()))*nt2::Two<A0>();
      else if (a0 > nt2::Half<A0>())
        return asin( nt2::sqrt(nt2::oneminus(a0)*nt2::Half<A0>()))*nt2::Two<A0>();
      return (nt2::Pio_2<A0>()-asin(a0));
    }

    static inline A0 atan(const A0& a0)
    {
      A0 x  = kernel_atan(a0);
      return nt2::bitwise_xor(x, nt2::bitofsign(a0));
    }

    static inline A0 kernel_atan(const  A0& a0)
    {
      if (nt2::is_eqz(a0))  return nt2::Zero<A0>();
      if (nt2::is_inf(a0))  return nt2::Pio_2<A0>();
      A0 x = nt2::abs(a0);
      A0 y;
      if( x >single_constant<A0,0x401a827a>())//2.414213562373095 )  /* tan 3pi/8 */
      {
        y = nt2::Pio_2<A0>();
        x = -nt2::rec(x);
      }
      else if( x > single_constant<A0,0x3ed413cd>()) //0.4142135623730950f ) /* tan pi/8 */
      {
        y = nt2::Pio_4<A0>();
        x = nt2::minusone(x)/nt2::oneplus(x);
      }
      else
        y = 0.0;

      A0 z = nt2::sqr(x);
      A0 z1 = nt2::fma(z,  single_constant<A0,0x3da4f0d1>(),single_constant<A0,0xbe0e1b85>());
      A0 z2 = nt2::fma(z,  single_constant<A0,0x3e4c925f>(),single_constant<A0,0xbeaaaa2a>());
      z1 = nt2::fma(z1, sqr(z), z2);
      return  nt2::add(y, nt2::fma(x, mul( z1, z), x));
    }
  };
} } }



#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_invtrig.hpp
// /////////////////////////////////////////////////////////////////////////////

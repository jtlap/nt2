//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED

#include <nt2/sdk/simd/tags.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace details { namespace internal
{
  template < class A0 >
  struct invtrig_base<A0,radian_tag,tag::simd_type, float>
  {
    typedef typename meta::as_logical<A0>::type    bA0;
    typedef typename A0::native_type              A0_n;
    static inline A0_n asin(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      A0 sign, x;
      x = nt2::abs(a0);
      sign = nt2::bitofsign(a0);
      const bA0 x_smaller_1e_4 = lt(x, single_constant<A0, 0x38d1b717>()); //1.0e-4f;
      const bA0 x_larger_05    = gt(x, nt2::Half<A0>());
      const bA0 x_else         = logical_or(x_smaller_1e_4, x_larger_05);
      A0 a = nt2::if_else_zero(x_smaller_1e_4, x);
      const A0 b = nt2::if_else_zero(x_larger_05, nt2::Half<A0>()*nt2::oneminus(x));
      A0 z = nt2::b_or(nt2::b_or(nt2::if_zero_else(x_else, nt2::sqr(x)), a), b);
      x = nt2::if_zero_else(x_else, x);
      a = nt2::if_else_zero(x_larger_05, sqrt(z));
      x = nt2::b_or(a, x);
      A0 z1 = nt2::fma(z,  single_constant<A0, 0x3d2cb352>(), single_constant<A0, 0x3cc617e3>());
      z1 = nt2::fma(z1, z, single_constant<A0, 0x3d3a3ec7>());
      z1 = nt2::fma(z1, z, single_constant<A0, 0x3d9980f6>());
      z1 = nt2::fma(z1, z, single_constant<A0, 0x3e2aaae4>());
      z1 = nt2::fma(z1, z*x, x);
      z = select(x_smaller_1e_4, z, z1);
      z1 = z+z;
      z1 = nt2::Pio_2<A0>()-z1;
      z = nt2::if_else(x_larger_05, z1, z);
      return nt2::b_xor(z, sign);
    }

    static inline A0_n acos(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      A0 x = nt2::abs(a0);
      A0 z2 = asin(a0);
      bA0 isgtxh = gt(x, nt2::Half<A0>());
      if (nt2::any(isgtxh))
      {
        const A0 as = asin(nt2::sqrt(nt2::oneminus(x)*nt2::Half<A0>()));
        const A0 z1 = as*nt2::Two<A0>();
        z2 = nt2::if_else(isgtxh, z1, z2);
      }
      z2 = nt2::if_else(lt(a0, nt2::Mhalf<A0>()), nt2::Pi<A0>()-z2, z2);
      return nt2::if_else(isgtxh, z2, nt2::Pio_2<A0>()-z2);
    }

    static inline A0_n atan(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      A0 x  = kernel_atan(a0);
      return nt2::b_xor(x, nt2::bitofsign(a0));
    }

    static inline A0_n kernel_atan(const A0_n a0_n)
    {
      const A0 a0 = a0_n;
      const A0 x = nt2::abs(a0);

      //here x is positive
      const bA0 flag1 = nt2::lt(x, single_constant<A0, 0x401a827a>()); //tan3pio8);
      const bA0 flag2 = nt2::logical_and(nt2::ge(x, single_constant<A0, 0x3ed413cd>()), flag1);
      A0 yy =  nt2::if_zero_else(flag1, Pio_2<A0>());
      yy =  nt2::if_else(flag2, Pio_4<A0>(), yy);
      A0 xx =   nt2::if_else(flag1, x, -rec(x));
      xx =  nt2::if_else(flag2, (nt2::minusone(x)/nt2::oneplus(x)),xx);
      const A0 z = nt2::sqr(xx);
      A0 z1 = nt2::fma(z,  single_constant<A0, 0x3da4f0d1>(),single_constant<A0, 0xbe0e1b85>());
      const A0 z2 = nt2::fma(z,  single_constant<A0, 0x3e4c925f>(),single_constant<A0, 0xbeaaaa2a>());
      z1 = nt2::fma(z1, nt2::sqr(z), z2);
      return  nt2::add(yy, nt2::fma(xx, nt2::mul( z1, z), xx));
    }
  };
} } }

#endif

/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_F_INVTRIG_HPP_INCLUDED
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_notand.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/sdk/simd/tags.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/any.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0 >
      struct invtrig_base<A0,radian_tag,tag::simd_type, float>
      {
        typedef typename meta::as_logical<A0>::type    bA0;
        typedef typename A0::native_type              A0_n; 
        static inline A0_n asin(const A0_n a0_n)
        {
          const A0 a0 = { a0_n };
          A0 sign, x;
          x = nt2::abs(a0);
          sign = bitofsign(a0);
          const bA0 x_smaller_1e_4 = lt(x, single_constant<A0, 0x38d1b717>()); //1.0e-4f;
          const bA0 x_larger_05    = gt(x, Half<A0>());
          const bA0 x_else         = logical_or(x_smaller_1e_4, x_larger_05);
          A0 a = if_else_zero(x_smaller_1e_4, x);
          const A0 b = if_else_zero(x_larger_05, Half<A0>()*oneminus(x));
          A0 z = b_or(b_or(if_zero_else(x_else, sqr(x)), a), b);
          x = if_zero_else(x_else, x);
          a = if_else_zero(x_larger_05, sqrt(z));
          x = b_or(a, x);
          A0 z1 = madd(z,  single_constant<A0, 0x3d2cb352>(), single_constant<A0, 0x3cc617e3>());
          z1 = madd(z1, z, single_constant<A0, 0x3d3a3ec7>());
          z1 = madd(z1, z, single_constant<A0, 0x3d9980f6>());
          z1 = madd(z1, z, single_constant<A0, 0x3e2aaae4>());
          z1 = madd(z1, z*x, x);
          z = select(x_smaller_1e_4, z, z1);
          z1 = z+z;
          z1 = Pio_2<A0>()-z1;
          z = select(x_larger_05, z1, z);
          return b_xor(z, sign);
        }
        
        static inline A0_n acos(const A0_n a0_n)
        {
          const A0 a0 = { a0_n };
          A0 x = nt2::abs(a0);
          A0 z2 = {asin(a0)};
          bA0 isgtxh = gt(x, Half<A0>());
          if (nt2::any(isgtxh))
            {
              const A0 as = {asin(sqrt(oneminus(x)*Half<A0>()))};
              const A0 z1 = as*Two<A0>(); 
              z2 = select(isgtxh, z1, z2);
            }
          z2 = select(lt(a0, -Half<A0>()), Pi<A0>()-z2, z2);
          return select(isgtxh, z2, Pio_2<A0>()-z2);
        }
        
        static inline A0_n atan(const A0_n a0_n)
        {
          const A0 a0 = {a0_n};
          A0 x  = {kernel_atan(a0)}; 
          return b_xor(x, bitofsign(a0));
        }

        static inline A0_n kernel_atan(const A0_n a0_n)
        {
          const A0 a0 = {a0_n};
          const A0 x = nt2::abs(a0);

          //here x is positive
          const bA0 flag1 = lt(x, single_constant<A0, 0x401a827a>()); //tan3pio8);
          const bA0 flag2 = logical_and(ge(x, single_constant<A0, 0x3ed413cd>()), flag1);
          A0 yy =  if_zero_else(flag1, Pio_2<A0>());
          yy =  select(flag2, Pio_4<A0>(), yy);
          A0 xx =   select(flag1, x, -rec(x));
          xx =  select(flag2, (minusone(x)/oneplus(x)),xx);
          const A0 z = sqr(xx);
          A0 z1 = madd(z,  single_constant<A0, 0x3da4f0d1>(),single_constant<A0, 0xbe0e1b85>());
          const A0 z2 = madd(z,  single_constant<A0, 0x3e4c925f>(),single_constant<A0, 0xbeaaaa2a>());
          z1 = madd(z1, sqr(z), z2);
          return  add(yy, madd(xx, mul( z1, z), xx));
        }
      }; 
    }
  }
}

#endif

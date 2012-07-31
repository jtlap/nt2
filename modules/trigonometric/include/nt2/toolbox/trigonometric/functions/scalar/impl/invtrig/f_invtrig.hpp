/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
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
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/nan.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
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
          //    bf::tie(sign, x) = sign_and_abs(a0);
          x = nt2::abs(a0);
          sign = bitofsign(a0);
          if ((x < single_constant<A0,0x38d1b717>())) return a0;
          if ((x >  One<A0>())) return Nan<A0>();
          bool bx_larger_05    = (x > Half<A0>());
          if (bx_larger_05)
            {
              z = Half<A0>()*oneminus(x);
              x =  sqrt(z);
            }
          else
            {
              z = sqr(x);
            }
          A0 z1 = madd(z,  single_constant<A0,0x3d2cb352>(),
                       single_constant<A0,0x3cc617e3>());
          z1 = madd(z1, z, single_constant<A0,0x3d3a3ec7>());
          z1 = madd(z1, z, single_constant<A0,0x3d9980f6>());
          z1 = madd(z1, z, single_constant<A0,0x3e2aaae4>());
          z1 = madd(z1, z*x, x);
          if(bx_larger_05)
            {
              z1 = z1+z1;
              z1 = Pio_2<A0>()-z1;
            }
          return b_xor(z1, sign);
        }

        static inline A0 acos(const  A0& a0)
        {
          if (a0 < Mhalf<A0>())
            return Pi<A0>()-asin( nt2::sqrt(oneplus(a0)*Half<A0>()))*Two<A0>();
          else if (a0 > Half<A0>())
            return asin( nt2::sqrt(oneminus(a0)*Half<A0>()))*Two<A0>();
          return (Pio_2<A0>()-asin(a0));
        }

        static inline A0 atan(const A0& a0)
        {
          A0 x  = kernel_atan(a0); 
          return b_xor(x, bitofsign(a0));
        }

        static inline A0 kernel_atan(const  A0& a0)
        {
          if (is_eqz(a0))  return Zero<A0>();
          if (is_inf(a0))  return Pio_2<A0>(); 
          A0 x = nt2::abs(a0);
          A0 y;   
          if( x >single_constant<A0,0x401a827a>())//2.414213562373095 )  /* tan 3pi/8 */
            {
              y = Pio_2<A0>();
              x = -rec(x);
            }

          else if( x > single_constant<A0,0x3ed413cd>()) //0.4142135623730950f ) /* tan pi/8 */
            {
              y = Pio_4<A0>();
              x = minusone(x)/oneplus(x);
            }
          else
            y = 0.0;

          A0 z = sqr(x);
          A0 z1 = madd(z,  single_constant<A0,0x3da4f0d1>(),single_constant<A0,0xbe0e1b85>());
          A0 z2 = madd(z,  single_constant<A0,0x3e4c925f>(),single_constant<A0,0xbeaaaa2a>());
          z1 = madd(z1, sqr(z), z2);
          return  add(y, madd(x, mul( z1, z), x));
//        y +=
//          ((( 8.05374449538e-2 * z
//              - 1.38776856032E-1) * z
//            + 1.99777106478E-1) * z
//           - 3.33329491539E-1) * z * x
//          + x;



        }
      }; 
    }
  }
}



#endif

// /////////////////////////////////////////////////////////////////////////////
// End of f_invtrig.hpp
// /////////////////////////////////////////////////////////////////////////////

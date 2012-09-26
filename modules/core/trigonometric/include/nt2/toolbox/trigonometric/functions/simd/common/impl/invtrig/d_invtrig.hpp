//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SIMD_COMMON_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/functions/simd/sign.hpp>
#include <nt2/include/functions/simd/bitwise_notand.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0 >
      struct invtrig_base<A0,radian_tag,tag::simd_type, double>
      {
        typedef typename meta::as_logical<A0>::type    bA0;
        typedef typename A0::native_type A0_n;
        static inline A0_n asin(const A0_n a0_n)
        {
          const A0 a0 = a0_n;
          typedef typename meta::scalar_of<A0>::type sA0;
          A0 x = nt2::abs(a0);
          const A0 pio4 =  Pio_4<A0>();
          const bA0 small_=  lt(x, Sqrteps<A0>());
          const A0 morebits = double_constant<A0, 0xbc91a62633145c07ll>();
          const A0 ct1      = double_constant<A0, 0x3fe4000000000000ll>();
          A0 zz1 = oneminus(x);
          const A0 vp = zz1*horner< NT2_HORNER_COEFF_T(sA0, 5,
                                                       (0x3f684fc3988e9f08ll,
                                                        0xbfe2079259f9290fll,
                                                        0x401bdff5baf33e6all,
                                                        0xc03991aaac01ab68ll,
                                                        0x403c896240f3081dll)
                                                       )>(zz1)/
                          horner< NT2_HORNER_COEFF_T(sA0, 5,
                                                     (0x3ff0000000000000ll,
                                                      0xc035f2a2b6bf5d8cll,
                                                      0x40626219af6a7f42ll,
                                                      0xc077fe08959063eell,
                                                      0x40756709b0b644bell)
                                                     )>(zz1);
          zz1 =  sqrt(zz1+zz1);
          A0 z = pio4-zz1;
          zz1 = fma(zz1, vp, morebits);
          z =  z-zz1;
          zz1 = z+pio4;
          A0 zz2 = sqr(a0);
          z = zz2*horner< NT2_HORNER_COEFF_T(sA0, 6,
                                         (0x3f716b9b0bd48ad3ll,
                                          0xbfe34341333e5c16ll,
                                          0x4015c74b178a2dd9ll,
                                          0xc0304331de27907bll,
                                          0x40339007da779259ll,
                                          0xc020656c06ceafd5ll)
                                         )>(zz2)/
                horner< NT2_HORNER_COEFF_T(sA0, 6,
                                         (0x3ff0000000000000ll,
                                          0xc02d7b590b5e0eabll,
                                          0x40519fc025fe9054ll,
                                          0xc06265bb6d3576d7ll,
                                          0x4061705684ffbf9dll,
                                          0xc04898220a3607acll)
                                         )>(zz2);
          zz2 = x*z+x;
          return if_nan_else( gt(x, One<A0>())
                            , b_xor ( select( small_
                                            , x
                                            , select( gt(x, ct1)
                                                    , zz1
                                                    , zz2
                                                    )
                                            )
                                    , bitofsign(a0)
                                    )
                            );
        }

        static inline A0_n acos(const A0_n a0_n)
        {
          const A0 a0 = a0_n;
          const A0 as = asin(  sqrt(Half<A0>() - Half<A0>()*a0) );
          A0 z1 = Two<A0>() * as;
          const A0 as1 = asin(a0);
          A0 z2 = ((Pio_4<A0>() - as1)+double_constant<A0, 0x3c91a62633145c07ll>())+ Pio_4<A0>();
          return if_nan_else( gt(abs(a0),One<A0>()), sel( gt(a0,Half<A0>()), z1, z2));
        }

        static inline A0_n atan(const A0_n a0_n)
        {
          const A0 a0 = a0_n;
          const A0 x  = kernel_atan(a0);
          return b_xor(x, bitofsign(a0));
        }

        static inline A0_n kernel_atan(const A0_n a0_n)
        {
          typedef typename meta::scalar_of<A0>::type sA0;
          const A0 tan3pio8  = double_constant<A0, 0x4003504f333f9de6ll>();
          const A0 tanpio8 = double_constant<A0, 0x3fda827999fcef31ll>();
          const A0 a0 = a0_n;
          const A0 x =  nt2::abs(a0);
          const bA0 flag1 = lt(x,  tan3pio8);
          const bA0 flag2 = logical_and(ge(x, tanpio8), flag1);
          A0 yy = if_zero_else(flag1, Pio_2<A0>());
          yy = select(flag2, Pio_4<A0>(), yy);
          A0 xx = select(flag1, x, -rec(x));
          xx = select(flag2, minusone(x)/oneplus(x),xx);
          A0 z = sqr(xx);
          z = z*horner< NT2_HORNER_COEFF_T(sA0, 5,
                                       (0xbfec007fa1f72594ll,
                                        0xc03028545b6b807all,
                                        0xc052c08c36880273ll,
                                        0xc05eb8bf2d05ba25ll,
                                        0xc0503669fd28ec8ell)
                                       )>(z)/
              horner< NT2_HORNER_COEFF_T(sA0, 6,
                                       (0x3ff0000000000000ll,
                                        0x4038dbc45b14603cll,
                                        0x4064a0dd43b8fa25ll,
                                        0x407b0e18d2e2be3bll,
                                        0x407e563f13b049eall,
                                        0x4068519efbbd62ecll)
                                       )>(z);
          z = fma(xx, z, xx);
          const A0 morebits = double_constant<A0, 0x3c91a62633145c07ll>();
          z = seladd(flag2, z, mul(Half<A0>(), morebits));
          z = z+if_zero_else(flag1, morebits);
          return yy + z;
        }
      };
    }
  }
}

#endif

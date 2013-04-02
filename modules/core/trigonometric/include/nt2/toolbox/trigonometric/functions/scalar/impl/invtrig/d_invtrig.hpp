//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/bitwise_xor.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2 { namespace details { namespace internal
{
  template < class A0 >
  struct invtrig_base<A0,radian_tag,tag::not_simd_type, double>
  {
    typedef typename meta::scalar_of<A0>::type stype;
    static inline A0 asin(const  A0& a0)
    {
      A0 x = nt2::abs(a0);
      if ((x >  nt2::One<A0>())) return nt2::Nan<A0>();
      if ((x <  nt2::Sqrteps<A0>())) return a0;
      A0 zz;
      if((x >  double_constant<double,0x3fe4000000000000ull> ())) //0.625;
      {
        zz = nt2::oneminus(x);
        const A0 vp = zz*nt2::horner< NT2_HORNER_COEFF_T(stype, 5,
                                                         (0x3f684fc3988e9f08ll,
                                                          0xbfe2079259f9290fll,
                                                          0x401bdff5baf33e6all,
                                                          0xc03991aaac01ab68ll,
                                                          0x403c896240f3081dll)
                                                        )>(zz)/
          nt2::horner< NT2_HORNER_COEFF_T(stype, 5,
                                          (0x3ff0000000000000ll,
                                           0xc035f2a2b6bf5d8cll,
                                           0x40626219af6a7f42ll,
                                           0xc077fe08959063eell,
                                           0x40756709b0b644bell)
                                         )>(zz);
        zz = nt2::sqrt(zz+zz);
        A0 z = nt2::Pio_4<A0>()-zz;
        zz = nt2::fma(zz, vp, double_constant<double,0xbc91a62633145c07ull>());
        z =  z-zz;
        zz = z+nt2::Pio_4<A0>();
      }
      else
      {
        zz = nt2::sqr(x);
        A0 z = zz*nt2::horner< NT2_HORNER_COEFF_T(stype, 6,
                                             (0x3f716b9b0bd48ad3ll,
                                              0xbfe34341333e5c16ll,
                                              0x4015c74b178a2dd9ll,
                                              0xc0304331de27907bll,
                                              0x40339007da779259ll,
                                              0xc020656c06ceafd5ll)
                                            )>(zz)/
          nt2::horner< NT2_HORNER_COEFF_T(stype, 6,
                                          (0x3ff0000000000000ll,
                                           0xc02d7b590b5e0eabll,
                                           0x40519fc025fe9054ll,
                                           0xc06265bb6d3576d7ll,
                                           0x4061705684ffbf9dll,
                                           0xc04898220a3607acll)
                                         )>(zz);
        zz = x*z+x;
      }
      return nt2::bitwise_xor(nt2::bitofsign(a0), zz);
    }

    static inline A0 acos(const  A0& a0)
    {
      if ((abs(a0) > One<A0>())) return nt2::Nan<A0>();
      if( a0 > nt2::Half<A0>() )
      {
        return nt2::Two<A0>() * asin(  nt2::sqrt(nt2::Half<A0>() - nt2::Half<A0>()*a0) ) ;
      }
      A0 z = nt2::Pio_4<A0>() - asin(a0);
      z = z + double_constant<double,0x3c91a62633145c07ull>();//6.123233995736765886130E-17
      z = z + nt2::Pio_4<A0>();
      return( z );
    }

    static inline A0 atan(const A0& a0)
    {
      A0 x  = kernel_atan(a0);
      return nt2::bitwise_xor(x, nt2::bitofsign(a0));
    }

    static inline A0 kernel_atan(const  A0& a0)
    {
      if (is_eqz(a0))  return nt2::Zero<A0>();
      if (is_inf(a0)) return nt2::Pio_2<A0>();
      A0 x =  nt2::abs(a0);
      A0 y;
      A0 flag = (x >  double_constant<double,0x4003504f333f9de6ull>());
      if (flag)
      {
        y =  nt2::Pio_2<A0>();
        x =  -nt2::rec(x);
      }
      else if ((x <=  double_constant<double,0x3fe51eb851eb851full>()))
      {
        y = nt2::Zero<A0>();
      }
      else
      {
        y = nt2::Pio_4<A0>();
        flag = nt2::Half<A0>();
        x = nt2::minusone(x)/nt2::oneplus(x);
      }
      A0 z = nt2::sqr(x);
      z = z*nt2::horner< NT2_HORNER_COEFF_T(stype, 5,
                                            (0xbfec007fa1f72594ll,
                                             0xc03028545b6b807all,
                                             0xc052c08c36880273ll,
                                             0xc05eb8bf2d05ba25ll,
                                             0xc0503669fd28ec8ell)
                                           )>(z)/
           nt2::horner< NT2_HORNER_COEFF_T(stype, 6,
                                           (0x3ff0000000000000ll,
                                            0x4038dbc45b14603cll,
                                            0x4064a0dd43b8fa25ll,
                                            0x407b0e18d2e2be3bll,
                                            0x407e563f13b049eall,
                                            0x4068519efbbd62ecll)
                                          )>(z);
      z = nt2::fma(x, z, x);
      static const A0 morebits = double_constant<double,0x3c91a62633145c07ull>();
      z += flag * morebits;
      return y + z;
    }
  };
} } }


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_invtrig.hpp
// /////////////////////////////////////////////////////////////////////////////

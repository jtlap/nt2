//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_IMPL_INVTRIG_D_INVTRIG_HPP_INCLUDED
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/digits.hpp>

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      template < class A0 >
      struct invtrig_base<A0,radian_tag,trig_tag,tag::simd_type, double>
      {
	static inline A0 asin(const A0& a0)
	{
	  typedef typename meta::scalar_of<A0>::type sA0;
	  A0 x = nt2::abs(a0);
	  static const A0 pio4 =  Pio_4<A0>();
	  static const A0 small=  lt(x, Sqrteps<A0>());
	  static const A0 morebits = double_constant<A0, 0xbc91a62633145c07ll>();
	  static const A0 ct1      = double_constant<A0, 0x3fe4000000000000ll>();
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
	  return b_or(b_xor(select(small,
				   x,
				   select(gt(x, ct1),
					  zz1,
					  zz2
					  )
				   ),
			    bitofsign(a0)
			    ),
		      gt(x, One<A0>())
		      );
	}

        static inline A0 acos(const A0& a0)
	{
	  A0 z1 = Two<A0>() * asin(  sqrt(Half<A0>() - Half<A0>()*a0) );
	  A0 z2 = ((Pio_4<A0>() - asin(a0))+double_constant<A0, 0x3c91a62633145c07ll>())+ Pio_4<A0>();
	  return b_or( gt(abs(a0),One<A0>()), sel( gt(a0,Half<A0>()), z1, z2));
	}

	static inline A0 atan(const A0& a0)
	{
	  typedef typename meta::scalar_of<A0>::type sA0;
	  static const A0 tan3pio8  = double_constant<A0, 0x4003504f333f9de6ll>();
	  static const A0 Twothird = double_constant<A0, 0x3fe51eb851eb851fll>();
	  static const A0 tanpio8 = double_constant<A0, 0x3fda827999fcef31ll>();
	  A0 x =  nt2::abs(a0);
	  const A0 flag1 = lt(x,  double_constant<A0, 0x4003504f333f9de6ll>());              //tan3pio8
	  const A0 flag2 = b_and(ge(x, double_constant<A0, 0x3fda827999fcef31ll>()), flag1); //tanpio8
	  A0 yy =  b_notand(flag1, Pio_2<A0>());
	  yy =  select(flag2, Pio_4<A0>(), yy);
	  A0 xx =   select(flag1, x, -rec(x));
	  xx =  select(flag2, minusone(x)/oneplus(x),xx);
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
	  //	static const A0 morebits = double_constant<A0, 0x3c91a62633145c07ll>();
	  z = seladd(flag2, z, mul(Half<A0>(),  double_constant<A0, 0x3c91a62633145c07ll>()));
	  z = z+b_notand(flag1, double_constant<A0, 0x3c91a62633145c07ll>());
	  yy = yy + z;
	  return b_xor(yy, bitofsign(a0));
	}
      };
    }
  }
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_invtrig.hpp
// /////////////////////////////////////////////////////////////////////////////

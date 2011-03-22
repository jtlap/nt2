/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_NUMERIC_FUNCTION_DETAILS_SIMD_COMMON_IMPL_TRIGO_D_INVTRIG_HPP_INCLUDED
#define NT2_CORE_NUMERIC_FUNCTION_DETAILS_SIMD_COMMON_IMPL_TRIGO_D_INVTRIG_HPP_INCLUDED

namespace nt2
{
  namespace details
  {
    namespace internal
    {
      using simd::native; 
      inline native<double> asin(const native<double>& a0)
      {
	typedef native<double> A0;
	A0 x = abs(a0);
	static const A0 pio4 =  Pio_4<A0>();
	static const A0 small=  islt(x, Sqrteps<A0>());
	static const A0 morebits = Const<A0, 0xbc91a62633145c07ll>();
	static const A0 ct1      = Const<A0, 0x3fe4000000000000ll>();
	A0 zz1 = oneminus(x);
	const A0 vp = zz1*horner< NT2_HORNER_COEFF(double, 5,
						   (0x3f684fc3988e9f08ll,
						    0xbfe2079259f9290fll,
						    0x401bdff5baf33e6all,
						    0xc03991aaac01ab68ll,
						    0x403c896240f3081dll)
						   )>(zz1)/
			  horner< NT2_HORNER_COEFF(double, 5,
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
        z = zz2*horner< NT2_HORNER_COEFF(double, 6,
					 (0x3f716b9b0bd48ad3ll,
					  0xbfe34341333e5c16ll,
					  0x4015c74b178a2dd9ll,
					  0xc0304331de27907bll,
					  0x40339007da779259ll,
					  0xc020656c06ceafd5ll)
					 )>(zz2)/
		horner< NT2_HORNER_COEFF(double, 6,
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
			      select(isgt(x, ct1),
				  zz1,
				  zz2
				  )
			      ),
			  bitofsign(a0)
			  ),
		    isgt(x, One<A0>())
		    );
      }

      inline native<double> acos(const  native<double>& a0)
      {
	typedef native<double> A0;
	A0 z1 = Two<A0>() * asin(  sqrt(Half<A0>() - Half<A0>()*a0) );
	A0 z2 = ((Pio_4<A0>() - asin(a0))+Const<A0, 0x3c91a62633145c07ll>())+ Pio_4<A0>();
	return b_or(abs(a0) > One<A0>(), sel( a0 > Half<A0>(), z1, z2)); 
      }

      inline native<double> atan(const  native<double>& a0)
      {
	typedef native<double> A0;
	static const A0 tan3pio8  = Const<native<double>, 0x4003504f333f9de6ll>();
	static const A0 Twothird = Const<native<double>, 0x3fe51eb851eb851fll>();
	static const A0 tanpio8 = Const<native<double>, 0x3fda827999fcef31ll>();
	A0 x =  abs(a0);
	const A0 flag1 = islt(x,  Const<native<double>, 0x4003504f333f9de6ll>());              //tan3pio8
	const A0 flag2 = b_and(isge(x, Const<native<double>, 0x3fda827999fcef31ll>()), flag1); //tanpio8
	A0 yy =  b_notand(flag1, Pio_2<A0>());
	yy =  select(flag2, Pio_4<A0>(), yy);
	A0 xx =   select(flag1, x, -rec(x));
	xx =  select(flag2, minusone(x)/oneplus(x),xx);
	A0 z = sqr(xx);
	z = z*horner< NT2_HORNER_COEFF(double, 5,
				       (0xbfec007fa1f72594ll,
					0xc03028545b6b807all,
					0xc052c08c36880273ll,
					0xc05eb8bf2d05ba25ll,
					0xc0503669fd28ec8ell)
				       )>(z)/
	      horner< NT2_HORNER_COEFF(double, 6,
				       (0x3ff0000000000000ll,
					0x4038dbc45b14603cll,
					0x4064a0dd43b8fa25ll,
					0x407b0e18d2e2be3bll,
					0x407e563f13b049eall,
					0x4068519efbbd62ecll)
				       )>(z);
        z = fma(xx, z, xx);
	//	static const A0 morebits = Const<native<double>, 0x3c91a62633145c07ll>();
        z = seladd(flag2, z, mul(Half<A0>(),  Const<native<double>, 0x3c91a62633145c07ll>()));
        z = z+b_notand(flag1, Const<A0, 0x3c91a62633145c07ll>());
        yy = yy + z;
        return b_xor(yy, bitofsign(a0));
      }
    }
  }
}


#endif

// /////////////////////////////////////////////////////////////////////////////
// End of d_invtrig.hpp
// /////////////////////////////////////////////////////////////////////////////

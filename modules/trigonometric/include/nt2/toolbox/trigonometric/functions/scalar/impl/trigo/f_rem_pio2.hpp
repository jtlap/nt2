/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_F_REM_PIO2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_IMPL_TRIGO_F_REM_PIO2_HPP_INCLUDED
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/floor.hpp>


#define GET_A0_WORD(i,d)						\
  do {									\
    A0 f = (d);								\
    (i) = *reinterpret_cast<uint32_t*>(&f);				\
  } while (0)								\
    /**/

/* Set a float from a 32 bit int.  */
#define SET_A0_WORD(d,i)					\
  do {								\
    int ii = (i);						\
    (d) = *reinterpret_cast<A0*>(&ii);				\
  } while (0)							\
    /**/

namespace nt2 {
  /*
   * ====================================================
   * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
   *
   * Developed at SunPro, a Sun Microsystems, Inc. business.
   * Permission to use, copy, modify, and distribute this
   * software is freely granted, provided that this notice
   * is preserved.
   * ====================================================
   */
  namespace details
  {
    namespace internal
    {
      
      template < class A0,
		 class style, 
		 class base_A0 = typename meta::scalar_of<A0>::type
      > struct rpio2;
    
      template < class A0 > struct rpio2 < A0, tag::not_simd_type, float > 
      {
	static inline void rem_pio2(const A0& x, int32_t &n, A0&xr, A0&xc)
	{
	  A0 y[2];
	  n = __ieee754_rem_pio2f(x, y);
	  xr = y[0];
	  xc = y[1];
	}
	
	static int32_t __ieee754_rem_pio2f(A0 x, A0 *y)
	{
	  /*
	   * Table of constants for 2/pi, 396 Hex digits (476 decimal) of 2/pi
	   */
	  static const int32_t two_over_pi[] = {
	    0xA2, 0xF9, 0x83, 0x6E, 0x4E, 0x44, 0x15, 0x29, 0xFC,
	    0x27, 0x57, 0xD1, 0xF5, 0x34, 0xDD, 0xC0, 0xDB, 0x62,
	    0x95, 0x99, 0x3C, 0x43, 0x90, 0x41, 0xFE, 0x51, 0x63,
	    0xAB, 0xDE, 0xBB, 0xC5, 0x61, 0xB7, 0x24, 0x6E, 0x3A,
	    0x42, 0x4D, 0xD2, 0xE0, 0x06, 0x49, 0x2E, 0xEA, 0x09,
	    0xD1, 0x92, 0x1C, 0xFE, 0x1D, 0xEB, 0x1C, 0xB1, 0x29,
	    0xA7, 0x3E, 0xE8, 0x82, 0x35, 0xF5, 0x2E, 0xBB, 0x44,
	    0x84, 0xE9, 0x9C, 0x70, 0x26, 0xB4, 0x5F, 0x7E, 0x41,
	    0x39, 0x91, 0xD6, 0x39, 0x83, 0x53, 0x39, 0xF4, 0x9C,
	    0x84, 0x5F, 0x8B, 0xBD, 0xF9, 0x28, 0x3B, 0x1F, 0xF8,
	    0x97, 0xFF, 0xDE, 0x05, 0x98, 0x0F, 0xEF, 0x2F, 0x11,
	    0x8B, 0x5A, 0x0A, 0x6D, 0x1F, 0x6D, 0x36, 0x7E, 0xCF,
	    0x27, 0xCB, 0x09, 0xB7, 0x4F, 0x46, 0x3F, 0x66, 0x9E,
	    0x5F, 0xEA, 0x2D, 0x75, 0x27, 0xBA, 0xC7, 0xEB, 0xE5,
	    0xF1, 0x7B, 0x3D, 0x07, 0x39, 0xF7, 0x8A, 0x52, 0x92,
	    0xEA, 0x6B, 0xFB, 0x5F, 0xB1, 0x1F, 0x8D, 0x5D, 0x08,
	    0x56, 0x03, 0x30, 0x46, 0xFC, 0x7B, 0x6B, 0xAB, 0xF0,
	    0xCF, 0xBC, 0x20, 0x9A, 0xF4, 0x36, 0x1D, 0xA9, 0xE3,
	    0x91, 0x61, 0x5E, 0xE6, 0x1B, 0x08, 0x65, 0x99, 0x85,
	    0x5F, 0x14, 0xA0, 0x68, 0x40, 0x8D, 0xFF, 0xD8, 0x80,
	    0x4D, 0x73, 0x27, 0x31, 0x06, 0x06, 0x15, 0x56, 0xCA,
	    0x73, 0xA8, 0xC9, 0x60, 0xE2, 0x7B, 0xC0, 0x8C, 0x6B,
	  };

	  /* This array is like the one in e_rem_pio2.c, but the numbers are
	     single precision and the last 8 bits are forced to 0.  */
	  static const int32_t npio2_hw[] = {
	    0x3fc90f00, 0x40490f00, 0x4096cb00, 0x40c90f00, 0x40fb5300, 0x4116cb00,
	    0x412fed00, 0x41490f00, 0x41623100, 0x417b5300, 0x418a3a00, 0x4196cb00,
	    0x41a35c00, 0x41afed00, 0x41bc7e00, 0x41c90f00, 0x41d5a000, 0x41e23100,
	    0x41eec200, 0x41fb5300, 0x4203f200, 0x420a3a00, 0x42108300, 0x4216cb00,
	    0x421d1400, 0x42235c00, 0x4229a500, 0x422fed00, 0x42363600, 0x423c7e00,
	    0x4242c700, 0x42490f00
	  };
	  
	  /*
	   * invpio2:  24 bits of 2/pi
	   * pio2_1:   first  17 bit of pi/2
	   * pio2_1t:  pi/2 - pio2_1
	   * pio2_2:   second 17 bit of pi/2
	   * pio2_2t:  pi/2 - (pio2_1+pio2_2)
	   * pio2_3:   third  17 bit of pi/2
	   * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
	   */
	  
	  static const A0
	    two8 =  2.5600000000e+02f, /* 0x43800000 */
	    invpio2 =  6.3661980629e-01f, /* 0x3f22f984 */
	    pio2_1  =  1.5707855225e+00f, /* 0x3fc90f80 */
	    pio2_1t =  1.0804334124e-05f, /* 0x37354443 */
	    pio2_2  =  1.0804273188e-05f, /* 0x37354400 */
	    pio2_2t =  6.0770999344e-11f, /* 0x2e85a308 */
	    pio2_3  =  6.0770943833e-11f, /* 0x2e85a300 */
	    pio2_3t =  6.1232342629e-17f;  /* 0x248d3132 */

	  A0 z,w,t,r,fn;
	  A0 tx[3];
	  int32_t e0,i,j,nx,n,ix,hx;
	  
	  GET_A0_WORD(hx,x);
	  ix = hx&0x7fffffff;
	  if(ix<=0x3f490fd8)   /* |x| ~<= pi/4 , no need for reduction */
	    {y[0] = x; y[1] = 0; return 0;}
	  if(ix<0x4016cbe4) {  /* |x| < 3pi/4, special case with n=+-1 */
	    if(hx>0) {
	      z = x - pio2_1;
	      if((ix&0xfffffff0)!=0x3fc90fd0) { /* 24+24 bit pi OK */
		y[0] = z - pio2_1t;
		y[1] = (z-y[0])-pio2_1t;
	      } else {		/* near pi/2, use 24+24+24 bit pi */
		z -= pio2_2;
		y[0] = z - pio2_2t;
		y[1] = (z-y[0])-pio2_2t;
	      }
	      return 1;
	    } else {	/* negative x */
	      z = x + pio2_1;
	      if((ix&0xfffffff0)!=0x3fc90fd0) { /* 24+24 bit pi OK */
		y[0] = z + pio2_1t;
		y[1] = (z-y[0])+pio2_1t;
	      } else {		/* near pi/2, use 24+24+24 bit pi */
		z += pio2_2;
		y[0] = z + pio2_2t;
		y[1] = (z-y[0])+pio2_2t;
	      }
	      return -1;
	    }
	  }
	  if(ix<=0x43490f80) { /* |x| ~<= 2^7*(pi/2), medium size */
	    t  = fabsf(x);
	    n  = (int32_t) (t*invpio2+Half<A0>());
	    fn = (A0)n;
	    r  = t-fn*pio2_1;
	    w  = fn*pio2_1t;	/* 1st round good to 40 bit */
	    if(n<32&&(int32_t)(ix&0xffffff00)!=npio2_hw[n-1]) {
	      y[0] = r-w;	/* quick check no cancellation */
	    } else {
	      u_int32_t high;
	      j  = ix>>23;
	      y[0] = r-w;
	      GET_A0_WORD(high,y[0]);
	      i = j-((high>>23)&0xff);
	      if(i>8) {  /* 2nd iteration needed, good to 57 */
		t  = r;
		w  = fn*pio2_2;
		r  = t-w;
		w  = fn*pio2_2t-((t-r)-w);
		y[0] = r-w;
		GET_A0_WORD(high,y[0]);
		i = j-((high>>23)&0xff);
		if(i>25)  {	/* 3rd iteration need, 74 bits acc */
		  t  = r;	/* will cover all possible cases */
		  w  = fn*pio2_3;
		  r  = t-w;
		  w  = fn*pio2_3t-((t-r)-w);
		  y[0] = r-w;
		}
	      }
	    }
	    y[1] = (r-y[0])-w;
	    if(hx<0) 	{y[0] = -y[0]; y[1] = -y[1]; return -n;}
	    else	 return n;
	  }
	  /*
	   * all other (large) arguments
	   */
	  if(ix>=0x7f800000) {		/* x is inf or NaN */
	    y[0]=y[1]=x-x; return 0;
	  }
	  /* set z = scalbn(|x|,ilogb(x)-7) */
	  e0 	= (ix>>23)-134;		/* e0 = ilogb(z)-7; */
	  SET_A0_WORD(z, ix - ((int32_t)(e0<<23)));
	  for(i=0;i<2;i++) {
	    tx[i] = (A0)((int32_t)(z));
	    z     = (z-tx[i])*two8;
	  }
	  tx[2] = z;
	  nx = 3;
	  while(tx[nx-1]==Zero<A0>()) nx--;	/* skip zero term */
	  n  =  __kernel_rem_pio2f(tx,y,e0,nx,2,two_over_pi);
	  if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
	  return n;
	}
	
	
	static int __kernel_rem_pio2f(A0 *x, A0 *y, int e0, int nx, int prec, const int32_t *ipio2) 
	{
	  static const int init_jk[] = {4,7,9}; /* initial value for jk */
	  
	  static const A0 PIo2[] = {
	    1.5703125000e+00f, /* 0x3fc90000 */
	    4.5776367188e-04f, /* 0x39f00000 */
	    2.5987625122e-05f, /* 0x37da0000 */
	    7.5437128544e-08f, /* 0x33a20000 */
	    6.0026650317e-11f, /* 0x2e840000 */
	    7.3896444519e-13f, /* 0x2b500000 */
	    5.3845816694e-15f, /* 0x27c20000 */
	    5.6378512969e-18f, /* 0x22d00000 */
	    8.3009228831e-20f, /* 0x1fc40000 */
	    3.2756352257e-22f, /* 0x1bc60000 */
	    6.3331015649e-25f, /* 0x17440000 */
	  };
	  
	  static const A0
	    two8 =  2.5600000000e+02f, /* 0x43800000 */
	    twon8  =  3.9062500000e-03f; /* 0x3b800000 */
	  int32_t jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
	  A0 z,fw,f[20],fq[20],q[20];
	  
	  /* initialize jk*/
	  jk = init_jk[prec];
	  jp = jk;
	  
	  /* determine jx,jv,q0, note that 3>q0 */
	  jx =  nx-1;
	  jv = (e0-3)/8; if(jv<0) jv=0;
	  q0 =  e0-8*(jv+1);
	  
	  /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
	  j = jv-jx; m = jx+jk;
	  for(i=0;i<=m;i++,j++) f[i] = (j<0)? Zero<A0>() : (A0) ipio2[j];
	  
	  /* compute q[0],q[1],...q[jk] */
	  for (i=0;i<=jk;i++) {
	    for(j=0,fw=0.0f;j<=jx;j++) fw += x[j]*f[jx+i-j]; q[i] = fw;
	  }
	  
	  jz = jk;
	recompute:
	  /* distill q[] into iq[] reversingly */
	  for(i=0,j=jz,z=q[jz];j>0;i++,j--) {
	    fw    =  (A0)((int32_t)(twon8* z));
	    iq[i] =  (int32_t)(z-two8*fw);
	    z     =  q[j-1]+fw;
	  }
	  
	  /* compute n */
	  z  = nt2::ldexp(z,q0);		/* actual value of z */
	  z -= (A0)8.0f*nt2::floor(z*(A0)0.125f);	/* trim off integer >= 8 */
	  n  = (int32_t) z;
	  z -= (A0)n;
	  ih = 0;
	  if(q0>0) {	/* need iq[jz-1] to determine n */
	    i  = (iq[jz-1]>>(8-q0)); n += i;
	    iq[jz-1] -= i<<(8-q0);
	    ih = iq[jz-1]>>(7-q0);
	  } 
	  else if(q0==0) ih = iq[jz-1]>>8;
	  else if(z>=(A0)0.5f) ih=2;
	  
	  if(ih>0) {	/* q > 0.5f */
	    n += 1; carry = 0;
	    for(i=0;i<jz ;i++) {	/* compute 1-q */
	      j = iq[i];
	      if(carry==0) {
		if(j!=0) {
		  carry = 1; iq[i] = 0x100- j;
		}
	      } else  iq[i] = 0xff - j;
	    }
	    if(q0>0) {		/* rare case: chance is 1 in 12 */
	      switch(q0) {
	      case 1:
		iq[jz-1] &= 0x7f; break;
	      case 2:
		iq[jz-1] &= 0x3f; break;
	      }
	    }
	    if(ih==2) {
	      z = One<A0>() - z;
	      if(carry!=0) z -= nt2::ldexp(One<A0>(),q0);
	    }
	  }
	  
	  /* check if recomputation is needed */
	  if(z==Zero<A0>()) {
	    j = 0;
	    for (i=jz-1;i>=jk;i--) j |= iq[i];
	    if(j==0) { /* need recomputation */
	      for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */
	      
	      for(i=jz+1;i<=jz+k;i++) {   /* add q[jz+1] to q[jz+k] */
		f[jx+i] = (A0) ipio2[jv+i];
		for(j=0,fw=0.0f;j<=jx;j++) fw += x[j]*f[jx+i-j];
		q[i] = fw;
	      }
	      jz += k;
	      goto recompute;
	    }
	  }
	  
	  /* chop off zero terms */
	  if(z==(A0)0.0f) {
	    jz -= 1; q0 -= 8;
	    while(iq[jz]==0) { jz--; q0-=8;}
	  } else { /* break z into 8-bit if necessary */
	    z = nt2::ldexp(z,-q0);
	    if(z>=two8) { 
	      fw = (A0)((int32_t)(twon8*z));
	      iq[jz] = (int32_t)(z-two8*fw);
	      jz += 1; q0 += 8;
	      iq[jz] = (int32_t) fw;
	    } else iq[jz] = (int32_t) z ;
	  }
	  
	  /* convert integer "bit" chunk to floating-point value */
	  fw = nt2::ldexp(One<A0>(),q0);
	  for(i=jz;i>=0;i--) {
	    q[i] = fw*(A0)iq[i]; fw*=twon8;
	  }
	  
	  /* compute PIo2[0,...,jp]*q[jz,...,0] */
	  for(i=jz;i>=0;i--) {
	    for(fw=0.0f,k=0;k<=jp&&k<=jz-i;k++) fw += PIo2[k]*q[i+k];
	    fq[jz-i] = fw;
	  }
	  
	  /* compress fq[] into y[] */
	  switch(prec) {
	  case 0:
	    fw = 0.0f;
	    for (i=jz;i>=0;i--) fw += fq[i];
	    y[0] = (ih==0)? fw: -fw; 
	    break;
	  case 1:
	  case 2:
	    fw = 0.0f;
	    for (i=jz;i>=0;i--) fw += fq[i]; 
	    y[0] = (ih==0)? fw: -fw; 
	    fw = fq[0]-fw;
	    for (i=1;i<=jz;i++) fw += fq[i];
	    y[1] = (ih==0)? fw: -fw; 
	    break;
	  case 3:	/* painful */
	    for (i=jz;i>0;i--) {
	      fw      = fq[i-1]+fq[i]; 
	      fq[i]  += fq[i-1]-fw;
	      fq[i-1] = fw;
	    }
	    for (i=jz;i>1;i--) {
	      fw      = fq[i-1]+fq[i]; 
	      fq[i]  += fq[i-1]-fw;
	      fq[i-1] = fw;
	    }
	    for (fw=0.0f,i=jz;i>=2;i--) fw += fq[i]; 
	    if(ih==0) {
	      y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
	    } else {
	      y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
	    }
	  }
	  return n&7;
	}
      };
    }
  }
}

#endif
#undef GET_A0_WORD
#undef SET_A0_WORD

// /////////////////////////////////////////////////////////////////////////////
// End of rem_pio2.hpp
// /////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_LOG1P_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_LOG1P_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/oneplus.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::log1p_, tag::cpu_,
                        (A0)(X),
                        ((simd_<double_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::log1p_(tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 u = oneplus(a0);
      return sel(eq(u, Inf<A0>()),
		 u,
		 log(u) - ((u-One<A0>())-a0)/u); /* cancels errors with IEEE arithmetic */
      
//    typedef typename meta::as_integer<A0, signed>::type int_type;
//    const A0 ln2_hi  =  nt2::vector_of<A0>(6.93147180369123816490e-01);     /* 3fe62e42 fee00000 */
//    const A0 ln2_lo  =  nt2::vector_of<A0>(1.90821492927058770002e-10);     /* 3dea39ef 35793c76 */
//    //      two54   =  1.80143985094819840000e+16,  /* 43500000 00000000 */
//    const A0 Lg1 = nt2::vector_of<A0>(6.666666666666735130e-01);  /* 3FE55555 55555593 */
//    const A0 Lg2 = nt2::vector_of<A0>(3.999999999940941908e-01);  /* 3FD99999 9997FA04 */
//    const A0 Lg3 = nt2::vector_of<A0>(2.857142874366239149e-01);  /* 3FD24924 94229359 */
//    const A0 Lg4 = nt2::vector_of<A0>(2.222219843214978396e-01);  /* 3FCC71C5 1D8E78AF */
//    const A0 Lg5 = nt2::vector_of<A0>(1.818357216161805012e-01);  /* 3FC74664 96CB03DE */
//    const A0 Lg6 = nt2::vector_of<A0>(1.531383769920937332e-01);  /* 3FC39A09 D078C69F */
//    const A0 Lg7 = nt2::vector_of<A0>(1.479819860511658591e-01);  /* 3FC2F112 DF3E5244 */
//    const A0 sqrth = nt2::vector_of<A0>( 0.70710678118654752440);
//    const A0 one =  One<A0>();
//         A0 x;
//    int_type k;
//    bf::tie(x, k) = fast_frexp(one+a0);
//    const int_type x_lt_sqrthf = cast<int_type>(isgt(sqrth, x));
//         k = k+x_lt_sqrthf;
//    A0 u =  oneplus(x);
//    A0 f = x+b_and(x,cast<A0>(x_lt_sqrthf))-one;
//    A0 dk = tofloat(k);
//    A0 s = f/add(Two<A0>(),f);
//    A0 z = sqr(s);
//    A0 w = sqr(z);
//    A0 t1= w*madd(Lg2, w, madd(Lg4, w, Lg6));
//    A0 t2= z*madd(Lg1, w, madd(Lg3, w, madd(Lg5, w, Lg7)));
//    A0 R = t2+t1;
//    A0 hfsq = mul(Half<A0>(), sqr(f));
//    //    A0 c  = select(isgtz(dk), one-(u-x), x-(u-one))/b_or(u, iseqz(u)); // correction term
//    A0 z2 = mul(dk, ln2_hi)-((hfsq-(s*(hfsq+R)+(mul(dk,ln2_lo))))-f);
//         const A0 small_mask = b_or(iseqz(a0),iseq(a0,Inf<A0>()));
//    return b_or(isltz(u),z2*select(small_mask,One<A0>(),(a0/(minusone(u)))));
//    //    return z2;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::log1p_, tag::cpu_,
                        (A0)(X),
                        ((simd_<float_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::log1p_(tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 u = oneplus(a0);
      return sel(eq(u, Inf<A0>()),
		 u,
		 log(u) - ((u-One<A0>())-a0)/u); /* cancels errors with IEEE arithmetic */

//    const A0 u = oneplus(a0);
//    const A0 small_mask = b_or(iseq(u,One<A0>()),iseq(a0,Inf<A0>()));
//    const A0 l = log(u);
//    return b_or(isltz(u),select(small_mask,a0,l*(a0/(minusone(u)))));
    }
  };
} }

#endif
// modified by jt the 05/01/2011

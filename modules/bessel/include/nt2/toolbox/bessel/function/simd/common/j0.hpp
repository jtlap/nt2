//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_J0_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_J0_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/all.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::j0_, tag::cpu_,
                     (A0)(X),
                     ((simd_<arithmetic_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::j0_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      return nt2::j0(tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::j0_, tag::cpu_,
                     (A0)(X),
                     ((simd_<double_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::j0_(tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return map(functor<tag::j0_>(), a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::j0_, tag::cpu_,
                     (A0)(X),
                     ((simd_<float_<A0>,X>))
                    );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::j0_(tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      A0 x   =  nt2::abs(a0);
      A0 lt2 = lt(x, Two<A0>());
      if (all(lt2))
      return branch1(x);
      else
      return select (lt2, branch1(x), branch2(x));
      // as branch1 is quick there is no need for an "else if" case
      // computing only branch2,  this probably due to the double pipeline
    }

    template < class A0 > static inline A0 branch1(const A0 & x)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
      const A0 z = sqr(x);
      return (z-single_constant<A0,0x40b90fdc> ())*
	horner< NT2_HORNER_COEFF_T(stype, 5,
				 (0xb382511c,
				  0x36d660a0,
				  0xb9d01fb1,
				  0x3c5a6271,
				  0xbe3110a6
				  ) ) > (z);
    }
    template < class A0 > static inline A0 branch2(const A0 & x)
    {
      typedef typename meta::scalar_of<A0>::type stype; 
      A0 q = rec(x);
      A0 w = sqrt(q);
      A0 p3 = w *
	horner< NT2_HORNER_COEFF_T(stype, 8,
			       (0xbd8c100e,
				0x3e3ef887,
				0xbe5ba616,
				0x3df54214,
				0xbb69539e,
				0xbd4b8bc1,
				0xb6612dc2,
				0x3f4c422a
				) ) > (q);

       w = sqr(q);
       A0 xn =  q*
          horner< NT2_HORNER_COEFF_T(stype, 8,
			       (0x4201aee0,
				0xc2113945,
				0x418c7f6a,
				0xc09f3306,
				0x3f8040aa,
				0xbe46a57f,
				0x3d84ed6e,
				0xbdffff97
				) ) > (w)-Pio_4<A0>();
      return p3*cos(xn+x);
    }
  };
} }

#endif
// modified by jt the 05/01/2011

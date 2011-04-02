//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_POW_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_POW_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/negif.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::pow_, tag::cpu_,
                      (A0)(X),
                      ((simd_<arithmetic_<A0>,X>))
                      ((simd_<arithmetic_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::pow_(tag::simd_<tag::arithmetic_, X> ,
                        tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::pow(tofloat(a0), tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::pow_, tag::cpu_,
                      (A0)(X),
                      ((simd_<real_<A0>,X>))
                      ((simd_<real_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::pow_(tag::simd_<tag::real_, X> ,
                        tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 res = exp(a1*log(nt2::abs(a0)));
      A0 isltza0 = is_ltz(a0); 
      return b_or( b_andnot(isltza0, is_flint(a1)),
		   seladd(is_nez(a0),
			  Zero<A0>(),
			  sel(is_eqz(a1),
			      One<A0>(),
			      negif(b_and(is_odd(a1), isltza0),res)
			      )
			  )
		   );
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::pow_, tag::cpu_,
                       (A0)(A1)(X),
                       ((simd_<arithmetic_<A0>,X>))
                       ((simd_<integer_<A1>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::pow_(tag::simd_<tag::arithmetic_, X> ,
                         tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename meta::as_integer<A0, signed>::type int_type;
	typedef typename NT2_RETURN_TYPE(2)::type             r_type;
	r_type a00 =  tofloat(a0); 
        r_type sign_x = bitofsign(a0);
        r_type x = b_xor(a0, sign_x);//x = nt2::abs(a0)
        int_type sign_n = signnz( a1 );
        int_type n = nt2::abs(a1);

        int_type   n_odd = is_odd(n);
        r_type n_oddf = tofloat(-n_odd);
        r_type nf = n_oddf;

        r_type y = madd(n_oddf,x,oneminus(n_oddf));

        r_type w = x;
        n = shri(n,1);
        while( any(n) )
          {
            w =sqr( w);
            n_oddf = tofloat(-is_odd(n));
            y = y*madd(n_oddf,w,oneminus(n_oddf));
            n = shri(n,1);
          }

        w = b_xor(y, sign_x);
        y = madd(nf, w, (oneminus(nf))*y);

        w = rec(y);
        x = tofloat(shri(oneplus(sign_n),1));  // 1 if positiv, else 0
        return madd(x,y,oneminus(x)*w);
    }

  };
} }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is scalar integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::pow_, tag::cpu_,
		      (A0)(A1)(X),
		      ((simd_<arithmetic_<A0>,X>))
		      ((integer_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::pow_(tag::simd_<tag::arithmetic_, X> ,
                         tag::integer_ ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return powi(a0, a1);
    }

  };
} }

#endif
// modified by jt the 05/01/2011

//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_POWI_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SIMD_COMMON_POWI_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/madd.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/any.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::powi_, tag::cpu_,
                       (A0)(A1)(X),
                       ((simd_<arithmetic_<A0>,X>))
                       ((simd_<integer_<A1>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::powi_(tag::simd_(tag::arithmetic_, X),
                         tag::simd_(tag::integer_, X)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        typedef typename meta::as_integer<A0, signed>::type int_type;
        A0 sign_x = bitofsign(a0);
        A0 x = b_xor(a0, sign_x);//x = abs(a0)
        int_type sign_n = signnz( a1 );
        int_type n = abs(a1);

        int_type   n_odd = is_odd(n);
        A0 n_oddf = tofloat(-n_odd);
        A0 nf = n_oddf;

        A0 y = madd(n_oddf,x,oneminus(n_oddf));

        A0 w = x;
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

#endif
// modified by jt the 05/01/2011


//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_POWI_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTION_SCALAR_POWI_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/madd.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/copysign.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::powi_, tag::cpu_,
                      (A0)(A1),
                      (arithmetic_<A0>)(integer_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::powi_(tag::arithmetic_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
      struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type; 
      return powi(type(a0), a1); 
    }

  };
} }

NT2_REGISTER_DISPATCH(tag::powi_, tag::cpu_,
                      (A0)(A1),
                      (real_<A0>)(integer_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::powi_(tag::real_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      bool isodda1 = is_odd(a1); 
      if (is_eqz(a1)) return One<type>(); 
      if (is_eqz(a0)) return (is_gtz(a1)) ? a0 : isodda1 ? rec(a0) : Inf<type>();
      if (is_inf(a0)) return (isodda1) ? a0 : -a0; 
      const type one = One<type>();
      type x = nt2::abs(a0);
      A1 sign_n = signnz(a1);
      A1 n = nt2::abs(a1);

      type n_oddf = is_odd(n);
      type nf = n_oddf;

      type y = madd(n_oddf,x,one-n_oddf);
      type w = x;
      n >>= 1;

      while( n )
      {
        w =sqr( w);
        n_oddf = is_odd(n);
        y = y*madd(n_oddf,w,one-n_oddf);
        n >>=1;
      }

      w = copysign(y, a0);
      y = madd(nf, w, (one-nf)*y);

      w = rec(y);
      x = shri(oneplus(sign_n),1);  // 1 if positive, else 0
      return madd(x,y,(one-x)*w);
    }

  };
} }

#endif
// modified by jt the 26/12/2010

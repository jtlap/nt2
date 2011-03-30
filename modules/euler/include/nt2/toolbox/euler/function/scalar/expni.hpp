//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_EXPNI_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_EXPNI_HPP_INCLUDED
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/gamma.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_odd.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expni_, tag::cpu_,
                       (A0)(A1),
                       (integer_<A0>)(arithmetic_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::expni_(tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return expni(a0, type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::expni_, tag::cpu_,
                       (A0)(A1),
                       (integer_<A0>)(real_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::expni_(tag::integer_,tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      A1 x = a1;
      const int32_t n =  a0;
      if( n < 0 ||  x < 0)      return Nan<A1>();
      if( x > Maxlog<A1>() )    return Zero<A1>();
      if( is_eqz(x) )           return (n < 2) ? Inf<A1>() : rec(n-One<A1>());
      if( n == 0 )              return exp(-x)/x;
      /* Expansion for large n */
      if( n > 5000 )
      {
        A1 xk = x + n;
        A1 yk = rec(sqr(xk));
        A1 t = n;
        A1 ans = yk*t*(Six<A1>()*sqr(x)-Eight<A1>()*t*x+sqr(t));
        ans = yk*(ans+t*(t-Two<A1>()*x));
        ans = yk*(ans+t);
        return oneplus(ans)*exp(-x)/xk;
      }

      if( x <=  One<A1>() )
      {
        /*        Power series expansion        */
        A1 psi = -Euler<A1>() - nt2::log(x);
        for( int32_t i=n-1; i; --i )  psi += rec((A1)i);
	A1 t;
        A1 z = -x;
        A1 xk = Zero<A1>();
        A1 yk = One<A1>();
        A1 pk = One<A1>() - n;
        A1 ans = ( n == 1 ) ? Zero<A1>() : rec(pk);
        do
          {
            xk += One<A1>();
            yk *= z/xk;
            pk += One<A1>();
            if(is_nez(pk)) ans += yk/pk;
            t = is_nez(ans) ? nt2::abs(yk/ans) : One<A1>();
          }
        while( t > Halfeps<A1>() );
        t = n;
        A1 r = n - 1;
        return (pow(z, r) * psi / gamma(t)) - ans;
      }
      /*          continued fraction            */
      int32_t k = 1;
      A1 t;
      A1 pkm2 = One<A1>();
      A1 qkm2 = x;
      A1 pkm1 =  One<A1>();
      A1 qkm1 = x + (A1)n;
      A1 ans = pkm1/qkm1;
      do
      {
        bool test =  is_odd(++k);
        A1 yk = test ? One<A1>() : x;
        A1 xk = test ? n + (k-1)/2 : k/2;
        A1 pk = pkm1 * yk  +  pkm2 * xk;
        A1 qk = qkm1 * yk  +  qkm2 * xk;
        if( is_nez(qk) )
          {
            A1 r = pk/qk;
            t = nt2::abs( (ans - r)/r );
            ans = r;
          }
        else
          {
            t = One<A1>();
          }
        pkm2 = pkm1;
        pkm1 = pk;
        qkm2 = qkm1;
        qkm1 = qk;
        if( nt2::abs(pk) > Expnibig<A1>() )
          {
            pkm2 *= Halfeps<A1>();
            pkm1 *= Halfeps<A1>();
            qkm2 *= Halfeps<A1>();
            qkm1 *= Halfeps<A1>();
          }
      }
      while( t > Halfeps<A1>() );

      return( ans*exp( -x ) );
    }
  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 02/01/2010


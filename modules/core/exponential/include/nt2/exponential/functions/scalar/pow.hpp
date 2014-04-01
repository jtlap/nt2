//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_POW_HPP_INCLUDED
#include <nt2/exponential/functions/pow.hpp>
#include <nt2/exponential/functions/details/pow_kernel.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/log2_em1.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/oneo_16.hpp>
#include <nt2/include/constants/powlargelim.hpp>
#include <nt2/include/constants/powlowlim.hpp>
#include <nt2/include/constants/sixteen.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/floor.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/fms.hpp>
#include <nt2/include/functions/scalar/frexp.hpp>
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/is_gtz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/ldexp.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/pow2.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/shr.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/scalar/is_nan.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/minf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                              (scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_integer<A0>::type  iA0;
      bool ltza0 = is_ltz(a0);
      #ifndef BOOST_SIMD_NO_INFINITIES
      if(a0 == a1 && a0 == Inf<A0>()) return Inf<A0>();
      if( (a0 == a1 && a0 == Minf<A0>()) ||  (ltza0 && !is_flint(a1)) )
      #else
      if( (ltza0 && !is_flint(a1)) )
      #endif
        return Nan<A0>();
      #ifndef BOOST_SIMD_NO_INVALIDS
      if(is_nan(a0) || is_nan(a1)) return Nan<A0>();
      #endif

      typedef typename meta::as_integer<A0>::type iA0;
      iA0 e;
      A0 x = frexp( nt2::abs(a0), e );
      iA0 i  = details::pow_kernel<A0>::select(x);
      A0 z = sqr(x);
      A0 w = details::pow_kernel<A0>::pow1(x, z);
      w = fma(Mhalf<A0>(), z, w);
      w = fma(Log2_em1<A0>(), w, w);
      z = fma(Log2_em1<A0>(), x, w);
      z += x;
      w =  fma(A0(-i), Oneo_16<A0>(), A0(e));
      A0 ya = reduc(a1);
      A0 yb = a1 - ya;
      A0 W = fma(z, a1, w*yb); //z * a1  +  w * yb;
      A0 Wa = reduc(W);
      A0 Wb = W - Wa;
      W = fma(w, ya, Wa); //Wa + w * ya;
      Wa = reduc(W);
      A0 u = W - Wa;
      W = Wb + u;
      Wb = reduc(W);
      w = Sixteen<A0>()*(Wa + Wb);

      // Test the power of 2 for overflow
      if( w > Powlargelim<A0>() ) return Inf<A0>();
      if( w < Powlowlim<A0>()   ) return Zero<A0>();
      e = w;
      Wb = W - Wb;  //
      if( Wb > 0.0f ) //
      {
        ++e;
        Wb -= Oneo_16<A0>(); //
      }
      z = details::pow_kernel<A0>::pow2(Wb)*Wb; //
      i = (e/Sixteen<iA0>()) + (e>=0);
      e = fms(i, Sixteen<iA0>(), e);
      w =  details::pow_kernel<A0>::twomio16(e);
      z = fma(w, z, w);
      z = ldexp( z, i );
      return  (ltza0 && nt2::is_odd(a1)) ? -z : z;
    }
  private :
    static BOOST_FORCEINLINE A0 reduc(const A0& x)
    {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return Oneo_16<A0>()*floor(Sixteen<A0>()*x);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if (is_eqz(a1)) return One<result_type>();
      bool isodda1 = is_odd(a1);
      result_type x = nt2::abs(a0);
      if (is_eqz(a0)) return (is_gtz(a1)) ? a0 : isodda1 ? rec(a0) : Inf<result_type>();
      #ifndef BOOST_SIMD_NO_INFINITIES
      if (x == Inf<A0>()) return (isodda1 && is_ltz(a0)) ? -x : x;
      #endif
      A1 sign_n = signnz(a1);
      A1 n = nt2::abs(a1);

      result_type n_oddf = is_odd(n);
      result_type nf = n_oddf;

      result_type y = fma(n_oddf,x,oneminus(n_oddf));
      result_type w = x;
      n >>= 1;

      while( n )
      {
        w =sqr( w);
        n_oddf = is_odd(n);
        y = y*fma(n_oddf,w,oneminus(n_oddf));
        n >>=1;
      }

      w = copysign(y, a0);
      y = fma(nf, w, (oneminus(nf))*y);

      w = rec(y);
      x = shr(oneplus(sign_n),1);  // 1 if positive, else 0
      return fma(x,y,(oneminus(x))*w);
    }
  };
} }
#endif

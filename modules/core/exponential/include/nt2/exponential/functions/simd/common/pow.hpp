//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_HPP_INCLUDED
#include <nt2/exponential/functions/pow.hpp>
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
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/frexp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_gtz.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/pow2.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/selinc.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/shr.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

#include <boost/dispatch/attributes.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>,X>))
                              ((simd_< floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      bA0 ltza0 = is_ltz(a0);
      bA0 allz = l_and(is_eqz(a0), is_eqz(a1));

      typedef typename meta::as_integer<A0>::type iA0;
      typedef typename boost::mpl::false_     is_simd;
      iA0 e;
      A0 x = frexp( nt2::abs(a0), e );
      iA0 i  = details::pow_kernel<A0>::select(x, is_simd());
      A0 z = sqr(x);
      A0 w = details::pow_kernel<A0>::pow1(x, z);
      w = fma(Mhalf<A0>(), z, w);
      w = fma(Log2_em1<A0>(), w, w);
      z = fma(Log2_em1<A0>(), x, w);
      z += x;
      w =  fma(tofloat(-i), Oneo_16<A0>(), tofloat(e));

      A0 ya = reduc(a1);
      A0 yb = a1 - ya;
      A0 W = fma(z, a1, w*yb); // z * a1  +  w * yb;
      A0 Wa = reduc(W);
      A0 Wb = W - Wa;
      W = fma(w, ya, Wa); // Wa + w * ya;
      Wa = reduc(W);
      A0 u = W - Wa;
      W = Wb + u;
      Wb = reduc(W);
      w = Sixteen<A0>()*(Wa + Wb);

      // Test the power of 2 for over/underflow
      bA0 inf_ret = gt(w, Powlargelim<A0>());
      bA0 zer_ret = lt(w, Powlowlim<A0>());
      e = toint(w);
      Wb = W - Wb;
      bA0 test = is_gtz(Wb);
//      e = seladd(test, e, One<iA0>()); //selinc doesnot work here !
      e = selinc(test, e);
      Wb = selsub(test, Wb, Oneo_16<A0>());

      z = details::pow_kernel<A0>::pow2(Wb)*Wb; //
      i = selinc(is_gtz(e), (e/Sixteen<iA0>()));
      e = (i*Sixteen<iA0>()) - e;
      w =  details::pow_kernel<A0>::Twomio16(e, is_simd());
      z = fma(w, z, w);      //   2**-e * ( 1 + (2**Wb-1) )
      z = ldexp( z, i );  //   multiply by integer power of 2

      z =  negif(l_and(is_odd(a1), ltza0), z);
      bA0 invalid =  l_and(ltza0, l_not( is_flint(a1)));
      #ifndef BOOST_SIMD_NO_INFINITIES
      z =  if_else(l_and(eq(a0, Inf<A0>()), eq(a1, Inf<A0>())), a0, z);
      #endif
      z = if_zero_else(zer_ret, z);
      z = if_else(inf_ret, Inf<A0>(), z);
      return if_else(invalid, Nan<result_type>(), if_else(allz, One<A0>(), z));
    }
  private :
    static BOOST_FORCEINLINE A0 reduc(const A0& x)
    {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return Oneo_16<A0>()*floor(Sixteen<A0>()*x);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((simd_<integer_<A1>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
        typedef A1                    int_type;
        typedef result_type             r_type;
        r_type a00 =  tofloat(a0);
        r_type sign_x = bitofsign(a00);
        r_type x = b_xor(a00, sign_x);
        int_type sign_n = signnz( a1 );
        int_type n = nt2::abs(a1);
        r_type n_oddf = if_else_zero(is_odd(n), One<r_type>());
        r_type nf = n_oddf;
        r_type y = fma(n_oddf,x,oneminus(n_oddf));
        r_type w = x;
        n = shri(n,1);
        while( nt2::any(n) )
        {
          w =sqr(w);
          n_oddf = if_else_zero(is_odd(n), One<r_type>());
          y = y*fma(n_oddf,w,oneminus(n_oddf));
          n = shri(n,1);
        }

        w = b_xor(y, sign_x);
        y = fma(nf, w, (oneminus(nf))*y);

        w = rec(y);
        x = tofloat(shri(oneplus(sign_n),1));  // 1 if positive, else 0
        r_type r = if_else(is_even(a1), nt2::abs(a00), a00);
        A0 r1 = fma(x,y,oneminus(x)*w);
        #ifndef BOOST_SIMD_NO_INFINITIES
        r1 =  if_else(is_inf(a00), if_else(is_gtz(a1), r, rec(r)), r1);
        #endif
        #ifndef BOOST_SIMD_NO_INVALIDS
        r1 =  if_nan_else(is_nan(a00), r1);
        #endif
        return r1;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))
                              ((scalar_<integer_<A1> >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
        result_type sign_x = bitofsign(a0);
        result_type x = b_xor(a0, sign_x);
        if (is_even(a1)) sign_x = Zero<result_type>();
        A1 n = nt2::abs(a1);
        result_type ret = One<result_type>();
        for(A1 t = n; t > 0; t >>= 1)
        {
          if(is_odd(t)) ret*=x;
          x = sqr(x);
        }
        x =  b_xor(ret, sign_x);
        return is_ltz(a1) ? rec(x) : x;
    }
  };
} }

#endif

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
#include <nt2/exponential/functions/details/pow_kernel.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/is_odd.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/pow_abs.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/shr.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/is_gtz.hpp>
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
      A0 z = pow_abs(a0, a1);
      z =  negif(l_and(is_odd(a1), ltza0), z);
      bA0 invalid =  l_andnot(ltza0, is_flint(a1));
      return if_else(invalid, Nan<result_type>(), z);
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

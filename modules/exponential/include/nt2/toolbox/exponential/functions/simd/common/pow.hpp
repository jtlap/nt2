//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_POW_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_nez.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else_zero.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/powi.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::pow(tofloat(a0), tofloat(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename meta::as_logical<A0>::type                 bA0;
      bA0 isltza0 = is_ltz(a0);
      bA0 allz = l_and(is_eqz(a0), is_eqz(a1));
      A0 res =  exp(a1*log(nt2::abs(a0)));
      res =  select(l_and(is_odd(a1), isltza0), -res, res);
      //     bA0 invalid =  logical_andnot(isltza0, is_flint(a1));
      bA0 invalid =  l_and(isltza0, logical_not( is_flint(a1)));
      return select(invalid, Nan<result_type>(), select(allz, One<A0>(), res));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))((simd_<integer_<A1>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
        typedef A1                    int_type;
        typedef result_type             r_type;
        r_type a00 =  tofloat(a0);
        r_type sign_x = bitofsign(a00);
        r_type x = b_xor(a00, sign_x);//x = nt2::abs(a0)
        int_type sign_n = signnz( a1 );
        int_type n = nt2::abs(a1);
        r_type n_oddf = if_else_zero(is_odd(n), One<r_type>());
        r_type nf = n_oddf;
        r_type y = madd(n_oddf,x,oneminus(n_oddf));
        r_type w = x;
        n = shri(n,1);
        while( nt2::any(n) )
        {
          w =sqr(w);
          n_oddf = if_else_zero(is_odd(n), One<r_type>());
          y = y*madd(n_oddf,w,oneminus(n_oddf));
          n = shri(n,1);
        }

        w = b_xor(y, sign_x);
        y = madd(nf, w, (oneminus(nf))*y);

        w = rec(y);
        x = tofloat(shri(oneplus(sign_n),1));  // 1 if positive, else 0
        r_type r = sel(is_even(a1), nt2::abs(a00), a00);
        return if_nan_else(is_nan(a00), sel(is_inf(a00), sel(is_gtz(a1), r, rec(r)), madd(x,y,oneminus(x)*w)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is scalar integer_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))(scalar_< integer_<A1> >)
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return powi(a0, a1);
    }
  };
} }

#endif

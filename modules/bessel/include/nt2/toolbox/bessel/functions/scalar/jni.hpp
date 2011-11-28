//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BESSEL_FUNCTIONS_SCALAR_JNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTIONS_SCALAR_JNI_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/j0.hpp>
#include <nt2/include/functions/j1.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/splat.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::jni(a0, result_type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< double_<A1> >)
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
        return ::jn(a0, a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< single_<A1> >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      result_type x = a1;
      const int32_t n1 = nt2::abs(a0);
      result_type sign = a0<Zero<A0>()?cospi(n1):One<A0>();
      if( n1 == 0 )
        return( sign * nt2::j0(x) );
      if( n1 == 1 )
        return( sign * nt2::j1(x) );
      if( n1 == 2 )
        return mul(sign, (mul(Two<result_type>(), nt2::j1(x) / x)  -  nt2::j0(x)) );

      /* continued fraction */
      int k = 24;
      result_type pk = Two<result_type>()*(result_type(n1) + result_type(k));
      result_type ans = pk;
      result_type xk = sqr(x);
      do {
        pk  = pk - Two<result_type>();
        ans = pk - (xk/ans);
      }
      while( --k > 0 );
      /* backward recurrence */

      pk = One<result_type>();
      /*pkm1 = 1.0/ans;*/
      result_type xinv = rec(x);
      result_type pkm1 = ans * xinv;
      k = n1-1;
      result_type r = 2.0f*k;

      do{
        const result_type pkm2 = (pkm1 * r  -  pk * x) * xinv;
        pk = pkm1;
        pkm1 = pkm2;
        r -= Two<result_type>();
      }
      while( --k > 0 );
      return sign*select(gt(abs(pk), nt2::abs(pkm1)),nt2::j1(x)/pk, nt2::j0(x)/pkm1);
      //     return ::jnf(a0, a1);
    }
  };
} }


#endif

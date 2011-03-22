//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_YNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SIMD_COMMON_YNI_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/y0.hpp>
#include <nt2/include/functions/y1.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_ltz.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::yni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((integer_<A0>))
                      ((simd_<arithmetic_<A1>,X> ))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::yni_(tag::integer_,
                        tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::as_real<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::yni(a0, tofloat(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::yni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((integer_<A0>))
                      ((simd_<double_<A1>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::yni_(tag::integer_,
	                tag::simd_<tag::double_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      const A1 r = {{yni(a0, a1[0]),yni(a0, a1[1])}} ;
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::yni_, tag::cpu_,
                      (A0)(A1)(X),
                      ((integer_<A0>))
                      ((simd_<float_<A1>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::yni_(tag::integer_,
                        tag::simd_<tag::float_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :  meta::strip<A1>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef A1 result_type;
      result_type x = a1;
      const int32_t n1 = nt2::abs(a0);
      result_type sign = splat<result_type>((a0<0)?cospi(n1):1);
      if( n1 == 0 ) return( sign * y0(x) );
      if( n1 == 1 ) return( sign * y1(x) );
      result_type an1 = splat<result_type>(n1);
      /* forward recurrence on n */

      result_type anm2 = y0(x);
      result_type anm1 = y1(x);
      int32_t k = 1;
      result_type r = splat<result_type>(k << 1);
      result_type xinv = rec(x);
      result_type an;
      do
        {
          an = r*anm1*xinv-anm2;
          anm2 = anm1;
          anm1 = an;
          r +=Two<result_type>();
          ++k;
        }
      while( k < n1 );
      return b_or(is_ltz(a1),sign*an);
    }
  };
} }

#endif
// modified by jt the 05/01/2011

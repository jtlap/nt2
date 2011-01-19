//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BESSEL_FUNCTION_SCALAR_YNI_HPP_INCLUDED
#define NT2_TOOLBOX_BESSEL_FUNCTION_SCALAR_YNI_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::yni_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(arithmetic_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::yni_(tag::integer_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return nt2::yni(a0, type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::yni_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(double_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::yni_(tag::integer_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
        return ::yn(a0, a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::yni_, tag::cpu_,
                     (A0)(A1),
                     (integer_<A0>)(float_<A1>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::yni_(tag::integer_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef A1 result_type;
      if (isltz(a1)) return Nan<result_type>();
      result_type x = a1;
      const int32_t n1 = abs(a0);
      result_type sign = a0<0?nt2::cospi(n1):1;
      if( n1 == 0 )
      return( sign * y0(x) );
      if( n1 == 1 )
      return( sign * y1(x) );
      if( n1 == 2 )
      return mul(sign, (mul(Two<result_type>(), j1(x) / x)  -  j0(x)) );
      result_type an1 = n1;
      result_type res1 = an1*log(an1/x);
      if ((x < 1.0) || (n1 > 29))
      return  res1;
      /* forward recurrence on n */

      result_type anm2 = y0(x);
      result_type anm1 = y1(x);
      int32_t k = 1;
      result_type r = k << 1;
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
      return sign*an;
      //     return ::ynf(a0, a1);
    }
  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 26/12/2010

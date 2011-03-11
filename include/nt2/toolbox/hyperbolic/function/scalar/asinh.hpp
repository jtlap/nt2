//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_ASINH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTION_SCALAR_ASINH_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/negate.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/rec.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asinh_, tag::cpu_,
                       (A0),
                       (arithmetic_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asinh_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asinh(nt2::tofloat(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asinh_, tag::cpu_,
                       (A0),
                       (double_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asinh_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      A0 x = nt2::abs(a0);
      if (x < Sqrteps<A0>() ) return a0;
      if (x*Sqrteps<A0>() >=  One<A0>()) return sign(a0)*(log1p(x)+Log_2<A0>());
      A0 invx = rec(x);
      return sign(a0)*log1p(x + x/(invx + sqrt(One<A0>()+invx*invx)) );

      //         asinh(x) := x  if  1+x*x=1,
      //  *               := sign(x)*(log1p(x)+ln2))      if sqrt(1+x*x)=x, else
      //  *               := sign(x)*log1p(|x| + |x|/(1/|x| + sqrt(1+(1/|x|)^2)) )
      //  *

    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::asinh_, tag::cpu_,
                       (A0),
                       (float_<A0>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::asinh_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> :
      std::tr1::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      A0 x = nt2::abs(a0);
      if (x < Sqrteps<A0>() )
      return a0;
      if (abs(a0) <  Half<A0>() )
      {
        A0 z =  sqr(a0);
        A0 n = a0*horner< NT2_HORNER_COEFF_T(A0, 4, (0x3b82db62,
                                            0xbd02b78b,
                                            0x3ef2d9f5,
                                            0x3f7fffff
                                            )) > (z);
        A0 d = horner< NT2_HORNER_COEFF_T(A0, 2, (0x3f24175a,
                                           0x3f800000
                                           )) > (z);
          return n/d;
        }
      return negate(nt2::log(x+nt2::sqrt(sqr(x)+One<type>())), a0); //TODO better eval
    }
  };
} }

#endif
// modified by jt the 26/12/2010
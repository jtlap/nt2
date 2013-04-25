//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ASINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ASINH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/asinh.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/scalar/negate.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sign.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/sqrteps.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::asinh(nt2::tofloat(a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 x = nt2::abs(a0);
      if (x < nt2::Sqrteps<A0>() ) return a0;
      if (x*nt2::Sqrteps<A0>() >=  nt2::One<A0>()) return nt2::sign(a0)*(nt2::log1p(x)+nt2::Log_2<A0>());
      A0 invx = nt2::rec(x);
      return nt2::sign(a0)*nt2::log1p(x + x/(invx + nt2::sqrt(nt2::One<A0>()+invx*invx)) );

      //         asinh(x) := x  if  1+x*x=1,
      //  *               := sign(x)*(log1p(x)+ln2))      if sqrt(1+x*x)=x, else
      //  *               := sign(x)*log1p(|x| + |x|/(1/|x| + sqrt(1+(1/|x|)^2)) )
      //  *

    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 x = nt2::abs(a0);
      if (x < nt2::Sqrteps<A0>() )
      return a0;
      if (nt2::abs(a0) <  nt2::Half<A0>() )
      {
        A0 z =  nt2::sqr(a0);
        A0 n = a0*nt2::horner< NT2_HORNER_COEFF_T(A0, 4, (0x3b82db62,
                                                     0xbd02b78b,
                                                     0x3ef2d9f5,
                                                     0x3f7fffff
                                                    )) > (z);
        A0 d = nt2::horner< NT2_HORNER_COEFF_T(A0, 2, (0x3f24175a,
                                                  0x3f800000
                                                 )) > (z);
          return n/d;
        }
      return nt2::negate(nt2::log(x+nt2::sqrt(x*x+nt2::One<A0>())), a0); //TODO better eval
    }
  };
} }


#endif

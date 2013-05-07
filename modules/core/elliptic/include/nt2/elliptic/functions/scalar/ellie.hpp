//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLIE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SCALAR_ELLIE_HPP_INCLUDED
#include <nt2/elliptic/functions/ellie.hpp>
#include <boost/math/special_functions.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/sin.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/sin.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/tan.hpp>
#include <nt2/include/functions/scalar/atan.hpp>
#include <nt2/include/functions/scalar/average.hpp>
#include <nt2/include/functions/scalar/ellpe.hpp>
#include <nt2/include/functions/scalar/ellpk.hpp>
#include <nt2/include/functions/scalar/ceil.hpp>
#include <nt2/sdk/error/policies.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/eps.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellie_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                              (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ellie(result_type(a0), result_type(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellie_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type type;
      if (a1>nt2::One<A0>()||(nt2::is_ltz(a1))) return Nan<type>();
      if (nt2::is_eqz(a1))  return type(a0);
      return boost::math::ellint_2(nt2::sqrt(type(a1)), type(a0), nt2_policy());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellie_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                              (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type type;
      if (a1>nt2::One<A0>()||(nt2::is_ltz(a1))) return nt2::Nan<type>();
      else if (nt2::is_eqz(a1))
        return a0;
      else if (a1 == nt2::One<A0>())
        return nt2::sin(a0);
      else
      {
        type lphi = nt2::abs(a0);
        type m   =  a1;
        type a = nt2::One<type>();
        type b = nt2::sqrt(nt2::oneminus(m));
        type c = nt2::sqrt(m);
        type d = nt2::One<type>();
        type e = nt2::Zero<type>();
        type t = nt2::tan( lphi );
        int mod = toint((lphi+nt2::Pio_2<type>())/nt2::Pi<type>());
        while( nt2::abs(c) > nt2::Eps<type>()*nt2::abs(a) )
        {
          type temp = b/a;
          lphi = lphi + nt2::atan(t*temp) + mod * nt2::Pi<type>();
          mod = nt2::toint((lphi+nt2::Pio_2<type>())/Pi<type>());
          t *= nt2::oneplus(temp)/( nt2::oneminus(temp * nt2::sqr(t)));
          c = nt2::average(a,-b);
          temp = nt2::sqrt(a*b);
          a = nt2::average(a,b);
          b = temp;
          d += d;
          e += c*nt2::sin(lphi);
        }

        b = nt2::oneminus(m);
        type temp = nt2::ellpe(b)/nt2::ellpk(b);
        temp *= (nt2::atan(t) + mod * nt2::Pi<type>())/(d * a);
        temp += e;
        if(nt2::is_ltz(a0))  temp = -temp;
        return temp ;
      }
      }
  };
} }


#endif

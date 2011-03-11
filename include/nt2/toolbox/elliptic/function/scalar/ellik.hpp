//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLIK_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLIK_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/sdk/constant/eps_related.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/average.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellik_, tag::cpu_,
                       (A0)(A1),
                       (arithmetic_<A0>)(arithmetic_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellik_(tag::arithmetic_,tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      return ellik(type(a0), type(a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellik_, tag::cpu_,
                       (A0)(A1),
                       (double_<A0>)(double_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellik_(tag::double_,tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      if (a1>One<A1>()||(is_ltz(a1))) return Nan<type>();
      if (is_eqz(a1))  return type(a0);
      return boost::math::ellint_1(nt2::sqrt(a1), a0);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellik_, tag::cpu_,
                       (A0)(A1),
                       (float_<A0>)(float_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellik_(tag::float_,tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      std::tr1::result_of<meta::floating(A0,A1)>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      if (a1>One<A1>()||(is_ltz(a1))) return Nan<type>();
      if (is_eqz(a1))  return a0;
      type phi = nt2::abs(a0);
      type m = a1;
      type a = 1.0;
      type b = oneminus(m);
      if( is_eqz(b) )   return nt2::log(nt2::tan(nt2::average(Pio_2<type>(),phi)));
      b = nt2::sqrt(b);
      type c = nt2::sqrt(m);
      int d = 1;
      type t = nt2::tan(phi);
      int mod = (phi + Pio_2<type>())/Pi<type>();
      while( nt2::abs(c) > nt2::abs(a)*Eps<type>() )
      {
        type temp = b/a;
        phi += nt2::atan(t*temp) + mod*Pi<type>();
        mod = (phi + Pio_2<type>())/Pi<type>();
        t = t*oneplus(temp)/( oneminus(temp*t*t));
        c = average(a,-b);
        temp = nt2::sqrt(a*b);
        a = average(a,b);
        b = temp;
        d += d;
      }
      type temp = (atan(t) + mod * Pi<type>())/(d * a);
      if( is_ltz(a0) )  temp = -temp;
      return temp;
    }
  };
} }

#endif
// modified by jt the 26/12/2010
//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLIK_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLIK_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>

#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/average.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ellik_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0,A1)>::type result_type;

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
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ellik_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< double_<A0> >)(scalar_< double_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0,A1)>::type result_type;

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
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ellik_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< float_<A0> >)(scalar_< float_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0,A1)>::type result_type;

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

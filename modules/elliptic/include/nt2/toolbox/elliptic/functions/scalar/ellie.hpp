//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SCALAR_ELLIE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTIONS_SCALAR_ELLIE_HPP_INCLUDED
#include <boost/math/special_functions.hpp>
#include <nt2/include/constants/eps_related.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/tan.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/ellpe.hpp>
#include <nt2/include/functions/ellpk.hpp>
#include <nt2/include/functions/ceil.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellie_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0)>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ellie(result_type(a0), result_type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellie_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)(scalar_< double_<A0> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0)>::type result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type type;
      if (a1>One<A0>()||(is_ltz(a1))) return Nan<type>();
      if (is_eqz(a1))  return type(a0);
      return boost::math::ellint_2(nt2::sqrt(type(a1)), type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellie_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)(scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type type;
      if (a1>One<A0>()||(is_ltz(a1))) return Nan<type>();
      else if (is_eqz(a1))
      return a0;
      else if (a1 == One<A0>())
      return nt2::sin(a0);
      else
      {
        type lphi = nt2::abs(a0);
        type m   =  a1;
        type a = One<type>();
        type b = nt2::sqrt(oneminus(m));
        type c = nt2::sqrt(m);
        type d = One<type>();
        type e = Zero<type>();
        type t = nt2::tan( lphi );
        int mod = toint((lphi+Pio_2<type>())/Pi<type>());
        while( nt2::abs(c) > Eps<type>()*nt2::abs(a) )
          {
            type temp = b/a;
            lphi = lphi + nt2::atan(t*temp) + mod * Pi<type>();
             mod = toint((lphi+Pio_2<type>())/Pi<type>());
            t *= oneplus(temp)/( oneminus(temp * sqr(t)));
            c = average(a,-b);
            temp = nt2::sqrt(a*b);
            a = nt2::average(a,b);
            b = temp;
            d += d;
            e += c*nt2::sin(lphi);
          }

        b = oneminus(m);
        type temp = nt2::ellpe(b)/nt2::ellpk(b);
        temp *= (nt2::atan(t) + mod * Pi < type>())/(d * a);
        temp += e;
        if(is_ltz(a0))  temp = -temp;
        return temp ;
      }
      }
  };
} }


#endif

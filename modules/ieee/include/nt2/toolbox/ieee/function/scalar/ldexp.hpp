//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_LDEXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_LDEXP_HPP_INCLUDED
#include <nt2/include/constants/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/real.hpp>

#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ldexp_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
        return (a1>0)?(a0<<a1):(a0>>a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::ldexp_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< integer_<A1> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename NT2_RETURN_TYPE(2)::type result_type;
      typedef typename meta::as_integer<result_type, unsigned>::type          int_type;

      //  static int_type const nmb = Nbmantissabits<result_type>();
      //      static int_type const n1  = ((2*(Maxexponent<result_type>()-1)+3) << nmb);

      // clear exponent in x
      result_type const x(b_andnot(a0, Ldexpmask<result_type>()));

      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<result_type>(), a0);
      e += int_type(a1) << Nbmantissabits<result_type>(); //nmb;
      if (is_nez(a0)&&is_finite(a0)) return  b_or(x, e);
      return a0;
    }
  };
} }


#endif

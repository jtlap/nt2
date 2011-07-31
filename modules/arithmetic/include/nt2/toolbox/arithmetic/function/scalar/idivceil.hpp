//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IDIVCEIL_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IDIVCEIL_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/rdivide.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/sdk/meta/as_real.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivceil_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::result_of<meta::floating(result_type)>::type ftype;
      ftype r = ceil(ftype(a0)/ftype(a1));
      if (r > Valmax<result_type>()) return Valmax<result_type>();
      else if (r <  Valmin<result_type>()) return Valmin<result_type>();
      else return result_type(r); 
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( tag::idivceil_, tag::cpu_
			      , (A0)(A1)
			      , (scalar_< unsigned_<A0> >)(scalar_< unsigned_<A1> >)
			      )
  {
    
    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;
    
    NT2_FUNCTOR_CALL(2)
      {
	return (a1) ? rdivide((a0+(a1-One<result_type>())), a1) : Valmax<result_type>();
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(tag::idivceil_, tag::cpu_,
			     (A0)(A1),
			     (scalar_< real_<A0> >)(scalar_< real_<A1> > )
			     )
  {
    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type typ;
    typedef typename meta::as_integer<typ>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return iceil(a0/a1);
    }
  };
} }

#endif

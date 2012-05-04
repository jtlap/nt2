//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SCALAR_ASECH_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_FUNCTIONS_SCALAR_ASECH_HPP_INCLUDED

#include <nt2/include/functions/scalar/acosh.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asech_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef result_type type;
      if (is_eqz(a0)) return Inf<type>();
      if (a0 ==  One<A0>()) return Zero<type>();
      return Nan<type>(); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asech_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (a0 > One<A0>() || a0 < Zero<A0>()) return Nan<A0>();
      if (a0 == Zero<A0>()) return Inf<A0>();
      return acosh(rec(a0)); 
//      type t = minusone(rec(a0));
//       if (t < 16*Sqrteps<A0>()){
// 	return sqrt(Two<A0>()*t)*(oneplus(t/12+3*sqr(t)/160)); //1 + t /12 + 3 * t*t / 160
//       }
//       return nt2::log1p(t+nt2::sqrt((t+t)+sqr(t)));
    }
  };
} }

  
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asech_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (a0 > One<A0>() || a0 < Zero<A0>()) return Nan<A0>();
      if (a0 == Zero<A0>()) return Inf<A0>();
      A0 tmp =  oneminus(a0);
      if (tmp <= 0.01f) {
	A0 f = 1.0f+tmp*(0.41666665982f+tmp*(0.26875436672f+tmp*(0.19711170102f+tmp* 0.16913685372f))); 
	return f*nt2::sqrt(2.0f*tmp);
      }
      return acosh(rec(a0)); 

    }
  };
} }

#endif

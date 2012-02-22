//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_ACOTD_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_SCALAR_ACOTD_HPP_INCLUDED
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/atand.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/bitwise_or.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acotd_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
	  A0 s = bitofsign(a0);
	  if(!a0)  return b_or(_90<A0>(), s);
	  if(is_inf(a0)) return b_or(Zero<A0>(), s);
	  return b_or(_90<A0>()-atand(abs(a0)), s);
	}
  };
} }


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acotd_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
	if(!a0)  return Zero<result_type>();
	return nt2::acotd(result_type(a0));
      }
  };
} }


#endif

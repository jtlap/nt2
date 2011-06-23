//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IROUND2EVEN_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_IROUND2EVEN_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/constants/properties.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/round.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_nan.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::iround2even_, tag::cpu_
                            , (A0)
                            , (scalar_< fundamental_<A0> >)
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} }


namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::iround2even_, tag::cpu_
                            , (A0)
                            , (scalar_< real_<A0> >)
                            )
  {

    typedef typename meta::as_integer<A0, signed>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type rtype; 
      if (is_inf(a0))
	{
	  if (is_ltz(a0))
	    return Valmin<rtype>(); 
	  else
	    return Valmax<rtype>();
	}
      if (is_nan(a0)) return Zero<rtype>(); 
      return round(a0);
    }
  };
} }


#endif

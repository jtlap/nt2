//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SATURATE_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_SATURATE_HPP_INCLUDED
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/properties.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::saturate_<T> , tag::cpu_,
                      (A0)(T),
                      (scalar_<integer_<A0> >)
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      if (a0 > Valmax<T>())
	return Valmax<T>();
      else if (a0 <  Valmin<T>())
 	return Valmin<T>();
      else
	return a0; 
    }
  };
  
} }
#endif

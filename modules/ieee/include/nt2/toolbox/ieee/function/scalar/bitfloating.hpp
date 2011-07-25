//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SCALAR_BITFLOATING_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/include/constants/digits.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::bitfloating_, tag::cpu_,
                             (A0),
                             (scalar_<arithmetic_<A0> > )
                            )
  {
 typedef typename meta::as_real<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return a0 >= Zero<A0>() ?
	bitwise_cast<result_type>(a0) :
	bitwise_cast<result_type>((One<A0>() << (8*sizeof(A0)-1))-a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////


  NT2_FUNCTOR_IMPLEMENTATION(tag::bitfloating_, tag::cpu_,
                             (A0),
                             (scalar_<unsigned_<A0> > )
                            )
  {
    typedef typename meta::as_real<A0>::type result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return bitwise_cast<result_type>(a0); 
    }
  };
} }
#endif

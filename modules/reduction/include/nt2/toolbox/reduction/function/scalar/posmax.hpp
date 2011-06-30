//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_POSMAX_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_POSMAX_HPP_INCLUDED
#include <nt2/sdk/details/ignore_unused.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::posmax_, tag::cpu_,
                        (A0),
                        (scalar_<fundamental_<A0> > )
                       )
  {
      typedef typename meta::as_integer<A0, signed>::type result_type;
    
    NT2_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return 0;
    }
  };
} }
#endif

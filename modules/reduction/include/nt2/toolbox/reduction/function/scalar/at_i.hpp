//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_AT_I_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SCALAR_AT_I_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION(tag::at_i_, tag::cpu_,
                    (A0)(A1),
                    (scalar_<fundamental_<A0> > )(scalar_ < integer_<A1> > )
                   )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      ignore_unused(a1);
      return a0;
    };
  };
} }
#endif

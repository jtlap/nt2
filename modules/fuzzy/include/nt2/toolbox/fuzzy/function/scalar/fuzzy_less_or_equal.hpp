//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_FUZZY_LESS_OR_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SCALAR_FUZZY_LESS_OR_EQUAL_HPP_INCLUDED

#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fuzzy_less_or_equal_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)(scalar_< real_<A2> >)
                            )
  {

    typedef bool result_type;

    NT2_FUNCTOR_CALL(3)
    {
       return a0 <= a1+a2*nt2::max(nt2::abs(a0),nt2::abs(a1));
    }
  };
} }


#endif

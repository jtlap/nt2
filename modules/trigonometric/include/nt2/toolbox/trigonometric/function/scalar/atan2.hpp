//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SCALAR_ATAN2_HPP_INCLUDED
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>
#include <nt2/toolbox/predicates/include/is_invalid.hpp>
#include <cmath>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::atan2_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::floating(A0,A1)>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if (is_invalid(a0) && is_invalid(a1)) return Nan<result_type>(); 
      return std::atan2(result_type(a0),result_type(a1));
    }
  };
} }


#endif

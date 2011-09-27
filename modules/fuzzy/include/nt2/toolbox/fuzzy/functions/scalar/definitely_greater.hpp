//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_FUZZY_FUNCTIONS_SCALAR_DEFINITELY_GREATER_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTIONS_SCALAR_DEFINITELY_GREATER_HPP_INCLUDED

#include <nt2/include/functions/is_ord.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/bitwise_and.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::definitely_greater_, tag::cpu_
                            , (A0)
                            , (scalar_< integer_<A0> >)(scalar_< integer_<A0> >)(scalar_< integer_<A0> >)
                            )
  {
    typedef bool result_type;
    NT2_FUNCTOR_CALL_REPEAT(3)
    {
      return (a0 > a1+nt2::abs(a2));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::definitely_greater_, tag::cpu_
			      , (A0)(A2)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)(scalar_< integer_<A2> >)
                            )
  {
    typedef bool result_type;
    inline A0 operator()(const A0& a0,const A0& a1, const A2& a2)
    {
      return b_and(
               is_ord(a0, a1),
               gt(a0, successor(a1, nt2::abs(a2)))
               );
    }
  };
} }


#endif

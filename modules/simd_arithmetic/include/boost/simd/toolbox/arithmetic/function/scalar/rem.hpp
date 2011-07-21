//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_REM_HPP_INCLUDED

#include <boost/simd/include/functions/idivfix.hpp>

/////////////////////////////////////////////////////////////////////////////
//  The rem function computes the floating-point remainder of dividing x by y.
//  The return value is x - n * y, where n is the quotient of x / y, rounded
//  toward zero to an integer.
//  The fmod function is just an alias for the same thing.
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::rem_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      if (a1) return a0%a1; else return a0;  
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::rem_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      if (a1) return a0-a1*idivfix(a0,a1);  else return a0;
    }
  };
} } }


#endif

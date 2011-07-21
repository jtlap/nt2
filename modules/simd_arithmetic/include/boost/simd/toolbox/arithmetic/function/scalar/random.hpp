//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_RANDOM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_RANDOM_HPP_INCLUDED
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/include/functions/iround.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::random_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      return iround((a1-a0)*((double)rand()/RAND_MAX)+a0); //TO DO
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::random_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< real_<A0> >)(scalar_< real_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      return (a1-a0)*((double)rand()/RAND_MAX)+a0; //TO DO
    }
  };
} } }


#endif

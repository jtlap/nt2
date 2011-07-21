//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_MAXMAG_HPP_INCLUDED

#include <boost/simd/include/functions/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::maxmag_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)(scalar_< fundamental_<A1> >)
                            )
  {

    typedef typename meta::result_of<meta::arithmetic(A0,A1)>::type result_type;

    BOOST_DISPATCH_FUNCTOR_CALL(2)
    {
      return (boost::simd::abs(a0) > boost::simd::abs(a1)) ? a0 : a1;
    }
  };
} } }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SCALAR_POSMIN_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTION_SCALAR_POSMIN_HPP_INCLUDED
#include <boost/simd/sdk/details/ignore_unused.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is fundamental_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::posmin_, tag::cpu_,
                        (A0),
                        (scalar_<fundamental_<A0> > )
                       )
  {
      typedef typename meta::as_integer<A0, signed>::type result_type;
    
    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      ignore_unused(a0);
      return 0;
    }
  };
} } }
#endif

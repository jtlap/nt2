//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SCALAR_SATURATE_HPP_INCLUDED
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/functor/forward.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_at_<Tag>
                                   , tag::cpu_
                                   , (A0)(Tag)
                                   , (scalar_<arithmetic_<A0> >)
                                   )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typename boost::simd::make_functor<Tag, A0>::type callee; 
      const A0 z = callee( as_<A0>() );
      if      (a0 > z)  return z;
      else if (a0 < -z) return -z;
      else              return a0; 
    }
  };
  
} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SATURATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SCALAR_SATURATE_HPP_INCLUDED
#include <boost/simd/toolbox/ieee/functions/saturate.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/properties.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_<T> , tag::cpu_,
                      (A0)(T),
                      (scalar_<integer_<A0> >)
                     )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      if (a0 > Valmax<T>())
	  return Valmax<T>();
      else if (a0 <  Valmin<T>())
 	  return Valmin<T>();
      else
	  return a0; 
    }
  };
} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/sdk/meta/strip.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/any.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace meta
{
  //TODO A0 == A1
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(tag::comparator_, tag::cpu_,
                             (A0)(A1)(A2)(X),
                             ((simd_<arithmetic_<A0>,X>))
                             ((simd_<arithmetic_<A1>,X>))
                             ((scalar_<integer_<A2> >))
                            )
  {
    typedef typename meta::strip<A0>::type                       nA0;
    typedef boost::fusion::vector<nA0,nA0,int>           result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      typedef result_type r_t;
      r_t res;
      if (a2)
	{
	  boost::fusion::at_c<1>(res) =  boost::simd::min(a0, a1);
	  boost::fusion::at_c<0>(res) =  boost::simd::max(a0, a1);
	}
      else
	{
	  boost::fusion::at_c<0>(res) =  boost::simd::min(a0, a1);
	  boost::fusion::at_c<1>(res) =  boost::simd::max(a0, a1);
	}
      boost::fusion::at_c<2>(res) = boost::simd::any(a0-boost::fusion::at_c<0>(res)); 
      return res; 
    }
  };
} } }
#endif

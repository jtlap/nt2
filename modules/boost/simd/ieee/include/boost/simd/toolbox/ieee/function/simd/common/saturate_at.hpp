//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SATURATE_AT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_SATURATE_AT_HPP_INCLUDED
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/functions/select.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(boost::simd::tag::saturate_at_<Tag>,
					tag::cpu_,
					(A0)(Tag)(X),
					((simd_<arithmetic_<A0>,X>))
					)
  {
    typedef A0 result_type;
    BOOST_DISPATCH_FUNCTOR_CALL(1)
    {
      return sel(gt(a0, boost::simd::functor<Tag>()),
		 boost::simd::functor<Tag>(),
		 boost::simd::sel(lt(a0,-boost::simd::functor<Tag>()),
				  -boost::simd::functor<Tag>(),
				  a0)
		 ); 
    }
  };
} } }
#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REMAINDER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_REMAINDER_HPP_INCLUDED
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/negate.hpp>
#include <boost/simd/include/functions/select.hpp>
#include <boost/simd/include/functions/idivround.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(tag::remainder_, tag::cpu_,
			     (A0)(X),
			     ((simd_<arithmetic_<A0>,X>))
			     ((simd_<arithmetic_<A0>,X>))
			     )
  {
    typedef A0 result_type; 
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
      {
	return a0-idivround(a0, a1)*a1; 
      }
    
  };
  
  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is real_
  /////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( tag::remainder_, tag::cpu_
			      , (A0)(X)
			      , ((simd_<real_<A0>,X>))((simd_<real_<A0>,X>))
			      )
  {
    
    typedef A0 result_type;
    
    BOOST_DISPATCH_FUNCTOR_CALL_REPEAT(2)
      {
	return b_or(is_invalid(a0), b_or(is_eqz(a1), a0-tofloat(idivround(a0, a1))*a1)); 
      }
  };
} } }


#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEXT_HPP_INCLUDED

#include <boost/simd/toolbox/ieee/functions/next.hpp>
#include <boost/simd/include/functions/oneplus.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/bitinteger.hpp>
#include <boost/simd/include/functions/bitfloating.hpp>
#include <boost/simd/include/functions/oneplus.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/one.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::next_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return oneplus(a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::next_, tag::cpu_,
                       (A0)(X),
                       ((simd_<floating_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return select(eq(a0, Inf<A0>()), a0,  bitfloating(oneplus(bitinteger(a0))));
    }
  };
} } }
#endif

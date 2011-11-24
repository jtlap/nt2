//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_NEGATE_HPP_INCLUDED
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/is_nan.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::negate_, tag::cpu_,
                         (A0)(X),
                         ((simd_<arithmetic_<A0>,X>))
                         ((simd_<arithmetic_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return  if_else(is_ltz(a1),-a0,if_else_zero(is_nez(a1), a0));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::negate_, tag::cpu_,
                         (A0)(X),
                         ((simd_<unsigned_<A0>,X>))
                         ((simd_<unsigned_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return if_else_zero(is_nez(a1), a0);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::negate_, tag::cpu_,
                         (A0)(X),
                         ((simd_<floating_<A0>,X>))
                         ((simd_<floating_<A0>,X>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 tmp = if_else_zero(is_nez(a1), a0);
      tmp = if_else(is_ltz(a1), -a0, tmp);
      return select(is_nan(a1), a1, tmp); //TODO signed Nan ?
    }
  };
} } }
#endif

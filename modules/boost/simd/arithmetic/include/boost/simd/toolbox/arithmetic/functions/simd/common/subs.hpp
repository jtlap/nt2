//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_SUBS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_COMMON_SUBS_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/subs.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/is_less_equal.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/adds.hpp>
#include <boost/simd/include/functions/any.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#include <boost/simd/include/constants/valmin.hpp>
#include <boost/simd/include/constants/valmax.hpp>
#include <boost/simd/include/constants/one.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return boost::simd::sub(a0, a1);
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<uint_<A0>,X>))((simd_<uint_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 a0ma1 = a0-a1;
      return if_else_zero(le(a0ma1, a0), a0ma1); 
      //      return seladd(gt(a0, a1), Zero<A0>(), a0-a1); 
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::subs_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int_<A0>,X>))((simd_<int_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 res =  adds(a0, -a1); 
      if (boost::simd::any(eq(a1, Valmin<A0>())))
        return if_else(eq(a1, Valmin<A0>()), adds(adds(a0, Valmax<A0>()),One<A0>()), res);
      else
        return res; 
    }
  };
} } }


#endif

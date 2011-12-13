//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SUCCESSOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_SUCCESSOR_HPP_INCLUDED
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/constants/properties.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/bitinteger.hpp>
#include <boost/simd/include/functions/bitfloating.hpp>
#include <boost/simd/include/functions/tofloat.hpp>
#include <boost/simd/include/functions/seladd.hpp>
#include <boost/simd/include/functions/if_else.hpp>
#include <boost/simd/include/functions/fast_frexp.hpp>
#include <boost/simd/include/functions/fast_ldexp.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_not_equal.hpp>
#include <boost/simd/include/functions/next.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_ unary
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return  seladd(neq(a0, Valmax<A0>()), a0, One<A0>());
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_ unary
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return boost::simd::next(a0);
    }
  };
} } }



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<integer_<A0>,X>))((simd_<integer_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return seladd( boost::simd::gt(Valmax<A0>()-boost::simd::abs(a1), a0), a0, boost::simd::abs(a1));
      }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::successor_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<integer_<A1>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return select(eq(a0, Inf<A0>()), a0,  bitfloating(bitinteger(a0)+boost::simd::abs(a1)));
    }
  };
} } }


#endif

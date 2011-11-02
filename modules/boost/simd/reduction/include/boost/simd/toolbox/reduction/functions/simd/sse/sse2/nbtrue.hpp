//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_NBTRUE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/functions/typed_bool.hpp>
#include <boost/simd/include/functions/popcnt.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nbtrue_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef int32_t result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef simd::native<typename boost::simd::meta::int8_t_<A0>::type,boost::simd::tag::sse_> i8type;
      i8type tmp = {typed_bool(a0)};
      return boost::simd::popcnt(_mm_movemask_epi8(tmp))*boost::simd::meta::cardinal_of<A0>::value >> 4;
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nbtrue_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<logical_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef int32_t result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename A0::type vA0;
      typedef typename meta::scalar_of<vA0>::type sA0;
      typedef typename simd::native<boost::simd::uint8_t,boost::simd::tag::sse_> i8type; 
      //      typedef simd::native<typename boost::simd::meta::int8_t_<typename A0::type>::type,boost::simd::tag::sse_> i8type;
      i8type tmp = native_cast<i8type>(typed_bool(a0));
      return boost::simd::popcnt(_mm_movemask_epi8(tmp))*boost::simd::meta::cardinal_of<A0>::value >> 4;
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nbtrue_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef int32_t result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      int32_t  r = _mm_movemask_pd(typed_bool(a0));
      return   (r&1)+(r>>1);
    }
  };
} } }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::nbtrue_, boost::simd::tag::sse2_
                            , (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                            )
  {
    typedef int32_t result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type type;
      int32_t  r = _mm_movemask_ps(typed_bool(a0));
      return   (r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3);
      //      return boost::simd::popcnt(_mm_movemask_ps(is_nez(cast<type>(a0))));
    }
  };
} } }


#endif
#endif

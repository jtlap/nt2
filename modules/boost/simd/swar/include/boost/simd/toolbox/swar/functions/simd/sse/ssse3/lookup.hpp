//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_LOOKUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/toolbox/swar/functions/lookup.hpp>
#include <boost/simd/include/functions/shli.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
#include <iostream>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::lookup_, boost::simd::tag::ssse3_,
                         (A0)(A1),
                         ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                         ((simd_<ints8_<A1>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
      {
      return simd::native_cast<A0>(_mm_shuffle_epi8(a0, a1));
      }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::lookup_, boost::simd::tag::ssse3_,
                         (A0)(A1),
                         ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                         ((simd_<ints32_<A1>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef simd::native<int8_t, boost::simd::tag::sse_> type8;
      const type8 inc = make<type8>(0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3);
      const type8 dup = make<type8>(0, 0, 0, 0, 4, 4, 4, 4, 8, 8, 8, 8, 12, 12, 12, 12);
//    const type8 inc = native_cast<type8>(make<type64>(0x302010003020100LL,0x302010003020100LL));
//    const type8 dup = native_cast<type8>(make<type64>(0x404040400000000LL,0xc0c0c0c08080808LL));
      type8 i1 = {_mm_shuffle_epi8(shli(a1, 2), dup)};
      type8  r = {_mm_shuffle_epi8(simd::native_cast<type8>(a0), i1+inc )};
      return simd::native_cast<A0>(r);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::lookup_, boost::simd::tag::ssse3_,
                         (A0)(A1),
                         ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                         ((simd_<ints64_<A1>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef simd::native<int8_t, boost::simd::tag::sse_> type8;
      const type8 inc = make<type8>(0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7);
      const type8 dup = make<type8>(0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8);
//    const type8 inc = native_cast<type8>(make<type64>(506097522914230528ll,506097522914230528ll));
//    const type8 dup = native_cast<type8>(make<type64>(0ll,578721382704613384ll));
      const type8 i1 =  {_mm_shuffle_epi8(shli(a1, 3), dup)};
      const type8 r  =  {_mm_shuffle_epi8(simd::native_cast<type8>(a0), i1+inc)};
      return simd::native_cast<A0>(r);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::lookup_, boost::simd::tag::ssse3_,
                         (A0)(A1),
                         ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                         ((simd_<ints16_<A1>,boost::simd::tag::sse_>))
                        )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef simd::native<int8_t, boost::simd::tag::sse_> type8;
      const type8 inc = make<type8>(0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
      const type8 dup = make<type8>(0, 0, 2, 2, 4, 4, 6, 6, 8, 8, 10, 10, 12, 12, 14, 14);
      const type8 i1 = {_mm_shuffle_epi8(shli(a1, 1), dup)};
      const type8 r =  {_mm_shuffle_epi8(simd::native_cast<type8>(a0), plus(i1, inc))};//add increment
      return simd::native_cast<A0>(r);
    }
  };
} } }
#endif
#endif

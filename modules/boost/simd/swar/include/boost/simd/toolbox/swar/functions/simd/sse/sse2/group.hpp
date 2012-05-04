//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/toolbox/swar/functions/group.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

// TODO no float no int8_
#define BOOST_SIMD_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::sse_>))
                        ((simd_<double_<A0>,boost::simd::tag::sse_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type      stype; 
      typedef typename simd::meta::float__<stype>::type    sftype; 
      typedef simd::native<sftype,boost::simd::tag::sse_>           result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      typedef typename dispatch::meta::as_integer<rtype>::type itype;
      rtype r = simd::bitwise_cast<rtype>(_mm_slli_si128(simd::bitwise_cast<itype >(_mm_cvtpd_ps(a1)), 8));
      return b_or(r, simd::bitwise_cast<rtype>(_mm_cvtpd_ps(a0)));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                        ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type         stype;
      typedef typename dispatch::meta::downgrade<stype>::type      utype;
      typedef simd::native<utype,boost::simd::tag::sse_>               result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      return simd::bitwise_cast<rtype>(_mm_packs_epi32(a0, a1));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
// BOOST_SIMD_REGISTER_DISPATCH(boost::simd::tag::group_, boost::simd::tag::sse2_,
//                         (A0),
//                         ((simd_<single_<A0>,boost::simd::tag::sse_>))
//                         ((simd_<single_<A0>,boost::simd::tag::sse_>))
//                        );
// namespace boost { namespace ext
// {
//   template<class Dummy>
//   struct call<boost::simd::tag::group_(tag::simd_<tag::float_, tag::sse_> ,
//                           boost::simd::tag::simd_<tag::float_, tag::sse_> ),
//               boost::simd::boost::simd::tag::sse2_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)>
//     {
//       typedef typename meta::scalar_of<A0>::type                                      stype;
//       typedef typename dispatch::meta::downgrade<stype>::type                                   utype;
//       typedef simd::native<utype,boost::simd::tag::sse_>                                           type1;
//       typedef simd::native<typename meta::single_<A0>::type,boost::simd::tag::sse_>                 type2;
//       typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
//                                         , type2
//                                         , type1
//                                         >::type type;
//     };
//   };
// } } }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                        ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename dispatch::meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,boost::simd::tag::sse_>                                            result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      return simd::bitwise_cast<rtype>(_mm_packs_epi16(a0, a1));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                        ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename dispatch::meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,boost::simd::tag::sse_>                                            result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      rtype r = simd::bitwise_cast<rtype > (_mm_set_epi16(a1[3], a1[2], a1[1], a1[0], a0[3], a0[2], a0[1], a0[0]));  
      //	make<rtype>( a0[0], a0[1], a0[2], a0[3], a1[0], a1[1], a1[2], a1[3] );
      return r; 
      //      return simd::bitwise_cast<rtype>(_mm_packus_epi32(a0, a1)); //_mm_packus_epi32 pas existe avant sse4.1
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                        ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename dispatch::meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,boost::simd::tag::sse_>                                           result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      return simd::bitwise_cast<rtype>(_mm_packus_epi16(a0, a1));
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::group_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                        ((simd_<ints64_<A0>,boost::simd::tag::sse_>))
                       )
  {
      typedef typename meta::scalar_of<A0>::type         stype;
      typedef typename dispatch::meta::downgrade<stype>::type      utype;
      typedef simd::native<utype,boost::simd::tag::sse_>              result_type;
    
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      rtype b = {_mm_slli_si128(simd::bitwise_cast<rtype>(a1),4)};// works only for int64 that are int32 representable
      b = b_or(b, a0);
      return simd::bitwise_cast<rtype>(_mm_shuffle_epi32(b, BOOST_SIMD_SH(0, 2, 1, 3)));
    }
  };
} } }
#undef BOOST_SIMD_SH
#endif
#endif

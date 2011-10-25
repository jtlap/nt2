//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SPLIT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/sdk/memory/aligned_type.hpp>

#include <boost/fusion/tuple.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/sdk/meta/templatize.hpp>
#include <boost/dispatch/meta/adapted_traits.hpp>
#include <boost/simd/include/functions/is_ltz.hpp>
#include <boost/simd/include/constants/digits.hpp>
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::split_, boost::simd::tag::sse2_
                                      , (A0)(A1)
                                      , (boost::mpl::and_ <
                                            boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::upgrade<A0>::type> >,
                                            boost::is_same<A1, typename dispatch::meta::upgrade<A0>::type>
                                        >)
                                      , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                                        ((simd_<arithmetic_<A1>,boost::simd::tag::sse_>))
                                        ((simd_<arithmetic_<A1>,boost::simd::tag::sse_>))
                                      ) 
  {
    typedef typename meta::scalar_of<A0>::type                                      stype;
    typedef typename dispatch::meta::upgrade<stype>::type                           utype;
    typedef simd::native<utype,boost::simd::tag::sse_>                              ttype;
    typedef dispatch::meta::is_floating_point<stype>                                rtag;
    typedef simd::native<typename boost::simd::meta::double__<A0>::type,boost::simd::tag::sse_>    dtype;
    typedef typename boost::mpl::if_c<rtag::value,dtype,ttype>::type                rtype;

    typedef int result_type;    
    inline result_type operator()(A0 const& a0,A1 & a1, A1 & a2) const
    {
      eval( a0, a1, a2, rtype());
      return 0; 
    }
  private:
    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename boost::simd::meta::int16_t_<A0>::type,boost::simd::tag::sse_>&)const
    {
      typedef simd::native<typename  boost::simd::meta::int16_t_<A0>::type,boost::simd::tag::sse_> rtype;
      r1 = bitwise_cast<rtype>(_mm_unpackhi_epi8(a0, is_ltz(a0)));
      r0 = bitwise_cast<rtype>(_mm_unpacklo_epi8(a0, is_ltz(a0)));
    }
    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  boost::simd::meta::uint16_t_<A0>::type,boost::simd::tag::sse_ > &)const
    {
      typedef simd::native<typename  boost::simd::meta::uint16_t_<A0>::type,boost::simd::tag::sse_> rtype;
      r1 = bitwise_cast<rtype>(_mm_unpackhi_epi8(a0, Zero<A0>()));
      r0 = bitwise_cast<rtype>(_mm_unpacklo_epi8(a0, Zero<A0>()));
    }
    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  boost::simd::meta::int32_t_<A0>::type,boost::simd::tag::sse_ > &)const
    {
      typedef simd::native<typename  boost::simd::meta::int32_t_<A0>::type,boost::simd::tag::sse_> rtype;
      r1 = bitwise_cast<rtype>(_mm_unpackhi_epi16(a0, is_ltz(a0)));
      r0 = bitwise_cast<rtype>(_mm_unpacklo_epi16(a0, is_ltz(a0)));
    }
    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  boost::simd::meta::uint32_t_<A0>::type,boost::simd::tag::sse_ > &)const
    {
      typedef simd::native<typename  boost::simd::meta::uint32_t_<A0>::type,boost::simd::tag::sse_> rtype;
      r1 = bitwise_cast<rtype>(_mm_unpackhi_epi16(a0, Zero<A0>()));
      r0 = bitwise_cast<rtype>(_mm_unpacklo_epi16(a0, Zero<A0>()));
    }
    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  boost::simd::meta::int64_t_<A0>::type,boost::simd::tag::sse_ > &)const
    {
      typedef simd::native<typename  boost::simd::meta::int64_t_<A0>::type,boost::simd::tag::sse_> rtype;
      r1 = bitwise_cast<rtype>(_mm_unpackhi_epi32(a0, is_ltz(a0)));
      r0 = bitwise_cast<rtype>(_mm_unpacklo_epi32(a0, is_ltz(a0)));
    }
    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  boost::simd::meta::uint64_t_<A0>::type,boost::simd::tag::sse_ > &)const
    {
      typedef simd::native<typename  boost::simd::meta::uint64_t_<A0>::type,boost::simd::tag::sse_> rtype;
      r1 = bitwise_cast<rtype>(_mm_unpackhi_epi32(a0, Zero<A0>()));
      r0 = bitwise_cast<rtype>(_mm_unpacklo_epi32(a0, Zero<A0>()));
    }

    template<class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  boost::simd::meta::double__<A0>::type,boost::simd::tag::sse_> &)const
    {
      typedef simd::native<typename boost::simd::meta::int32_t_<A0>::type,boost::simd::tag::sse_> itype;
      r1 = bitwise_cast<R1>(_mm_cvtps_pd(bitwise_cast<A0>(_mm_srli_si128( bitwise_cast<itype>(a0), 8))));
      r0 = bitwise_cast<R0>(_mm_cvtps_pd(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF(boost::simd::tag::split_, boost::simd::tag::sse2_,
                                       (A0),
                                       (boost::mpl::not_< boost::is_same<A0, typename dispatch::meta::upgrade<A0>::type> >), 
                                       ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))
                                      )
  {
    typedef typename dispatch::meta::upgrade<A0>::type                              rtype;
    typedef boost::fusion::tuple<rtype,rtype>                       result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type res;
      boost::simd::split(a0, boost::fusion::at_c<0>(res), boost::fusion::at_c<1>(res));
      return res;
    }


  };
} } }

#endif
#endif

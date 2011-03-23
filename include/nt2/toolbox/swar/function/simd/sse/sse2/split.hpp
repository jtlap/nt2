//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_SPLIT_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ltz.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::split_, tag::cpu_,
                        (A0),
                        ((simd_<arithmetic_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::split_(tag::simd_<tag::arithmetic_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::sse_>                                 ttype;
      typedef meta::is_floating_point<stype>                                 rtag;
      typedef simd::native<typename  meta::double__<A0>::type,tag::sse_>    dtype;

      typedef typename boost::mpl::if_c<rtag::value,dtype,ttype>::type      rtype;
      typedef boost::fusion::tuple<rtype,rtype>                              type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef meta::is_floating_point<stype>                                 rtag;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::sse_>                                 ttype;
      typedef typename boost::mpl::if_c<rtag::value,
                                        simd::native<double,tag::sse_>,
	                                ttype>::type                        rtype;
      typename NT2_RETURN_TYPE(1)::type                                       res;
      typedef rtype                                                           tag;

      eval( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          , tag()
          );
      return res;
    }
  private:
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int16_t_<A0>::type,tag::sse_>&)const
    {
      typedef simd::native<typename  meta::int16_t_<A0>::type,tag::sse_> rtype;
      r1 = simd::native_cast<rtype>(_mm_unpackhi_epi8(a0, is_ltz(a0)));
      r0 = simd::native_cast<rtype>(_mm_unpacklo_epi8(a0, is_ltz(a0)));
    }
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::uint16_t_<A0>::type,tag::sse_ > &)const
    {
      typedef simd::native<typename  meta::uint16_t_<A0>::type,tag::sse_> rtype;
      r1 = simd::native_cast<rtype>(_mm_unpackhi_epi8(a0, Zero<A0>()));
      r0 = simd::native_cast<rtype>(_mm_unpacklo_epi8(a0, Zero<A0>()));
    }
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int32_t_<A0>::type,tag::sse_ > &)const
    {
      typedef simd::native<typename  meta::int32_t_<A0>::type,tag::sse_> rtype;
      r1 = simd::native_cast<rtype>(_mm_unpackhi_epi16(a0, is_ltz(a0)));
      r0 = simd::native_cast<rtype>(_mm_unpacklo_epi16(a0, is_ltz(a0)));
    }
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::uint32_t_<A0>::type,tag::sse_ > &)const
    {
      typedef simd::native<typename  meta::uint32_t_<A0>::type,tag::sse_> rtype;
      r1 = simd::native_cast<rtype>(_mm_unpackhi_epi16(a0, Zero<A0>()));
      r0 = simd::native_cast<rtype>(_mm_unpacklo_epi16(a0, Zero<A0>()));
    }
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int64_t_<A0>::type,tag::sse_ > &)const
    {
      typedef simd::native<typename  meta::int64_t_<A0>::type,tag::sse_> rtype;
      r1 = simd::native_cast<rtype>(_mm_unpackhi_epi32(a0, is_ltz(a0)));
      r0 = simd::native_cast<rtype>(_mm_unpacklo_epi32(a0, is_ltz(a0)));
    }
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::uint64_t_<A0>::type,tag::sse_ > &)const
    {
      typedef simd::native<typename  meta::uint64_t_<A0>::type,tag::sse_> rtype;
      r1 = simd::native_cast<rtype>(_mm_unpackhi_epi32(a0, Zero<A0>()));
      r0 = simd::native_cast<rtype>(_mm_unpacklo_epi32(a0, Zero<A0>()));
    }

    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::double__<A0>::type,tag::sse_> &)const
    {
      typedef simd::native<typename meta::int32_t_<A0>::type,tag::sse_> itype;
      r1 = simd::native_cast<R1>(_mm_cvtps_pd(simd::native_cast<A0>(_mm_srli_si128( simd::native_cast<itype>(a0), 8))));
      r0 = simd::native_cast<R0>(_mm_cvtps_pd(a0));
    }


  };
} }

#endif
// modified by jt the 05/01/2011

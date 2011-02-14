//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_SPLIT_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/split.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::split_, tag::cpu_,
                        (A0),
                        ((simd_<arithmetic_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::split_(tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                  utype;
      typedef simd::native<utype,simd::avx_>                                ttype;
      typedef meta::is_floating_point<stype>                                 rtag;
      typedef simd::native<typename  meta::double_<A0>::type,simd::avx_>    dtype;

      typedef typename boost::mpl::if_c < rtag::value
                                        , dtype, ttype>::type              rtype;
      typedef boost::fusion::tuple<rtype,rtype>                              type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef meta::is_floating_point<stype>                                 rtag;
      typedef typename meta::upgrade<stype>::type                  utype;
      typedef simd::native<utype,simd::avx_>                                ttype;
      typedef typename boost::mpl::if_c<rtag::value,
                                        simd::native<double,simd::avx_>, ttype>::type rtype;
      typename NT2_RETURN_TYPE(1)::type                                  res;
      typedef rtype                                                           tag;

      eval( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          , tag()
          );
      return res;
    }
  private:
//     template<class A0,class R0,class R1> inline void
//     eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int16_t_<A0>::type,simd::avx_>&)const
//     {
//       typedef simd::native<typename  meta::int16_t_<A0>::type,simd::avx_> rtype;
//       r1 = simd::native_cast<rtype>(_mm_unpackhi_epi8(a0, is_ltz(a0)));
//       r0 = simd::native_cast<rtype>(_mm_unpacklo_epi8(a0, is_ltz(a0)));
//     }
//     template<class A0,class R0,class R1> inline void
//     eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::uint16_t_<A0>::type,simd::avx_ > &)const
//     {
//       typedef simd::native<typename  meta::uint16_t_<A0>::type,simd::avx_> rtype;
//       r1 = simd::native_cast<rtype>(_mm_unpackhi_epi8(a0, Zero<A0>()));
//       r0 = simd::native_cast<rtype>(_mm_unpacklo_epi8(a0, Zero<A0>()));
//     }
//     template<class A0,class R0,class R1> inline void
//     eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int32_t_<A0>::type,simd::avx_ > &)const
//     {
//       typedef simd::native<typename  meta::int32_t_<A0>::type,simd::avx_> rtype;
//       r1 = simd::native_cast<rtype>(_mm_unpackhi_epi16(a0, is_ltz(a0)));
//       r0 = simd::native_cast<rtype>(_mm_unpacklo_epi16(a0, is_ltz(a0)));
//     }
//     template<class A0,class R0,class R1> inline void
//     eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::uint32_t_<A0>::type,simd::avx_ > &)const
//     {
//       typedef simd::native<typename  meta::uint32_t_<A0>::type,simd::avx_> rtype;
//       r1 = simd::native_cast<rtype>(_mm_unpackhi_epi16(a0, Zero<A0>()));
//       r0 = simd::native_cast<rtype>(_mm_unpacklo_epi16(a0, Zero<A0>()));
//     }
//     template<class A0,class R0,class R1> inline void
//     eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int64_t_<A0>::type,simd::avx_ > &)const
//     {
//       typedef simd::native<typename  meta::int64_t_<A0>::type,simd::avx_> rtype;
//       r1 = simd::native_cast<rtype>(_mm_unpackhi_epi32(a0, Zero<A0>()));
//       r0 = simd::native_cast<rtype>(_mm_unpacklo_epi32(a0, Zero<A0>()));
//     }
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::int64_t_<A0>::type,simd::avx_ > &)const
    {
      typedef simd::native<typename  meta::int64_t_<A0>::type,simd::avx_> rtype;
      typedef simd::native<typename  meta::float_ <A0>::type,simd::avx_> ftype;
#define CAST(TYPE, CAT, A) simd::native_cast<simd::native<TYPE, simd::CAT> >(A)
      ftype a00 = {CAST(float, avx_,_mm256_permute_pd(CAST(double, avx_,a0), 0xFF))};
      r1 =  simd::native_cast<rtype>(_mm256_unpackhi_ps(a00, Zero<ftype>()));
      r0 =  simd::native_cast<rtype>(_mm256_unpacklo_ps(a00, Zero<ftype>()));
#undef CAT
    }

    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0, R0& r0, R1& r1, const simd::native<typename  meta::double_<A0>::type,simd::avx_> &)const
    {
      r0 = _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 0)) ;
      r1 = _mm256_cvtps_pd(_mm256_extractf128_ps(a0, 1)) ;
    }


  };
} }

#endif
// modified by jt the 05/01/2011
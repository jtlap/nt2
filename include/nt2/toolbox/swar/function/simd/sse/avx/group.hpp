//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_GROUP_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<double_<A0>,tag::avx_>))
                        ((simd_<double_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::double_, tag::avx_),
                          tag::simd_<tag::double_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      typedef simd::native<float,tag::sse_ >   htype;
      htype r0 = {_mm256_cvtpd_ps(a0)};
      htype r1 = {_mm256_cvtpd_ps(a1)};
      rtype r  = {_mm256_insertf128_ps(r, r0, 0)};
      r = _mm256_insertf128_ps(r, r1, 1);
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<int32_<A0>,tag::avx_>))
                        ((simd_<int32_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::int32_, tag::avx_),
                          tag::simd_<tag::int32_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packs_epi32(a00, a01)};
      std::cout  << "v0 "<< v0 << std::endl;
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packs_epi32(a10, a11)};
      std::cout  << "v1 "<< v1 << std::endl;
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<int16_<A0>,tag::avx_>))
                        ((simd_<int16_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::int16_, tag::avx_),
                          tag::simd_<tag::int16_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0   = {_mm_packs_epi16(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1   = {_mm_packs_epi16(a10, a11)};
      rtype r   = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<uint32_<A0>,tag::avx_>))
                        ((simd_<uint32_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::uint32_, tag::avx_),
                          tag::simd_<tag::uint32_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0 = {_mm_packus_epi32(a00, a01)};
      std::cout  << "v0 "<< v0 << std::endl;
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1 = {_mm_packus_epi32(a10, a11)};
      std::cout  << "v1 "<< v1 << std::endl;
      rtype r = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<int64_<A0>,tag::avx_>))
                        ((simd_<int64_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::int64_, tag::avx_),
                          tag::simd_<tag::int64_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };


  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<uint64_<A0>,tag::avx_>))
                        ((simd_<uint64_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::uint64_, tag::avx_),
                          tag::simd_<tag::uint64_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };


  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<uint16_<A0>,tag::avx_>))
                        ((simd_<uint16_<A0>,tag::avx_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::uint16_, tag::avx_),
                          tag::simd_<tag::uint16_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                          utype;
      typedef simd::native<utype,simd::avx_>                                          type1;
      typedef simd::native<typename meta::float_<A0>::type,simd::avx_>                type2;
      typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
                                        , type2
                                        , type1
                                        >::type type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      //     typedef typename meta::same<A0,tag::sse_>::type htype;
      typedef simd::native<typename meta::scalar_of<A0>::type,tag::sse_ >   htype;
      typedef simd::native<typename meta::scalar_of<rtype>::type,tag::sse_ >   type;
      //      typedef typename meta::same<rtype,tag::sse_>::type type;
      htype a00 = {_mm256_extractf128_si256(a0, 0)};
      htype a01 = {_mm256_extractf128_si256(a0, 1)};
      type v0   = {_mm_packus_epi16(a00, a01)};
      htype a10 = {_mm256_extractf128_si256(a1, 0)};
      htype a11 = {_mm256_extractf128_si256(a1, 1)};
      type v1   = {_mm_packus_epi16(a10, a11)};
      rtype r   = {_mm256_insertf128_si256(r, v0, 0)};
      r = simd::native_cast<rtype>(_mm256_insertf128_si256(r, v1, 1));
      return r;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
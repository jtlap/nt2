//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_GROUP_HPP_INCLUDED
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>

// TODO no float no int8_

#define NT2_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::double_, tag::sse_> ,
                          tag::simd_<tag::double_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type      stype; 
      typedef typename meta::float__<stype>::type    sftype; 
      typedef simd::native<sftype,tag::sse_>           type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      typedef typename meta::as_integer<rtype>::type itype;
      rtype r = simd::native_cast<rtype>(_mm_slli_si128(simd::native_cast<itype >(_mm_cvtpd_ps(a1)), 8));
      return b_or(r, simd::native_cast<rtype>(_mm_cvtpd_ps(a0)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<ints32_<A0>,tag::sse_>))
                        ((simd_<ints32_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::ints32_, tag::sse_> ,
                          tag::simd_<tag::ints32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type         stype;
      typedef typename meta::downgrade<stype>::type      utype;
      typedef simd::native<utype,tag::sse_>               type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi32(a0, a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
//                         (A0),
//                         ((simd_<float_<A0>,tag::sse_>))
//                         ((simd_<float_<A0>,tag::sse_>))
//                        );

// namespace nt2 { namespace ext
// {
//   template<class Dummy>
//   struct call<tag::group_(tag::simd_<tag::float_, tag::sse_> ,
//                           tag::simd_<tag::float_, tag::sse_> ),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)>
//     {
//       typedef typename meta::scalar_of<A0>::type                                      stype;
//       typedef typename meta::downgrade<stype>::type                                   utype;
//       typedef simd::native<utype,tag::sse_>                                           type1;
//       typedef simd::native<typename meta::float_<A0>::type,tag::sse_>                 type2;
//       typedef typename boost::mpl::if_c < boost::is_same<stype,double>::value
//                                         , type2
//                                         , type1
//                                         >::type type;
//     };


//   };
// } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<int16_<A0>,tag::sse_>))
                        ((simd_<int16_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::int16_, tag::sse_> ,
                          tag::simd_<tag::int16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                            type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packs_epi16(a0, a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<uint32_<A0>,tag::sse_>))
                        ((simd_<uint32_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::uint32_, tag::sse_> ,
                          tag::simd_<tag::uint32_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                            type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      rtype r = simd::native_cast<rtype > (_mm_set_epi16(a1[3], a1[2], a1[1], a1[0], a0[3], a0[2], a0[1], a0[0]));  
      //	{{ a0[0], a0[1], a0[2], a0[3], a1[0], a1[1], a1[2], a1[3]}};
      return r; 
      //      return simd::native_cast<rtype>(_mm_packus_epi32(a0, a1)); //_mm_packus_epi32 pas existe avant sse4.1
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<uint16_<A0>,tag::sse_>))
                        ((simd_<uint16_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::uint16_, tag::sse_> ,
                          tag::simd_<tag::uint16_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type                                      stype;
      typedef typename meta::downgrade<stype>::type                                   utype;
      typedef simd::native<utype,tag::sse_>                                           type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      return simd::native_cast<rtype>(_mm_packus_epi16(a0, a1));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is ints64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::group_, tag::cpu_,
                        (A0),
                        ((simd_<ints64_<A0>,tag::sse_>))
                        ((simd_<ints64_<A0>,tag::sse_>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::group_(tag::simd_<tag::ints64_, tag::sse_> ,
                          tag::simd_<tag::ints64_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)>
    {
      typedef typename meta::scalar_of<A0>::type         stype;
      typedef typename meta::downgrade<stype>::type      utype;
      typedef simd::native<utype,tag::sse_>              type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      rtype b = {_mm_slli_si128(simd::native_cast<rtype>(a1),4)};// works only for int64 that are int32 representable
      b = b_or(b, a0);
      return simd::native_cast<rtype>(_mm_shuffle_epi32(b, NT2_SH(0, 2, 1, 3)));
    }
  };
} }

#undef NT2_SH

#endif
// modified by jt the 05/01/2011
// modified manually by jt the 05/01/2011

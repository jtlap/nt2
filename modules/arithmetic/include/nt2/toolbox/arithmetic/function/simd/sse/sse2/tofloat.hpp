//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_TOFLOAT_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/include/functions/is_gez.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::tofloat_, tag::cpu_,
                          (A0),
                          ((simd_<int32_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::tofloat_(tag::simd_<tag::int32_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type type;
      type that = { _mm_cvtepi32_ps(a0)};
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::tofloat_, tag::cpu_,
                          (A0),
                          ((simd_<uint64_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::tofloat_(tag::simd_<tag::uint64_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type  type;
      typedef typename meta::scalar_of<type>::type stype;
      type const v = {{static_cast<stype>(a0[0])
                      , static_cast<stype>(a0[1])}};
      return v;

    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::tofloat_, tag::cpu_,
                          (A0),
                          ((simd_<real_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::tofloat_(tag::simd_<tag::real_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      return a0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::tofloat_, tag::cpu_,
                          (A0),
                          ((simd_<uint32_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::tofloat_(tag::simd_<tag::uint32_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type  type;
      typedef typename meta::scalar_of<type>::type stype;

      type that = {{ static_cast<stype>(a0[0])
                  , static_cast<stype>(a0[1])
                  , static_cast<stype>(a0[2])
                  , static_cast<stype>(a0[3])
	}}; //TO DO
      return that;
 //      typedef typename meta::scalar_of<A0>::type stype;
//       typedef typename meta::as_integer<A0,signed>::type sint_type;
//       //      static const sint_type hibitmask = integral_constant<sint_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const result_type offset = integral_constant<result_type, 1ll << (8*sizeof(stype)-1) >() ;
//       const sint_type a00 = simd::native_cast<sint_type>(a0);
//       result_type v1 = {_mm_cvtepi32_ps(a00)};
//       result_type v2 = {_mm_cvtepi32_ps((b_andnot(a00, Signmask<sint_type>())))};
//       v2 = v2+offset;
//       return sel(is_gez(a00),v1,v2);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::tofloat_, tag::cpu_,
                          (A0),
                          ((simd_<int64_<A0>,tag::sse_>))
                         );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::tofloat_(tag::simd_<tag::int64_, tag::sse_>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_real<A0>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_RETURN_TYPE(1)::type  type;
      typedef typename meta::scalar_of<type>::type sftype;
      if (maximum(abs(a0)) > Valmax<int32_t>())
      {
        type const v =  {{ static_cast<sftype>(a0[0])
                        , static_cast<sftype>(a0[1])
	  }};
         return v;
      }
      typedef typename meta::int32_t_<A0>::type htype;
      typedef simd::native<htype,tag::sse_> itype;
      itype tmp = {_mm_shuffle_epi32(a0, _MM_SHUFFLE(3, 1, 2, 0))};
      type v = { _mm_cvtepi32_pd(tmp)};
      return v;
    }
  };
} }

#endif
// modified by jt the 04/01/2011
// modified manually by jt the 06/01/2011

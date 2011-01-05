//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_PUT_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_PUT_FIRST_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/templatize.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0),
                            ((simd_<double_<A0>,tag::sse_>))
                            ((simd_<double_<A0>,tag::sse_>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_(tag::double_, tag::sse_),
                              tag::simd_(tag::double_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      if(a1)
      {
        A0 that = { _mm_unpackhi_pd(a0,a0)};
        return that;
      }
      return a0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0),
                            ((simd_<types8_<A0>,tag::sse_>))
                            ((simd_<types8_<A0>,tag::sse_>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_(tag::types8_, tag::sse_),
                              tag::simd_(tag::types8_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef simd::native<typename meta::double_<A0>::type,tag::sse_>   rtype;
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
      if(a1 > 7)
      {
        A0 t = { _mm_srli_si128(simd::native_cast<type64>(a0), 8 )};
        return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-8) << 3));
      }
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 3));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0),
                            ((simd_<types64_<A0>,tag::sse_>))
                            ((simd_<types64_<A0>,tag::sse_>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_(tag::types64_, tag::sse_),
                              tag::simd_(tag::types64_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_real<A0>::type rtype;
      if(a1)
      {
        return simd::native_cast<A0>(_mm_unpackhi_pd(simd::native_cast<rtype>(a0),simd::native_cast<rtype>(a0)));
      }
      return a0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0),
                            ((simd_<types16_<A0>,tag::sse_>))
                            ((simd_<types16_<A0>,tag::sse_>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_(tag::types16_, tag::sse_),
                              tag::simd_(tag::types16_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef simd::native<typename meta::double_<A0>::type,tag::sse_>   rtype;
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
      if(a1 > 3)
      {
        A0 t = { _mm_srli_si128(simd::native_cast<type64>(a0), 8 )};
        return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-4) << 4));
      }
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 4));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0),
                            ((simd_<types32_<A0>,tag::sse_>))
                            ((simd_<types32_<A0>,tag::sse_>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_(tag::types32_, tag::sse_),
                              tag::simd_(tag::types32_, tag::sse_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef simd::native<typename meta::double_<A0>::type,tag::sse_>   rtype;
      typedef simd::native<typename meta::int64_t_<A0>::type,tag::sse_>  type64;
      if(a1 > 1)
      {
        A0 t = { simd::native_cast<A0>(_mm_srli_si128(simd::native_cast<type64>(a0), 8 ))};
        return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-2) << 5));
      }
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 5));
    }
  };
} }

#endif
// modified by jt the 04/01/2011
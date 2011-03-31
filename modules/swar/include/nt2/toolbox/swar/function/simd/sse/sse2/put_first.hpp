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
#include <nt2/sdk/simd/native_cast.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0)(A1),
                            ((simd_<double_<A0>,tag::sse_>))
                            ((integer_<A1>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::double_, tag::sse_> ,
                              tag::integer_),
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
// Implementation when type A0 is type8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0)(A1),
                            ((simd_<type8_<A0>,tag::sse_>))
                            ((integer_<A1>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::type8_, tag::sse_> ,
                              tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
      struct result<This(A0, A1)> :  meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
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
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0)(A1),
                            ((simd_<type64_<A0>,tag::sse_>))
                            ((integer_<A1>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::type64_, tag::sse_> ,
			      tag::integer_),
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
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0)(A1),
                            ((simd_<type16_<A0>,tag::sse_>))
                            ((integer_<A1>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::type16_, tag::sse_> ,
                              tag::integer_),
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
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::put_first_, tag::cpu_,
                            (A0)(A1),
                            ((simd_<type32_<A0>,tag::sse_>))
                             ((integer_<A1>))
                           );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::put_first_(tag::simd_<tag::type32_, tag::sse_> ,
                              tag::integer_),
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
	type64 z = simd::native_cast<type64>(a0);
	z = _mm_srli_si128(z, 8 ); 
        A0 t = simd::native_cast<A0>(z);
        return simd::native_cast<A0>(shri(simd::native_cast<type64>(t), (a1-2) << 5));
      }
      return simd::native_cast<A0>(shri(simd::native_cast<type64>(a0), a1 << 5));
    }
  };
} }

#endif
// modified by jt the 05/01/2011

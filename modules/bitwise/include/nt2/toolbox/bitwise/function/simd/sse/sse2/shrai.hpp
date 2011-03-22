//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRAI_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE2_SHRAI_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shrai_, tag::cpu_,
                        (A0)(A1),
                        ((simd_<unsigned_<A0>,tag::sse_>))
                         ((integer_<A1>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shrai_(tag::simd_<tag::unsigned_, tag::sse_>,
                          tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return shri(a0, a1);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shrai_, tag::cpu_,
                        (A0)(A1),
                        ((simd_<int32_<A0>,tag::sse_>))
                         ((integer_<A1>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shrai_(tag::simd_<tag::int32_, tag::sse_>,
                          tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0,signed>::type sint;
      sint const that = {_mm_srai_epi32(simd::native_cast<sint>(a0), a1)};
      return simd::native_cast<A0>(that);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shrai_, tag::cpu_,
                        (A0)(A1),
                        ((simd_<int16_<A0>,tag::sse_>))
                         ((integer_<A1>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shrai_(tag::simd_<tag::int16_, tag::sse_>,
                          tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0,signed>::type sint;
      sint const that =  {_mm_srai_epi16(simd::native_cast<sint>(a0), a1)};
      return simd::native_cast<A0>(that);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shrai_, tag::cpu_,
                        (A0)(A1),
                        ((simd_<int8_<A0>,tag::sse_>))
                         ((integer_<A1>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shrai_(tag::simd_<tag::int8_, tag::sse_>,
                          tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type result_type;
      typedef simd::native<typename meta::int16_t_<A0>::type,tag::sse_> gen_type;
      gen_type a0h, a0l;
      boost::fusion::tie(a0l, a0h) = split(a0);
      return simd::native_cast<A0>(group(shrai(a0l, a1),shrai(a0h, a1)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::shrai_, tag::cpu_,
                        (A0)(A1),
                        ((simd_<int64_<A0>,tag::sse_>))
                         ((integer_<A1>))
                       );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::shrai_(tag::simd_<tag::int64_, tag::sse_>,
                          tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0,A1)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {

      A0 that = {{shrai(a0[0], a1), shrai(a0[1], a1)}};
      return that;
    }
  };
} }

#endif
// modified by jt the 04/01/2011
// modified manually by jt the 05/01/2011    

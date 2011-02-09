//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_NOT_EQUAL_TO_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_SSE_SSE2_IS_NOT_EQUAL_TO_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/downgrade.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for double
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_not_equal_, tag::cpu_, (A0)
                      , ((simd_<double_<A0>,tag::sse_>))
                        ((simd_<double_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_not_equal_( tag::simd_<tag::double_,tag::sse_>
                                  , tag::simd_<tag::double_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpneq_pd(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for float
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_not_equal_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::sse_>))
                        ((simd_<float_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_not_equal_( tag::simd_<tag::float_,tag::sse_>
                                  , tag::simd_<tag::float_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = { _mm_cmpneq_ps(a0,a1) };
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for integer
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_not_equal_, tag::cpu_, (A0)
                      , ((simd_<integer_<A0>,tag::sse_>))
                        ((simd_<integer_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_not_equal_( tag::simd_<tag::integer_,tag::sse_>
                                  , tag::simd_<tag::integer_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = nt2::complement(nt2::eq(a0,a1));
      return that;
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation for ints64
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::is_not_equal_, tag::cpu_, (A0)
                      , ((simd_<ints64_<A0>,tag::sse_>))
                        ((simd_<ints64_<A0>,tag::sse_>))
                      );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::is_not_equal_( tag::simd_<tag::ints64_,tag::sse_>
                                  , tag::simd_<tag::ints64_,tag::sse_>
                                  )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::downgrade<A0, unsigned>::type  type;
      type tmp      = { a0 - a1 };
      tmp           = nt2::neq(tmp,Zero<type>());
      type shuffled = { _mm_shuffle_epi32(tmp, _MM_SHUFFLE(2, 3, 0, 1)) };
      A0   that     = { tmp | shuffled };
      return that;
    }
  };
} }

#endif

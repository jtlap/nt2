//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_XOP_ABS_HPP_INCLUDED

#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/ssse3/abs.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is signed_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<signed_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::signed_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
 //      typedef typename meta::scalar_of<A0>::type sctype;
//       typedef typename simd::native<sctype, tag::sse_ >  svtype;
//       svtype a00 = { _mm256_extractf128_si256(a0, 0)};
//       svtype a01 = { _mm256_extractf128_si256(a0, 1)};
//       A0 that = { _mm256_insertf128_si256(that,nt2::abs(a00), 0)};
//       that =  _mm256_insertf128_si256(that,nt2::abs(a01), 1);
       NT2_XOP_JOIN128INT1(that, nt2::abs);
       return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<unsigned_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::unsigned_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1){ return a0; }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::abs_, tag::cpu_,
                      (A0),
                      ((simd_<real_<A0>,tag::xop_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::abs_(tag::simd_<tag::real_, tag::xop_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1){ return b_notand(Mzero<A0>(),a0); }
  };
} }

#endif
// modified by jt the 04/01/2011
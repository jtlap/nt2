//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_CUMSUM_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_AVX_CUMSUM_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/details/simd/sse/sse4_1/cumsum.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<arithmetic_<A0>,tag::avx_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::arithmetic_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, tag::sse_ >  svtype;
      svtype a000 = { _mm256_extractf128_si256(a0, 0)};
      svtype a011 = { _mm256_extractf128_si256(a0, 1)};
      std::cout << " == a000 " << a000 << std::endl;
      std::cout << " == a011 " << a011 << std::endl;
       svtype a00 =  cumsum(a000);
       svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      std::cout << " == a00 " << a00 << std::endl;
      std::cout << " == a01 " << a01 << std::endl;
      std::cout << " == z   " << z   << std::endl;
      A0 that = simd::native_cast<A0>(_mm256_insertf128_si256(that,a00, 0));
      that =  simd::native_cast<A0>(_mm256_insertf128_si256(that, a01+z, 1))              ;
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<double_<A0>,tag::avx_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::double_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, tag::sse_ >  svtype;
      svtype a000 = { _mm256_extractf128_pd(a0, 0)};
      svtype a011 = { _mm256_extractf128_pd(a0, 1)};
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      A0 that = simd::native_cast<A0>(_mm256_insertf128_pd(that,a00, 0));
      that =  simd::native_cast<A0>(_mm256_insertf128_pd(that, a01+z, 1))                 ;
      return that;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::cumsum_, tag::cpu_,
                         (A0),
                         ((simd_<float_<A0>,tag::avx_>))
                        );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::cumsum_(tag::simd_<tag::float_, tag::avx_)),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(1)
    {
      cout << "pb lié à gcc 4.5 ?" << std::endl;
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef typename simd::native<sctype, tag::sse_ >  svtype;
      std::cout << " == a0 " << a0 << std::endl;
      svtype a011;
      a011=  _mm256_extractf128_ps(a0, 1);
      svtype a000;
      a000 =  _mm256_extractf128_ps(a0, 0);
      std::cout << " == a000 " << a000 << std::endl;
      std::cout << " == a011 " << a011 << std::endl;
      svtype a00 =  cumsum(a000);
      svtype a01 =  cumsum(a011);
      svtype z = splat<svtype>(a00[meta::cardinal_of<svtype>::value-1]);
      std::cout << " == a00 " << a00 << std::endl;
      std::cout << " == a01 " << a01 << std::endl;
      std::cout << " == z   " << z   << std::endl;
      A0 that = {_mm256_insertf128_ps(that,a00, 0)};
      that =  _mm256_insertf128_ps(that, a01+z, 1);
      return that;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
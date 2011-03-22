//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_REVERSEBITS_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_REVERSEBITS_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/sdk/meta/downgrade.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::reversebits_, tag::cpu_,
                              (A0)(X),
                              ((simd_<int8_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::reversebits_(tag::simd_<tag::int8_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};


    NT2_FUNCTOR_CALL(1)
      {
      typedef typename NT2_RETURN_TYPE(1)::type    result_type;
      typedef typename meta::as_integer<A0, unsigned>::type utype;
      utype v = simd::native_cast<utype>(a0);
      const utype m1  = integral_constant<utype,0x55>(); //binary: 0101...
      const utype m2  = integral_constant<utype,0x33>(); //binary: 00110011..
      const utype m4  = integral_constant<utype,0x0f>(); //binary:  4 zeros,  4 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      return simd::native_cast<A0>(v);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::reversebits_, tag::cpu_,
                              (A0)(X),
                              ((simd_<int64_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::reversebits_(tag::simd_<tag::int64_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};


    NT2_FUNCTOR_CALL(1)
      {
      typedef typename NT2_RETURN_TYPE(1)::type    result_type;
      typedef typename meta::as_integer<A0, unsigned>::type utype;
      utype v = simd::native_cast<utype>(a0);
      const result_type m1  = integral_constant<result_type,0x5555555555555555ull>(); //binary: 0101...
      const result_type m2  = integral_constant<result_type,0x3333333333333333ull>(); //binary: 00110011..
      const result_type m4  = integral_constant<result_type,0x0f0f0f0f0f0f0f0full>(); //binary:  4 zeros,  4 ones ...
      const result_type m8  = integral_constant<result_type,0x00ff00ff00ff00ffull>(); //binary:  8 zeros,  8 ones ...
      const result_type m16 = integral_constant<result_type,0x0000ffff0000ffffull>(); //binary:  16 zeros,  16 ones ...
      const result_type m32 = integral_constant<result_type,0x00000000ffffffffull>(); //binary:  32 zeros,  32 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      // swap bytes ...
      v = (shri(v, 8) & m8) | shli((v & m8), 8);
      // swap shorts ...
      v = (shri(v, 16) & m16) | shli((v & m16), 16);
      // swap ints ...
      v = (shri(v, 32) & m32) | shli((v & m32), 32);
      return simd::native_cast<A0>(v);
 //   typedef typename NT2_RETURN_TYPE(1)::type    result_type;
//    typedef typename meta::as_integer<A0, unsigned>::type   utype;
//    typedef typename meta::scalar_of<utype>::type          sutype;
//    typedef typename meta::downgrade<sutype>::type         hutype;
//    typedef simd::native<hutype,tag::sse_>                 dutype;
//    //    typedef typename meta::downgrade<utype>::type          dutype;
//    dutype v = simd::native_cast<dutype>(a0);
// #define NT2_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))
//    dutype vv = {_mm_shuffle_epi32(reversebits(v), NT2_SH(0, 1, 2, 3))};
//    return simd::native_cast<A0 > (v);
// #undef   NT2_SH
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::reversebits_, tag::cpu_,
                              (A0)(X),
                              ((simd_<int16_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::reversebits_(tag::simd_<tag::int16_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};


    NT2_FUNCTOR_CALL(1)
      {
      typedef typename NT2_RETURN_TYPE(1)::type    result_type;
      typedef typename meta::as_integer<A0, unsigned>::type utype;
      utype v = simd::native_cast<utype>(a0);
      const result_type m1  = integral_constant<result_type,0x5555>(); //binary: 0101...
      const result_type m2  = integral_constant<result_type,0x3333>(); //binary: 00110011..
      const result_type m4  = integral_constant<result_type,0x0f0f>(); //binary:  4 zeros,  4 ones ...
      const result_type m8  = integral_constant<result_type,0x00ff>(); //binary:  8 zeros,  8 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      // swap bytes ...
      v = (shri(v, 8) & m8) | shli((v & m8), 8);
      return simd::native_cast<A0>(v);
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::reversebits_, tag::cpu_,
                              (A0)(X),
                              ((simd_<int32_<A0>,X>))
                             );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::reversebits_(tag::simd_<tag::int32_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> : meta::strip<A0>{};


    NT2_FUNCTOR_CALL(1)
      {
      typedef typename NT2_RETURN_TYPE(1)::type    result_type;
      typedef typename meta::as_integer<A0, unsigned>::type utype;
      utype v = simd::native_cast<utype>(a0);
      const result_type m1  = integral_constant<result_type,0x55555555>(); //binary: 0101...
      const result_type m2  = integral_constant<result_type,0x33333333>(); //binary: 00110011..
      const result_type m4  = integral_constant<result_type,0x0f0f0f0f>(); //binary:  4 zeros,  4 ones ...
      const result_type m8  = integral_constant<result_type,0x00ff00ff>(); //binary:  8 zeros,  8 ones ...
      const result_type m16 = integral_constant<result_type,0x0000ffff>(); //binary:  16 zeros,  16 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      // swap bytes ...
      v = (shri(v, 8) & m8) | shli((v & m8), 8);
      // swap shorts ...
      v = (shri(v, 16) & m16) | shli((v & m16), 16);
      return simd::native_cast<A0>(v);
      }
  };
} }

#endif
// modified by jt the 04/01/2011
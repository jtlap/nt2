//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_MULS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_SSE_SSE2_MULS_HPP_INCLUDED

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::muls_(tag::simd_<tag::arithmetic_, X> ,
			 tag::simd_<tag::arithmetic_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::upgrade<A0>::type utype; 
      utype res = utype(a0)*utype(a1);
      return A0(res) | genmask(A0(res >> sizeof(A0)*8)); 	
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                       (A0)(X),
                       ((simd_<uint16_<A0>,X>))((simd_<uint16_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::muls_(tag::simd_<tag::uint16_, X> ,
			 tag::simd_<tag::uint16_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 mulhi =  _mm_mulhi_epu16(a0, a1);
      A0 mullo =  _mm_mullo_epu16(a0, a1);
      return sel(eqz(mulhi), mullo, Valmax<A0>()); 
    }
  };
} }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                       (A0)(X),
                       ((simd_<int16_<A0>,X>))((simd_<int16_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::muls_(tag::simd_<tag::int16_, X> ,
			 tag::simd_<tag::int16_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 mulhi =  _mm_mulhi_epi16(a0, a1);
      A0 mullo =  _mm_mullo_epi16(a0, a1);
      return sel(eqz(mulhi), mullo, Valmax<A0>()); 
    }
  };
} }

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::muls_(tag::simd_<tag::uint8_, X> ,
			 tag::simd_<tag::uint8_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      A0 mulhi =  _mm_mulhi_epu8(a0, a1);
      A0 mullo =  _mm_mullo_epi8(a0, a1);
      return sel(eqz(mulhi), mullo, Valmax<A0>()); 
    }
  };
} }

#endif


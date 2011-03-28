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
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/rdivide.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int 32 8 64
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                       (A0)(X),
                       ((simd_<integer_<A0>,X>))((simd_<integer_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::muls_(tag::simd_<tag::integer_, X> ,
			 tag::simd_<tag::integer_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0, unsigned>::type untype; 
      A0 sign = b_xor(is_ltz(a0), is_ltz(a1));
      untype aa0 = simd::native_cast<untype>(nt2::abs(a0));
      untype aa1 = simd::native_cast<untype>(nt2::abs(a1));
      untype ga =  nt2::max(aa0, aa1);
      untype la =  nt2::min(aa0, aa1);
//       std::cout << "a0 "<< a0 << std::endl;
//       std::cout << "a1 "<< a1 << std::endl;
//       std::cout << "aa0 "<< aa0 << std::endl;
//       std::cout << "aa1 "<< aa1 << std::endl;
//       std::cout << "ga  "<< ga  << std::endl;
//       std::cout << "la  "<< la  << std::endl;
//       std::cout << "sgn "<< sign<< std::endl;
//       std::cout << "rd  "<< rdivide(simd::native_cast<untype>(Valmax<A0>()), ga)<< std::endl;
//       std::cout << "is_ltz(a0) " << is_ltz(a0)<< std::endl;
//       std::cout << "is_ltz(a1) " << is_ltz(a1)<< std::endl;
//       std::cout << "rdivide(simd::native_cast<untype>(Valmax<A0>()), ga)  " << rdivide(simd::native_cast<untype>(Valmax<A0>()), aa0)<< std::endl;
//       std::cout << "aa1  " << aa1 << std::endl;
//       std::cout << "lt(rdivide(simd::native_cast<untype>(Valmax<A0>()), aa0), aa1)  " << lt(rdivide(simd::native_cast<untype>(Valmax<A0>()), aa0), aa1)<< std::endl;
      return sel( lt(rdivide(simd::native_cast<untype>(Valmax<A0>()), ga), la),
		  sel(sign, Valmin<A0>(), Valmax<A0>()),
		  a0*a1
		 ); 
    }
  };
} }

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is int16_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
//                        (A0)(X),
//                        ((simd_<int16_<A0>,X>))((simd_<int16_<A0>,X>))
//                       );

// namespace nt2 { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<tag::muls_(tag::simd_<tag::int16_, X> ,
// 			 tag::simd_<tag::int16_, X>),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)> : meta::strip<A0>{};

//     NT2_FUNCTOR_CALL(2)
//     {
//       A0 aa0 = nt2::abs(a0);
//       A0 aa1 = nt2::abs(a1);
//       A0 mulhi =  simd::native_cast<A0>(_mm_mulhi_epi16(aa0, aa1));
//       A0 mullo =  simd::native_cast<A0>(_mm_mullo_epi16(a0, a1));
//       A0 sign = b_xor(is_ltz(a0), is_ltz(a1));
//       std::cout <<  "mullo "<<  mullo << std::endl;
//       std::cout <<  "mulhi "<<  mulhi << std::endl;
//       return sel(is_eqz(mulhi), mullo, sel(sign, Valmin<A0>(), Valmax<A0>())); 
//     }
//   };
// } }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint 32 8 64
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                       (A0)(X),
                       ((simd_<unsigned_<A0>,X>))((simd_<unsigned_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::muls_(tag::simd_<tag::unsigned_, X> ,
			 tag::simd_<tag::unsigned_, X>),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      return sel( lt(rdivide(Valmax<A0>(), a0), a1),
		  Valmax<A0>(),
		  a0*a1
		 ); 
    }
  };
} }
  
// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type A0 is uint16_
// /////////////////////////////////////////////////////////////////////////////
// NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
//                        (A0)(X),
//                        ((simd_<uint16_<A0>,X>))((simd_<uint16_<A0>,X>))
//                       );

// namespace nt2 { namespace ext
// {
//   template<class X, class Dummy>
//   struct call<tag::muls_(tag::simd_<tag::uint16_, X> ,
// 			 tag::simd_<tag::uint16_, X>),
//               tag::cpu_, Dummy> : callable
//   {
//     template<class Sig> struct result;
//     template<class This,class A0>
//     struct result<This(A0, A0)> : meta::strip<A0>{};

//     NT2_FUNCTOR_CALL(2)
//     {
//       A0 mulhi =  simd::native_cast<A0>(_mm_mulhi_epu16(a0, a1));
//       A0 mullo =  simd::native_cast<A0>(_mm_mullo_epi16(a0, a1));
//       return sel(is_eqz(mulhi), mullo, Valmax<A0>()); 
//     }
//   };
// } }



#endif


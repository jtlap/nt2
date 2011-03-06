/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_SHIFT_RIGHT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_SHIFT_RIGHT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// operator binary shift right
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::shift_right_, tag::cpu_, (A0)(A1)
                      , ((simd_<integer_<A0>,tag::altivec_>))
                        ((simd_<integer_<A1>,tag::altivec_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::shift_right_( tag::simd_<tag::integer_,tag::altivec_>
                                , tag::simd_<tag::integer_,tag::altivec_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0,class A1>  
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)  
    { 
     typedef typename meta::as_unsigned<A1>::type type;
     type shift = simd::native_cast<type>(a1);
     A0 that  = { vec_sr(a0(), shift()) }; 
     return that; 
    }
  };
} }

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::shift_right_, tag::cpu_, (A0)(A1)
                      , ((simd_<float_<A0>,tag::altivec_>))
                        ((simd_<ints32_<A1>,tag::altivec_>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy>
  struct  call< tag::shift_right_( tag::simd_<tag::float_,tag::altivec_>
                                , tag::simd_<tag::ints32_,tag::altivec_>
                                )
              , tag::cpu_, Dummy
              >
        : callable
  {
    template<class Sig>           struct result;
    template<class This,class A0,class A1>  
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2) 
   { 
     typedef typename meta::as_unsigned<A1>::type type;
     type shift = simd::native_cast<type>(a1);
     type value = simd::native_cast<type>(a0);
     A0 that  = simd::native_cast<A0>( vec_sr(value(), shift()) ); 
     return that;  
   }
  };
} }

#endif


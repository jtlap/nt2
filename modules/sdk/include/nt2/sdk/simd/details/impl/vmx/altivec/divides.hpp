/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_DIVIDES_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_DIVIDES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Register divides overload
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<float_<A0>,tag::altivec_>))
                        ((simd_<float_<A0>,tag::altivec_>))
                      );
/*
NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<ints8_<A0>,tag::altivec_>))
                        ((simd_<ints8_<A0>,tag::altivec_>))
                      );

NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<ints16_<A0>,tag::altivec_>))
                        ((simd_<ints16_<A0>,tag::altivec_>))
                      );

NT2_REGISTER_DISPATCH ( tag::divides_, tag::cpu_, (A0)
                      , ((simd_<ints32_<A0>,tag::altivec_>))
                        ((simd_<ints32_<A0>,tag::altivec_>))
                      );
*/

////////////////////////////////////////////////////////////////////////////////
// Altivec division algorithm are long-ass. Let's hide them for clarity purpose
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/details/impl/vmx/altivec/impl/divides_float.hpp>
#include <nt2/sdk/simd/details/impl/vmx/altivec/impl/divides_int32.hpp>
#include <nt2/sdk/simd/details/impl/vmx/altivec/impl/divides_int16.hpp>
#include <nt2/sdk/simd/details/impl/vmx/altivec/impl/divides_int8.hpp>

#endif

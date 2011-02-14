/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_MODULO_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_MODULO_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::modulo_, tag::cpu_, (A0)(X)
                      , ((simd_<integer_<A0>,X>))
                        ((simd_<integer_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct  call< tag::modulo_( tag::simd_<tag::integer_,X> 
                            , tag::simd_<tag::integer_,X> 
                            )
              , tag::cpu_, Dummy
              >
        : call< tag::modulo_( tag::simd_<tag::unspecified_,X> 
                            , tag::simd_<tag::unspecified_,X> 
                            )
              , tag::cpu_, Dummy
              >
  {};
} }

#endif

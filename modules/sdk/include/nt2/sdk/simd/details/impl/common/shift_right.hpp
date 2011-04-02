/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SHIFT_RIGHT_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_SHIFT_RIGHT_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Overload registration
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::shift_right_, tag::cpu_, (A0)(A1)(X)
                      , ((simd_<type64_<A0>,X>))
                        ((simd_<ints64_<A1>,X>))
                      );

NT2_REGISTER_DISPATCH ( tag::shift_right_, tag::cpu_, (A0)(A1)(X)
                      , ((simd_<type32_<A0>,X>))
                        ((simd_<ints32_<A1>,X>))
                      );

NT2_REGISTER_DISPATCH ( tag::shift_right_, tag::cpu_, (A0)(A1)(X)
                      , ((simd_<type16_<A0>,X>))
                        ((simd_<ints16_<A1>,X>))
                      );

NT2_REGISTER_DISPATCH ( tag::shift_right_, tag::cpu_, (A0)(A1)(X)
                      , ((simd_<type8_<A0>,X>))
                        ((simd_<ints8_<A1>,X>))
                      );

////////////////////////////////////////////////////////////////////////////////
// Overloads implementation
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  template<class Dummy,class X>
  struct  call< tag::shift_right_( tag::simd_<tag::type8_,X> 
                                , tag::simd_<tag::ints8_,X> 
                                )
              , tag::cpu_, Dummy
              >
        : call< tag::shift_right_ ( tag::simd_<tag::unspecified_,X> 
                                  , tag::simd_<tag::unspecified_,X> 
                                  )
              , tag::cpu_, Dummy
              >
  {
  };

  template<class Dummy,class X>
  struct  call< tag::shift_right_( tag::simd_<tag::type16_,X> 
                                , tag::simd_<tag::ints16_,X> 
                                )
              , tag::cpu_, Dummy
              >
        : call< tag::shift_right_( tag::simd_<tag::type8_,X> 
                                , tag::simd_<tag::ints8_,X> 
                                )
              , tag::cpu_, Dummy
              >
  {};

  template<class Dummy,class X>
  struct  call< tag::shift_right_( tag::simd_<tag::type32_,X> 
                                , tag::simd_<tag::ints32_,X> 
                                )
              , tag::cpu_, Dummy
              >
        : call< tag::shift_right_( tag::simd_<tag::type8_,X> 
                                , tag::simd_<tag::ints8_,X> 
                                )
              , tag::cpu_, Dummy
              >
  {};

  template<class Dummy,class X>
  struct  call< tag::shift_right_( tag::simd_<tag::type64_,X> 
                                , tag::simd_<tag::ints64_,X> 
                                )
              , tag::cpu_, Dummy
              >
        : call< tag::shift_right_( tag::simd_<tag::type8_,X> 
                                , tag::simd_<tag::ints8_,X> 
                                )
              , tag::cpu_, Dummy
              >
  {};
} }

#endif

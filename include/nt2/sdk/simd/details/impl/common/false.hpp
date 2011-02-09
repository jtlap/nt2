//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_FALSE_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_FALSE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// in SIMD, False is simply 0 adn forward to its actual optimized version
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::false_, tag::cpu_
                      , (A0)(X), ((target_< simd_< arithmetic_<A0> ,X> >))
                      )

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct  call< tag::false_( tag::target_<tag::simd_<tag::arithmetic_,X> >)
              , tag::cpu_
              , Dummy
              >
        : call< tag::digit_<0>( tag::target_<tag::simd_<tag::arithmetic_,X> >)
              , tag::cpu_
              , Dummy
              >
  {};
} }

#endif

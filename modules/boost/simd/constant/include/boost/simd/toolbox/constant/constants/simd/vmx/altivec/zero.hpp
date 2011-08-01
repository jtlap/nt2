//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_ZERO_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_IMPL_VMX_ALTIVEC_ZERO_HPP_INCLUDED

namespace boost { namespace simd
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::digit_<0>, tag::cpu_, (A0)
                            , ((target_< simd_< arithmetic_<A0>,tag::altivec_> >))
                            )
  {
    typedef A0::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = { simd::native_cast<result_type>(vec_splat_u8(0)) };
      return that;
    }
  };
} }

#endif

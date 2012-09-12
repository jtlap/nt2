//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_SHIFT_RIGHT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/operator/functions/shift_right.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_unsigned.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_right_, boost::simd::tag::altivec_, (A0)(A1)
                            , ((simd_<integer_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<integer_<A1>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
     typedef typename dispatch::meta::as_unsigned<A1>::type type;
     type shift = simd::bitwise_cast<type>(a1);
     return vec_sra(a0(), shift());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_right_, boost::simd::tag::altivec_, (A0)(A1)
                            , ((simd_<single_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<ints32_<A1>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
   {
     typedef typename dispatch::meta::as_unsigned<A1>::type type;
     type shift = simd::bitwise_cast<type>(a1);
     type value = simd::bitwise_cast<type>(a0);
     return simd::bitwise_cast<A0>( vec_sra(value(), shift()) );
   }
  };
} } }

#endif
#endif

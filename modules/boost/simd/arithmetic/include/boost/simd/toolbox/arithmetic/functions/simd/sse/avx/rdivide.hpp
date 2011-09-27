//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_RDIVIDE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_RDIVIDE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/include/constants/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/simd/include/functions/is_eqz.hpp>
#include <boost/simd/include/functions/is_equal.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/valmin.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
 //  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::rdivide_, boost::simd::tag::avx_,
//                           (A0),
//                           ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
//                           ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
//                          )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       const A0 iseqza1 = is_eqz(a1);
//       const A0 c = b_and(eq(a0, Valmin<A0>()), eq(a1, Mone<A0>())); 
//       return ((a0-c)-(iseqza1&a0))/(a1+(iseqza1&One<A0>()));
//     }
//   };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::rdivide_, boost::simd::tag::avx_,
                          (A0),
                          ((simd_<floating_<A0>,boost::simd::tag::avx_>))
                          ((simd_<floating_<A0>,boost::simd::tag::avx_>))
                         )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return divides(a0, a1);
    }
  };
} } }
#endif
#endif

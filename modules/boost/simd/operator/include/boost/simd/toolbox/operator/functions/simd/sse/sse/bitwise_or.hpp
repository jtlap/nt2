//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_BITWISE_OR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_BITWISE_OR_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE_SUPPORT
#include <boost/simd/toolbox/operator/functions/bitwise_or.hpp>
#include <boost/simd/include/functions/genmask.hpp>

// namespace boost { namespace simd { namespace ext
// {
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_or_, boost::simd::tag::sse_,
//                                 (A0),
//                                 ((simd_<logical_<A0>,boost::simd::tag::sse_>))
//                                 ((simd_<logical_<A0>,boost::simd::tag::sse_>))
//                               )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
//     {
//       typedef typename A0::type type; 
//       return bitwise_cast<result_type>(bitwise_or(bitwise_cast<type>(a0), bitwise_cast<type>(a1)));
//     }
//   };
// } } }

#endif
#endif

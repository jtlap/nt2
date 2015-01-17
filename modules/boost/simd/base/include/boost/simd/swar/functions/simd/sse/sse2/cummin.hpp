//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// #ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMMIN_HPP_INCLUDED
// #define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_CUMMIN_HPP_INCLUDED
// #ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

// #include <boost/simd/swar/functions/cummin.hpp>
// #include <boost/simd/include/functions/simd/min.hpp>
// #include <boost/simd/swar/include/functions/shuffle.hpp>

// namespace boost { namespace simd { namespace ext
// {
//   BOOST_DISPATCH_IMPLEMENT (cummin_, boost::simd::tag::sse2_,
//                             (A0),
//                             ((simd_<type8_<A0>,boost::simd::tag::sse_>))
//                            )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
//     {
//       A0 tmp = min(a0,  shuffle<0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14>(a0));
//       tmp =    min(tmp, shuffle<0,1,1,1,4,4,4,5,6,7,8,9,10,11,12,13>(tmp));
//       tmp =    min(tmp, shuffle<0,1,2,3,3,3,3,3,4,5,6,7,8,9,10,11>(tmp));
//       return   min(tmp, shuffle<0,1,2,3,4,5,6,7,7,7,7,7,7,7,7,7>(tmp));
//      }
//   };

//   BOOST_DISPATCH_IMPLEMENT         (cummin_, boost::simd::tag::sse2_,
//                                     (A0),
//                                     ((simd_<type64_<A0>,boost::simd::tag::sse_>))
//                                    )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
//     {
//       return min(a0, shuffle<0,0>(a0));
//     }
//   };

//   BOOST_DISPATCH_IMPLEMENT         (cummin_, boost::simd::tag::sse2_,
//                                     (A0),
//                                     ((simd_<type16_<A0>,boost::simd::tag::sse_>))
//                                    )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
//     {
//        A0 tmp = min(a0,  shuffle<0,0,1,2,3,4,5,6>(a0));
//        tmp =    min(tmp, shuffle<0,1,1,1,4,4,4,5>(tmp));
//        return   min(tmp, shuffle<0,1,2,3,3,3,3,3>(tmp));
//     }
//   };

//   BOOST_DISPATCH_IMPLEMENT         (cummin_, boost::simd::tag::sse2_,
//                                     (A0),
//                                     ((simd_<type32_<A0>,boost::simd::tag::sse_>))
//                                    )
//   {
//     typedef A0 result_type;
//     BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
//     {
//       A0 tmp = min(a0,  shuffle<0,0,1,2>(a0));
//       return   min(tmp, shuffle<0,1,1,1>(tmp));
//     }
//   };
// } } }
// #endif
// #endif

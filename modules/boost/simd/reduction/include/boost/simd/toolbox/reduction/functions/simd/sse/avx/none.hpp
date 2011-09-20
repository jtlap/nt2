//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_NONE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_NONE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/reduction/functions/none.hpp>
#include <boost/simd/include/constants/true.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/sdk/simd/native_cast.hpp>
// take care that is_nez is NECESSARY because the documentation of _mm256_testz_si256/ps/pd
// is far from being accurate...

//#include <iostream>


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
      {
      //      std::cout << "arith" << _mm256_testz_si256(is_nez(a0), True<A0>()) << std::endl; 
      return _mm256_testz_si256(is_nez(a0), True<A0>());
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<uint8_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm256_testz_si256(is_nez(a0), True<A0>());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<int8_<A0>,boost::simd::tag::avx_>))
                       )
  {
    typedef bool result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm256_testz_si256(is_nez(a0), True<A0>());
    }
   };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<float_<A0>,boost::simd::tag::avx_>))
                       )
  {
     typedef bool result_type;
     BOOST_SIMD_FUNCTOR_CALL(1)
     {
      //     std::cout << "ps" << _mm256_testz_ps(is_nez(a0), True<A0>()) << std::endl; 
      return _mm256_testz_ps(is_nez(a0), True<A0>());
     }
   };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
                        (A0),
                        ((simd_<double_<A0>,boost::simd::tag::avx_>))
                       )
  {
     typedef bool result_type;
     BOOST_SIMD_FUNCTOR_CALL(1)
     {
      //      std::cout << "pd" << _mm256_testz_pd(is_nez(a0), True<A0>()) << std::endl; 
      return _mm256_testz_pd(is_nez(a0), True<A0>());
     }
   };
} } }
#endif
#endif


// namespace boost { namespace simd { namespace ext
// {
//    BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
//                         (A0),
//                         ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
//                        )
//   {
//     typedef bool result_type;
//     BOOST_SIMD_FUNCTOR_CALL(1)
//     {
//       typedef typename meta::scalar_of<A0>::type             sctype;
//       typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
//       svtype a00 = { _mm256_extractf128_si256(a0, 0)};
//       if  (any(a00)) return false;
//       svtype a01 = { _mm256_extractf128_si256(a0, 1)};
//       return none(a01);
//     }
//   };
  
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
//                         (A0),
//                         ((simd_<real_<A0>,boost::simd::tag::avx_>))
//                        )
//   {
//     typedef bool result_type;
//     BOOST_SIMD_FUNCTOR_CALL(1)
//     {
//       typedef typename dispatch::meta::as_integer<A0>::type iA0; 
//       return none(bitwise_cast<iA0>(a0)) ;
//     }
//   };
// //   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
// //                         (A0),
// //                         ((simd_<float_<A0>,boost::simd::tag::avx_>))
// //                        )
// //   {
// //     typedef bool result_type;
// //     BOOST_SIMD_FUNCTOR_CALL(1)
// //     {
// //       return _mm256_testz_ps(a0, True<A0>());
// //     }
// //   };
// //   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
// //                         (A0),
// //                         ((simd_<double_<A0>,boost::simd::tag::avx_>))
// //                        )
// //   {
// //     typedef bool result_type;
// //     BOOST_SIMD_FUNCTOR_CALL(1)
// //     {
// //       return _mm256_testz_pd(a0, True<A0>());
// //     }
// //   };
// //   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::none_, boost::simd::tag::avx_,
// //                         (A0),
// //                         ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
// //                        )
// //   {
// //     typedef bool result_type;
// //     BOOST_SIMD_FUNCTOR_CALL(1)
// //     {
// //       typedef native <float, boost::simd::tag::avx_> ftype; 
// //       return none(bitwise_cast<ftype>(a0)) ;
// //     }
// //   };
// } } }  
// #endif
// #endif

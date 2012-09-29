//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_PERMUTE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
#include <boost/simd/toolbox/swar/functions/permute.hpp>
#include <boost/simd/include/functions/make.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/toolbox/swar/functions/details/shuffle.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, boost::simd::tag::ssse3_
                                      , (A0)(I0)(I1)(I2)(I3)
                                      , ((simd_< type32_<A0>,boost::simd::tag::sse_>))
                                      ((unspecified_<I0>))
                                      ((unspecified_<I1>))
                                      ((unspecified_<I2>))
                                      ((unspecified_<I3>))
                                      )
  {
    typedef A0 result_type;
    typedef boost::simd::native<int8_t, tag::sse_>                          i8type; 
    
    result_type operator()(A0 const& a, I0 const &, I1 const&, I2 const&, I3 const&) const
    {
//       std::cout << "ssse3" << std::endl; 
      static const int i0 = I0::value;
      static const int i1 = I1::value;
      static const int i2 = I2::value;
      static const int i3 = I3::value;
#define H0(i) ((i & 3) << 2) 
#define H1(i, inc) ((i < 0) ? -1 : (H0(i)+inc))
      
      return shuf<H1(i0, 0), H1(i0, 1) ,H1(i0, 2), H1(i0, 3),
        H1(i1, 0), H1(i1, 1) ,H1(i1, 2),H1(i1, 3),
        H1(i2, 0), H1(i2, 1) ,H1(i2, 2),H1(i2, 3),
        H1(i3, 0), H1(i3, 1) ,H1(i3, 2),H1(i3, 3) >(a);

#undef H0
#undef H1
    }
  private:
    template< int i0, int i1,  int i2, int i3, int i4, int i5,  int i6, int i7,
      int i8, int i9,  int i10, int i11, int i12, int i13, int i14, int i15> 
      BOOST_FORCEINLINE static 
      A0 shuf( const A0& a)
      {
        typedef boost::simd::native<int8_t, boost::simd::tag::sse_> i8type; 
        __m128i i = boost::simd::make<i8type>(i0,  i1,  i2,  i3,  i4,  i5,   i6,  i7,
                                              i8,  i9,  i10,  i11,   i12,  i13,  i14,  i15);
        return bitwise_cast<A0>(_mm_shuffle_epi8( bitwise_cast<i8type>(a), i));
      }
    
  };
} } }


#endif
#endif

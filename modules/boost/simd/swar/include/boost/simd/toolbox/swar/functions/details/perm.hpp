//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/char.hpp>
#include <iostream>
#define BOOST_SIMD_MM_PERM2(i0, i1) (i0+(i1 << 4))                             \
/**/

namespace boost { namespace simd { namespace details
{
  // Result of the meta permutation
  template<class P, class Card, int I>
  struct index_ : boost::mpl::char_< boost::mpl::apply< typename P::type                                        
                                                      , boost::mpl::int_<I>                             
                                                      , Card                                         
                                                      >::type::value>
  {};

  // Generate the the correct mask
  template<class P, class Card, char Offset, char Idx, char Inc>
  struct generate_ : boost::mpl::char_<(index_<P,Card,Idx>::value<0?-1:(Offset+Inc))>
  {};

  // Permute specialization
  template<class P, std::size_t N>
  struct permute {};

  template<class P>
  struct permute<P,2>
  {
    typedef P permut_t;
    typedef boost::mpl::size_t<2> card_t;

    template<char I, char J>
    struct mask_ 
    : boost::mpl::char_< generate_< permut_t
                                  , card_t
                                  , ((index_<permut_t,card_t,I>::value & 1) << 3)
                                  , I
                                  , J
                                  >::value
                        >
    {};

#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
    static __m128i call()
    {
      return _mm_setr_epi8( mask_<0,0>::value, mask_<0,1>::value 
                          , mask_<0,2>::value, mask_<0,3>::value 
                          , mask_<0,4>::value, mask_<0,5>::value 
                          , mask_<0,6>::value, mask_<0,7>::value 
                          , mask_<1,0>::value, mask_<1,1>::value 
                          , mask_<1,2>::value, mask_<1,3>::value 
                          , mask_<1,4>::value, mask_<1,5>::value 
                          , mask_<1,6>::value, mask_<1,7>::value 
                          );
    }
#elif defined(BOOST_SIMD_HAS_VMX_SUPPORT)
    static __vector unsigned char call()
    {
      __vector unsigned char that = { mask_<0,0>::value, mask_<0,1>::value 
                                    , mask_<0,2>::value, mask_<0,3>::value 
                                    , mask_<0,4>::value, mask_<0,5>::value 
                                    , mask_<0,6>::value, mask_<0,7>::value 
                                    , mask_<1,0>::value, mask_<1,1>::value 
                                    , mask_<1,2>::value, mask_<1,3>::value 
                                    , mask_<1,4>::value, mask_<1,5>::value 
                                    , mask_<1,6>::value, mask_<1,7>::value };
      return that;     
    } 
#endif  
  };

  template<class P>
  struct permute<P,4>
  {
    typedef P permut_t;
    typedef boost::mpl::size_t<4> card_t;  

    template<char I, char J>
    struct mask_ 
    : boost::mpl::char_< generate_< permut_t
                                  , card_t
                                  , ((index_<permut_t,card_t,I>::value & 3) << 2)
                                  , I
                                  , J
                                  >::value
                        >
    {};

#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
    static __m128i call()
    {
      return _mm_setr_epi8( mask_<0, 0>::value, mask_<0, 1>::value 
                          , mask_<0, 2>::value, mask_<0, 3>::value
                          , mask_<1, 0>::value, mask_<1, 1>::value 
                          , mask_<1, 2>::value, mask_<1, 3>::value
                          , mask_<2, 0>::value, mask_<2, 1>::value 
                          , mask_<2, 2>::value, mask_<2, 3>::value
                          , mask_<3, 0>::value, mask_<3, 1>::value 
                          , mask_<3, 2>::value, mask_<3, 3>::value
                          );
    }
#elif defined(BOOST_SIMD_HAS_VMX_SUPPORT)
    static __vector unsigned char call()
    {
      __vector unsigned char that = { mask_<0, 0>::value, mask_<0, 1>::value 
                                    , mask_<0, 2>::value, mask_<0, 3>::value
                                    , mask_<1, 0>::value, mask_<1, 1>::value 
                                    , mask_<1, 2>::value, mask_<1, 3>::value
                                    , mask_<2, 0>::value, mask_<2, 1>::value 
                                    , mask_<2, 2>::value, mask_<2, 3>::value
                                    , mask_<3, 0>::value, mask_<3, 1>::value 
                                    , mask_<3, 2>::value, mask_<3, 3>::value };
      return that;     
    } 
#endif  
  };

  template<class P>
  struct permute<P,8>
  {
    typedef P permut_t;
    typedef boost::mpl::size_t<8> card_t;   

    template<char I, char J>
    struct mask_ 
    : boost::mpl::char_< generate_< permut_t
                                  , card_t
                                  , ((index_<permut_t,card_t,I>::value & 7) << 1)
                                  , I
                                  , J
                                  >::value
                        >
    {};

#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
    static __m128i call()
    {
      return _mm_setr_epi8( mask_<0, 0>::value, mask_<0, 1>::value 
                          , mask_<1, 0>::value, mask_<1, 1>::value
                          , mask_<2, 0>::value, mask_<2, 1>::value
                          , mask_<3, 0>::value, mask_<3, 1>::value
                          , mask_<4, 0>::value, mask_<4, 1>::value 
                          , mask_<5, 0>::value, mask_<5, 1>::value
                          , mask_<6, 0>::value, mask_<6, 1>::value
                          , mask_<7, 0>::value, mask_<7, 1>::value
                          );
    }
#elif defined(BOOST_SIMD_HAS_VMX_SUPPORT)
    static __vector unsigned char call()
    {
      __vector unsigned char that = { mask_<0, 0>::value, mask_<0, 1>::value 
                                    , mask_<1, 0>::value, mask_<1, 1>::value
                                    , mask_<2, 0>::value, mask_<2, 1>::value
                                    , mask_<3, 0>::value, mask_<3, 1>::value
                                    , mask_<4, 0>::value, mask_<4, 1>::value 
                                    , mask_<5, 0>::value, mask_<5, 1>::value
                                    , mask_<6, 0>::value, mask_<6, 1>::value
                                    , mask_<7, 0>::value, mask_<7, 1>::value };
      return that;     
    } 
#endif  
  };
  template<class P>
  struct permute<P,16>
  {
    typedef P permut_t;
    typedef boost::mpl::size_t<16> card_t;  

    template<char I>
    struct mask_ 
    : boost::mpl::char_<(index_<P,card_t,I>::value)<0?-1:index_<P,card_t,I>::value>
    {};

#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
    static __m128i call()
    {
      return _mm_setr_epi8( mask_< 0>::value, mask_< 1>::value
                          , mask_< 2>::value, mask_< 3>::value
                          , mask_< 4>::value, mask_< 5>::value
                          , mask_< 6>::value, mask_< 7>::value
                          , mask_< 8>::value, mask_< 9>::value
                          , mask_<10>::value, mask_<11>::value
                          , mask_<12>::value, mask_<13>::value
                          , mask_<14>::value, mask_<15>::value
                          );
    }
#elif defined(BOOST_SIMD_HAS_VMX_SUPPORT)
    static __vector unsigned char call()
    {
      __vector unsigned char that = { mask_< 0>::value, mask_< 1>::value
                                    , mask_< 2>::value, mask_< 3>::value
                                    , mask_< 4>::value, mask_< 5>::value
                                    , mask_< 6>::value, mask_< 7>::value
                                    , mask_< 8>::value, mask_< 9>::value
                                    , mask_<10>::value, mask_<11>::value
                                    , mask_<12>::value, mask_<13>::value
                                    , mask_<14>::value, mask_<15>::value };
      return that;     
    } 
#endif  
  };

#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
template< unsigned int i0, unsigned int i1>
BOOST_FORCEINLINE
__m256 perm2(__m256 const lower, __m256 const upper)
{
  return _mm256_permute2f128_ps( lower, upper
                          , BOOST_SIMD_MM_PERM2(i0, i1)
                          );
}
template< unsigned int i0, unsigned int i1>
BOOST_FORCEINLINE
__m256d perm2(__m256d const lower, __m256d const upper)
{
  return _mm256_permute2f128_pd( lower, upper
                          , BOOST_SIMD_MM_PERM2(i0, i1)
                          );
}
template< unsigned int i0, unsigned int i1>
BOOST_FORCEINLINE
__m256i perm2(__m256i const lower, __m256i const upper)
{
  return _mm256_permute2f128_si256( lower, upper
                          , BOOST_SIMD_MM_PERM2(i0, i1)
                          );
}

#undef BOOST_SIMD_MM_PERM2
#endif
} } }
#undef V
#undef H1
#endif

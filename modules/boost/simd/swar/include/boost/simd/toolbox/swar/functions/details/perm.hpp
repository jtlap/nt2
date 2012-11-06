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

#define BOOST_SIMD_MM_PERM2(i0, i1) (i0+(i1 << 4))                             \
/**/
#define V(i) boost::mpl::apply<permut_t                                        \
                              ,boost::mpl::int_<i>                             \
                              ,card_t                                          \
                              >::type::value                                   \
/**/
#define H1(i, inc) ((V(i) < 0) ? -1 : (H0(i)+inc))                             \
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

    template<char I>
    struct offset_ : boost::mpl::char_<((index_<permut_t,card_t,I>::value & 1) << 3)>
    {};

    static __m128i call()
    {
      return _mm_setr_epi8( generate_<permut_t,card_t,offset_<0>::value,0,0>::value
                          , generate_<permut_t,card_t,offset_<0>::value,0,1>::value //H1(0, 1) 
                          , generate_<permut_t,card_t,offset_<0>::value,0,2>::value //H1(0, 2)
                          , generate_<permut_t,card_t,offset_<0>::value,0,3>::value //H1(0, 3)
                          , generate_<permut_t,card_t,offset_<0>::value,0,4>::value //H1(0, 4)
                          , generate_<permut_t,card_t,offset_<0>::value,0,5>::value //H1(0, 5) 
                          , generate_<permut_t,card_t,offset_<0>::value,0,6>::value //H1(0, 6)
                          , generate_<permut_t,card_t,offset_<0>::value,0,7>::value //H1(0, 7)
                          , generate_<permut_t,card_t,offset_<1>::value,1,0>::value //H1(1, 0)
                          , generate_<permut_t,card_t,offset_<1>::value,1,1>::value //H1(1, 1) 
                          , generate_<permut_t,card_t,offset_<1>::value,1,2>::value //H1(1, 2)
                          , generate_<permut_t,card_t,offset_<1>::value,1,3>::value //H1(1, 3)
                          , generate_<permut_t,card_t,offset_<1>::value,1,4>::value //H1(1, 4)
                          , generate_<permut_t,card_t,offset_<1>::value,1,5>::value //H1(1, 5) 
                          , generate_<permut_t,card_t,offset_<1>::value,1,6>::value //H1(1, 6)
                          , generate_<permut_t,card_t,offset_<1>::value,1,7>::value //H1(1, 7)
                          );
    }
  };

  template<class P>
  struct permute<P,4>
  {
    typedef typename P::type permut_t;
    typedef boost::mpl::size_t<4> card_t;  
    static __m128i call()
    {
      #define H0(i) ((V(i) & 3) << 2)
      return _mm_setr_epi8( H1(0, 0), H1(0, 1) ,H1(0, 2), H1(0, 3)
                          , H1(1, 0), H1(1, 1) ,H1(1, 2), H1(1, 3)
                          , H1(2, 0), H1(2, 1) ,H1(2, 2), H1(2, 3)
                          , H1(3, 0), H1(3, 1) ,H1(3, 2), H1(3, 3)
                          );
    }
    #undef H0
  };

  template<class P>
  struct permute<P,8>
  {
    typedef typename P::type permut_t;
    typedef boost::mpl::size_t<8> card_t;   
    static __m128i call()
    {
      #define H0(i) ((V(i) & 7) << 1)
      return _mm_setr_epi8( H1(0, 0), H1(0, 1) ,H1(1, 0), H1(1, 1)
                          , H1(2, 0), H1(2, 1) ,H1(3, 0), H1(3, 1)
                          , H1(4, 0), H1(4, 1) ,H1(5, 0), H1(5, 1)
                          , H1(6, 0), H1(6, 1) ,H1(7, 0), H1(7, 1)
                          );
    }
    #undef H0
  };

  template<class P>
  struct permute<P,16>
  {
    typedef typename P::type permut_t;
    typedef boost::mpl::size_t<16> card_t;  
    static __m128i call()
    {
      #define H(i) ((V(i) < 0) ? -1 : V(i))
      return _mm_setr_epi8( H( 0), H( 1), H( 2), H(3)
                          , H( 4), H( 5), H( 6), H(7)
                          , H( 8), H( 9), H(10), H(11)
                          , H(12), H(13), H(14), H(15)
                          );
    }
    #undef H
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

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_PERM_HPP_INCLUDED

#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/integer/static_log2.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/int.hpp>

#define BOOST_SIMD_MM_PERM2(i0, i1) (i0+(i1 << 4))

namespace boost { namespace simd { namespace details
{
  // Result of the meta permutation
  template<class P, class Card, int I>
  struct index_ : boost::mpl::apply < typename P::type
                                    , boost::mpl::int_<I>
                                    , Card
                                    >::type
  {};

  // Generate the the correct mask
  template<class P, class Card, char Offset, char Idx, char Inc>
  struct  generate_
        : boost::mpl::int_<((0>index_<P,Card,Idx>::value)?-1:(Offset+Inc))>
  {};

  // Permute specialization
  template<class P, class Type, int N> struct permute
  {
    template<char I>
    struct  mask_
          : generate_ < P
                      , boost::mpl::int_<N>
                      , ( ( index_< P
                                  , boost::mpl::int_<N>
                                  , (I / (16/N))
                                  >::value
                          ) << (4-boost::static_log2<N>::value)
                        )
                      , I / (16/N)
                      , I % (16/N)
                      >
    {};

    static BOOST_FORCEINLINE Type call()
    {
      return make<Type> ( mask_< 0>::value, mask_< 1>::value
                        , mask_< 2>::value, mask_< 3>::value
                        , mask_< 4>::value, mask_< 5>::value
                        , mask_< 6>::value, mask_< 7>::value
                        , mask_< 8>::value, mask_< 9>::value
                        , mask_<10>::value, mask_<11>::value
                        , mask_<12>::value, mask_<13>::value
                        , mask_<14>::value, mask_<15>::value
                        );
    }
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

#endif

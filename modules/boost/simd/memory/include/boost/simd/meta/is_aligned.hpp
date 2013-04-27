//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_META_IS_ALIGNED_HPP_INCLUDED

/*!
  @file
  @brief Define and implements is_aligned and is_aligned_c
**/

#include <boost/simd/meta/is_power_of_2.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <cstddef>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Check alignment of arbitrary integral constant

    is_aligned_c is a Boolean meta-function that check if any given
    Integral Constant @c V is aligned on any given power of two boundary @c N.

    By default @c N is equal to current architecture preferred alignment.

    If @c N is not a power of two, a BOOST_SIMD_INVALID_ALIGNMENT_VALUE static
    assertion is triggered.

    @par Semantic:
    For any given Integral Constants @c N and @c V:

    @code
    typedef is_aligned_c<V,N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::bool<(V % N) == 0>::type r;
    @endcode

    @tparam N Integral constant to check
  **/
  template<std::size_t V, std::size_t N = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct  is_aligned_c
#if !defined(BOOST_DOXYGEN_ONLY)
        : boost::mpl::bool_<!(V & (N-1) )>
#endif
  {
    //==========================================================================
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    // If this static assert triggers, a call to is_aligned_c has been issued
    // with a non-power of 2 boundary argument.
    //               ****BOOST_SIMD_INVALID_ALIGNMENT_VALUE****
    //==========================================================================
    BOOST_MPL_ASSERT_MSG
    ( (boost::simd::meta::is_power_of_2_c<N>::value)
    , BOOST_SIMD_INVALID_ALIGNMENT_VALUE
    , (boost::mpl::int_<N>)
    );
  };

  /*!
    @brief Check alignment of arbitrary integral constant

    is_aligned is a Boolean meta-function that check if any given
    Integral Constant @c V is aligned on any given power of two boundary @c N.

    By default @c N is equal to current architecture preferred alignment.

    If @c N is not a power of two, a static assertion is triggered.

    @par Semantic:
    For any given Integral Constants @c N and @c V:

    @code
    typedef is_aligned<V,N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef is_aligned_c<V::value,N::value>::type r;
    @endcode

    @tparam N Integral constant to check
  **/
  template<class V, class N = boost::mpl::size_t<BOOST_SIMD_CONFIG_ALIGNMENT> >
  struct  is_aligned
#if !defined(BOOST_DOXYGEN_ONLY)
        : is_aligned_c<V::value,N::value>
#endif
  {};
} } }

#endif

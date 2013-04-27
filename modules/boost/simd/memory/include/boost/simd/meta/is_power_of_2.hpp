//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_META_IS_POWER_OF_2_HPP_INCLUDED

/*!
  @file
  @brief Define and implements is_power_of_2 and is_power_of_2_c
**/

#include <cstddef>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Checks if integral constant is a power of two.

    is_power_of_2_c is a Boolean meta-function that check if any given
    Integral Constant @c N is a non null power of two.

    @par Semantic:
    For any given Integral Constant @c N:

    @code
    typedef is_power_of_2_c<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::bool<(!(N & (N - 1)) && N)> r;
    @endcode

    @tparam N Integral constant to check
  **/
  template<std::size_t N> struct  is_power_of_2_c
#if !defined(BOOST_DOXYGEN_ONLY)
        : boost::mpl::bool_<(!(N & (N - 1)) && N)>
#endif
  {};

  /*!
    @brief Checks if integral constant is a power of two.

    is_power_of_2_c is a Boolean meta-function that check if any given
    Integral Constant @c N is a non null power of two.

    @par Semantic:
    For any given Integral Constant @c N:

    @code
    typedef is_power_of_2<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef is_power_of_2_c<N::value>::type r;
    @endcode

    @tparam N Integral constant to check
  **/
  template<class N> struct  is_power_of_2
#if !defined(BOOST_DOXYGEN_ONLY)
        : boost::mpl::bool_<(!(N::value & (N::value - 1)) && N::value)>
#endif
  {};
} } }

#endif

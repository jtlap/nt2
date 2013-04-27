//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_PREV_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_META_PREV_POWER_OF_2_HPP_INCLUDED

/*!
  @file
  @brief Define and implements prev_power_of_2 and prev_power_of_2_c
**/

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>

namespace boost { namespace simd {  namespace details
{
  /// INTERNAL ONLY
  template<std::size_t N> struct prev_power_of_2_impl
  {
    BOOST_STATIC_CONSTANT(std::size_t, x0    = N               );
    BOOST_STATIC_CONSTANT(std::size_t, x1    = x0 | (x0 >>  1) );
    BOOST_STATIC_CONSTANT(std::size_t, x2    = x1 | (x1 >>  2) );
    BOOST_STATIC_CONSTANT(std::size_t, x3    = x2 | (x2 >>  4) );
    BOOST_STATIC_CONSTANT(std::size_t, x4    = x3 | (x3 >>  8) );
    BOOST_STATIC_CONSTANT(std::size_t, x5    = x4 | (x4 >> 16) );
    BOOST_STATIC_CONSTANT(std::size_t, value = (x5 >> 1) + 1   );
  };

  /// INTERNAL ONLY
  template<> struct prev_power_of_2_impl<0>
  {
    BOOST_STATIC_CONSTANT(std::size_t, value = 0 );
  };
} } }

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Evaluates previous power of 2

    prev_power_of_2_c is a meta-function that computes the power of 2
    lesser or equal to any given Integral Constant @c N.

    @par Semantic:
    For any given Integral Constant @c N:

    @code
    typedef prev_power_of_2_c<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef mpl::size_t<M> r;
    @endcode

    Where @c M is lesser or equal to N and so that it exists a given @c P so
    that @c M is equal to 2 at the power of @c P.

    @tparam N Integral constant to downgrade
  **/
  template<std::size_t N> struct  prev_power_of_2_c
#if !defined(BOOST_DOXYGEN_ONLY)
        : boost::mpl::size_t<details::prev_power_of_2_impl<N>::value>
#endif
  {};

  /*!
    @brief Evaluates previous power of 2

    prev_power_of_2 is a meta-function that computes the power of 2
    lesser or equal to any given Integral Constant @c N.

    @par Semantic:
    For any given Integral Constant @c N:

    @code
    typedef prev_power_of_2<N>::type r;
    @endcode

    is equivalent to:

    @code
    typedef prev_power_of_2_c<N::value>::type r;
    @endcode

    @tparam N Integral Constant to downgrade
  **/
  template<class N> struct  prev_power_of_2
#if !defined(BOOST_DOXYGEN_ONLY)
        : boost::mpl::integral_c< typename N::value_type
                                , details::prev_power_of_2_impl<N::value>::value
                                >
#endif
  {};
} } }

#endif

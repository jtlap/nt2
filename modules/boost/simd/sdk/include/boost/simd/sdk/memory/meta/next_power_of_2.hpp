//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_SDK_MEMORY_META_NEXT_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_META_NEXT_POWER_OF_2_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>

namespace boost { namespace simd { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Integral meta-function computing the power of 2 less or equal to any
  // integral constant.
  // Documentation: next_power_of_2_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N>
  struct prev_power_of_2_c
  {
    BOOST_STATIC_CONSTANT(std::size_t, x0    = N               );
    BOOST_STATIC_CONSTANT(std::size_t, x1    = x0 | (x0 >>  1) );
    BOOST_STATIC_CONSTANT(std::size_t, x2    = x1 | (x1 >>  2) );
    BOOST_STATIC_CONSTANT(std::size_t, x3    = x2 | (x2 >>  4) );
    BOOST_STATIC_CONSTANT(std::size_t, x4    = x3 | (x3 >>  8) );
    BOOST_STATIC_CONSTANT(std::size_t, x5    = x4 | (x4 >> 16) );
    BOOST_STATIC_CONSTANT(std::size_t, value = (x5 >> 1) + 1   );
    typedef boost::mpl::size_t<value> type;
  };
  template<std::size_t N>
  std::size_t const prev_power_of_2_c<N>::value;

  //////////////////////////////////////////////////////////////////////////////
  // Integral meta-function computing the power of 2 less or equal to any
  // Integral Constant.
  // Documentation: next_power_of_2.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class N>
  struct  prev_power_of_2
        : boost::mpl::integral_c< typename N::value_type
                                , prev_power_of_2_c<N::value>::value
                                > {};

  //////////////////////////////////////////////////////////////////////////////
  // Integral meta-function computing the power of 2 greater or equal to any
  // integral constant.
  // Documentation: next_power_of_2_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N>
  struct next_power_of_2_c
  {
    BOOST_STATIC_CONSTANT(std::size_t, x0    = N-1             );
    BOOST_STATIC_CONSTANT(std::size_t, x1    = x0 | (x0 >>  1) );
    BOOST_STATIC_CONSTANT(std::size_t, x2    = x1 | (x1 >>  2) );
    BOOST_STATIC_CONSTANT(std::size_t, x3    = x2 | (x2 >>  4) );
    BOOST_STATIC_CONSTANT(std::size_t, x4    = x3 | (x3 >>  8) );
    BOOST_STATIC_CONSTANT(std::size_t, x5    = x4 | (x4 >> 16) );
    BOOST_STATIC_CONSTANT(std::size_t, value = x5 + 1          );
    typedef boost::mpl::size_t<value> type;
  };
  template<std::size_t N>
  std::size_t const next_power_of_2_c<N>::value;

  //////////////////////////////////////////////////////////////////////////////
  // Integral meta-function computing the power of 2 greater or equal to any
  // Integral Constant.
  // Documentation: next_power_of_2.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class N>
  struct  next_power_of_2
        : boost::mpl::integral_c< typename N::value_type
                                , next_power_of_2_c<N::value>::value
                                > {};
} } }


#endif

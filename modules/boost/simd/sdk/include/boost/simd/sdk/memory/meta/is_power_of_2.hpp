//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_META_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_META_IS_POWER_OF_2_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/bool.hpp>

namespace boost { namespace simd {  namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Boolean meta-function checking if a Integral Constant is a power of 2
  // Documentation: is_power_of_2.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N>
  struct is_power_of_2_c : boost::mpl::bool_<(!(N & (N - 1)) && N)> {};

  //////////////////////////////////////////////////////////////////////////////
  // Boolean meta-function checking if a compile-time integral is a power of 2
  // Documentation: is_power_of_2_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class N>
  struct is_power_of_2 : is_power_of_2_c<N::value> {};
} } }

#endif

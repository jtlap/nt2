//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_MEMORY_META_NEXT_POWER_OF_2_HPP_INCLUDED
#define NT2_SDK_MEMORY_META_NEXT_POWER_OF_2_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>

namespace nt2 { namespace details
{
  template<std::size_t N> struct next_power_of_2_impl
  {
    BOOST_STATIC_CONSTANT(std::size_t, x0    = N-1            );
    BOOST_STATIC_CONSTANT(std::size_t, x1    = x0 | (x0 >> 1) );
    BOOST_STATIC_CONSTANT(std::size_t, x2    = x1 | (x1 >> 1) );
    BOOST_STATIC_CONSTANT(std::size_t, x3    = x2 | (x2 >> 1) );
    BOOST_STATIC_CONSTANT(std::size_t, x4    = x3 | (x3 >> 1) );
    BOOST_STATIC_CONSTANT(std::size_t, x5    = x4 | (x4 >> 1) );
    BOOST_STATIC_CONSTANT(std::size_t, value = x5 + 1         );
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Boolean meta-function computing the power of 2 greater or equal to any
  // integral constant.
  // Documentation: next_power_of_2_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t N>
  struct  next_power_of_2_c
        : boost::mpl::size_t<details::next_power_of_2_impl<N>::value> {};

  //////////////////////////////////////////////////////////////////////////////
  // Boolean meta-function computing the power of 2 greater or equal to any
  // Integral Constant.
  // Documentation: next_power_of_2.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class N>
  struct  next_power_of_2
        : boost::mpl::integral_c< typename N::value_type
                                , next_power_of_2_c<N::value>::value
                                > {};
} }


#endif

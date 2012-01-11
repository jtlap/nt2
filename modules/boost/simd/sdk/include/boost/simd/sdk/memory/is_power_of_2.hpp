/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_IS_POWER_OF_2_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_IS_POWER_OF_2_HPP_INCLUDED

#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/simd/sdk/memory/meta/is_power_of_2.hpp>
#include <boost/dispatch/functor/preprocessor/function.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check if a value is a power of 2
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd
{
  namespace tag { struct is_power_of_2_ {}; }
  namespace memory
  {
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_power_of_2_, is_power_of_2, 1);
  }
} }

namespace boost { namespace dispatch
{
  template<>
  struct default_site< boost::simd::tag::is_power_of_2_, void >
  {
    typedef tag::cpu_ type;
  };
} }

#include <boost/simd/sdk/memory/details/is_power_of_2.hpp>

#endif

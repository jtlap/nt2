/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Support for basic SIMD extensions - Note those are themselves extendables
////////////////////////////////////////////////////////////////////////////////
//#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/error/warning.hpp>

////////////////////////////////////////////////////////////////////////////////
// Regular SIMD extensions
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/extensions/sse.hpp>
#include <boost/simd/sdk/simd/extensions/altivec.hpp>
#include <boost/simd/sdk/simd/extensions/none.hpp>

#include <boost/dispatch/functor/forward.hpp>
namespace boost { namespace dispatch 
{
  template<class Tag>
  struct default_site<Tag>
  {
    typedef BOOST_SIMD_DEFAULT_SITE type;
  };
} }

#endif

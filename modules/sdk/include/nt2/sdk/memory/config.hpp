/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_CONFIG_HPP_INCLUDED
#define NT2_SDK_MEMORY_CONFIG_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Memory config header
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/config/types.hpp>
#include <boost/simd/sdk/memory/config.hpp>

#define NT2_CONFIG_SUPPORT_POSIX_MEMALIGN BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN

////////////////////////////////////////////////////////////////////////////////
// Small byte typedef for memory components
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace memory
{
  typedef nt2::uint8_t byte;
} }

#endif

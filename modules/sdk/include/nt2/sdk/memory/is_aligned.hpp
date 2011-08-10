/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_IS_ALIGNED_HPP_INCLUDED
#define NT2_SDK_MEMORY_IS_ALIGNED_HPP_INCLUDED

#include <nt2/sdk/memory/parameters.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>

////////////////////////////////////////////////////////////////////////////////
// Check if a value is aligned on some power of 2 alignment boundary
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  namespace tag { using boost::simd::tag::is_aligned_; }

  namespace memory
  {
    using boost::simd::memory::is_aligned;
} }

#endif

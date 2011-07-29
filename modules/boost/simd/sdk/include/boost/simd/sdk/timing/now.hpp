/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_TIMING_NOW_HPP_INCLUDED
#define BOOST_SIMD_SDK_TIMING_NOW_HPP_INCLUDED

#include <boost/simd/sdk/config/types.hpp>

namespace boost { namespace simd { namespace details
{
  typedef boost::simd::uint64_t  cycles_t;
  double    now();
} } }

#include <boost/simd/sdk/timing/impl/cycles.hpp>

#endif

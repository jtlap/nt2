/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_DOMAIN_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_DOMAIN_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/proto/domain.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Tell proto that in the simd::domain, all expressions should be
  // wrapped in simd::expr<> using simd::generator
  ////////////////////////////////////////////////////////////////////////////
  struct domain : boost::proto::domain< generator
                                      , grammar
                                      >
  {
  };
} }

#endif

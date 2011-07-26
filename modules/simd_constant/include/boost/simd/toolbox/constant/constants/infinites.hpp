//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INFINITES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INFINITES_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Generating an infinite constant
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include.hpp>
#include <boost/simd/sdk/constant/common.hpp>

namespace boost { namespace simd { namespace tag
{
  struct inf_   {}; struct m_inf_ {}; struct nan_  {};
} } }

namespace boost { namespace simd
{
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::inf_    , Inf   )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::m_inf_  , Minf  )
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::nan_    , Nan   )
} }

#include <boost/simd/toolbox/constant/constants/scalar/infinites.hpp>
#include <boost/simd/toolbox/constant/constants/simd/all/infinites.hpp>

#endif

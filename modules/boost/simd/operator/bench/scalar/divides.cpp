/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/simd/include/functor.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <nt2/sdk/unit/benchmark.hpp>

////////////////////////////////////////////////////////////////////////////////
// Runtime benchmark for functor<divide_>
////////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::divides_;
using namespace boost;

////////////////////////////////////////////////////////////////////////////////
// Scalar benchmark - each test are divided in 2 to avoid x/0
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TIMING( divides_ , ((double, 0.1     , 10000. ))((double, 0.1     , 10000. )) )
BOOST_SIMD_TIMING( divides_ , ((double, -10000. , -0.1   ))((double, -10000. , -0.1   )) )
BOOST_SIMD_TIMING( divides_ , ((float , 0.1f    , 10000.f))((float , 0.1f    , 10000.f)) )
BOOST_SIMD_TIMING( divides_ , ((float , -10000.f, -0.1f  ))((float , -10000.f, -0.1f  )) )

BOOST_SIMD_TIMING( divides_ , ((boost::simd::int64_t, 1     , 10000))((boost::simd::int64_t, 1     , 10000)) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int64_t, -10000, -1   ))((boost::simd::int64_t, -10000, -1   )) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int32_t, 1     , 10000))((boost::simd::int32_t, 1     , 10000)) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int32_t, -10000, -1   ))((boost::simd::int32_t, -10000, -1   )) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int16_t, 1     , 32768))((boost::simd::int16_t, 1     , 32768)) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int16_t, -32768, -1   ))((boost::simd::int16_t, -32768, -1   )) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int8_t , 1     , 128  ))((boost::simd::int8_t , 1     , 128  )) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::int8_t , -128  , -1   ))((boost::simd::int8_t , -128  , -1   )) )

BOOST_SIMD_TIMING( divides_ , ((boost::simd::uint64_t , 1, ~0ULL))((boost::simd::uint64_t , 1, ~0ULL)) )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::uint32_t , 1, ~0U))((boost::simd::uint32_t   , 1, ~0U))   )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::uint16_t , 1, 65535))((boost::simd::uint16_t , 1, 6535))  )
BOOST_SIMD_TIMING( divides_ , ((boost::simd::uint8_t  , 1, 255))((boost::simd::uint8_t    , 1, 255))   )


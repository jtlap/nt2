/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/simd/include/functor.hpp>
#include <boost/simd/include/functions/unary_plus.hpp>
#include <boost/simd/sdk/unit/benchmark.hpp>

////////////////////////////////////////////////////////////////////////////////
// Runtime benchmark for functor<unary_plus_>
////////////////////////////////////////////////////////////////////////////////
using boost::simd::tag::unary_plus_;
using namespace boost;

////////////////////////////////////////////////////////////////////////////////
// Symmetric range
////////////////////////////////////////////////////////////////////////////////
#define RS(T,V) ((T, -V , V))

////////////////////////////////////////////////////////////////////////////////
// Scalar benchmark
////////////////////////////////////////////////////////////////////////////////
BOOST_SIMD_TIMING( unary_plus_ , RS(double,2000000))
BOOST_SIMD_TIMING( unary_plus_ , RS(float ,2000000))
BOOST_SIMD_TIMING( unary_plus_ , RS(boost::simd::int64_t,2000000))
BOOST_SIMD_TIMING( unary_plus_ , RS(boost::simd::int32_t,2000000))
BOOST_SIMD_TIMING( unary_plus_ , RS(boost::simd::int16_t,32768))
BOOST_SIMD_TIMING( unary_plus_ , RS(boost::simd::int8_t,127))
BOOST_SIMD_TIMING( unary_plus_ , ((boost::simd::uint64_t, 0, ~0ULL)) )
BOOST_SIMD_TIMING( unary_plus_ , ((boost::simd::uint32_t, 0, ~0U)) )
BOOST_SIMD_TIMING( unary_plus_ , ((boost::simd::uint16_t, 0, 65535)) )
BOOST_SIMD_TIMING( unary_plus_ , ((boost::simd::uint8_t , 0, 255)) )

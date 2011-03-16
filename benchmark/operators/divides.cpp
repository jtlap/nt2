/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/include/functor.hpp>
#include <nt2/sdk/unit/benchmark.hpp>

////////////////////////////////////////////////////////////////////////////////
// Runtime benchmark for functor<divide_>
////////////////////////////////////////////////////////////////////////////////
using nt2::tag::divides_;
using namespace nt2;

////////////////////////////////////////////////////////////////////////////////
// Scalar benchmark - each test are divided in 2 to avoid x/0
////////////////////////////////////////////////////////////////////////////////
NT2_TIMING( divides_ , ((double, 0.1     , 10000. ))((double, 0.1     , 10000. )) )
NT2_TIMING( divides_ , ((double, -10000. , -0.1   ))((double, -10000. , -0.1   )) )
NT2_TIMING( divides_ , ((float , 0.1f    , 10000.f))((float , 0.1f    , 10000.f)) )
NT2_TIMING( divides_ , ((float , -10000.f, -0.1f  ))((float , -10000.f, -0.1f  )) )

NT2_TIMING( divides_ , ((nt2::int64_t, 1     , 10000))((nt2::int64_t, 1     , 10000)) )
NT2_TIMING( divides_ , ((nt2::int64_t, -10000, -1   ))((nt2::int64_t, -10000, -1   )) )
NT2_TIMING( divides_ , ((nt2::int32_t, 1     , 10000))((nt2::int32_t, 1     , 10000)) )
NT2_TIMING( divides_ , ((nt2::int32_t, -10000, -1   ))((nt2::int32_t, -10000, -1   )) )
NT2_TIMING( divides_ , ((nt2::int16_t, 1     , 32768))((nt2::int16_t, 1     , 32768)) )
NT2_TIMING( divides_ , ((nt2::int16_t, -32768, -1   ))((nt2::int16_t, -32768, -1   )) )
NT2_TIMING( divides_ , ((nt2::int8_t , 1     , 128  ))((nt2::int8_t , 1     , 128  )) )
NT2_TIMING( divides_ , ((nt2::int8_t , -128  , -1   ))((nt2::int8_t , -128  , -1   )) )

NT2_TIMING( divides_ , ((nt2::uint64_t , 1, ~0ULL))((nt2::uint64_t , 1, ~0ULL)) )
NT2_TIMING( divides_ , ((nt2::uint32_t , 1, ~0U))((nt2::uint32_t   , 1, ~0U))   )
NT2_TIMING( divides_ , ((nt2::uint16_t , 1, 65535))((nt2::uint16_t , 1, 6535))  )
NT2_TIMING( divides_ , ((nt2::uint8_t  , 1, 255))((nt2::uint8_t    , 1, 255))   )


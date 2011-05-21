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
// Runtime benchmark for functor<plus_>
////////////////////////////////////////////////////////////////////////////////
using nt2::tag::plus_;
using namespace nt2;

////////////////////////////////////////////////////////////////////////////////
// Symmetric range
////////////////////////////////////////////////////////////////////////////////
#define RS(T,V) ((T, -V , V))((T, -V , V))

////////////////////////////////////////////////////////////////////////////////
// Scalar benchmark
////////////////////////////////////////////////////////////////////////////////
NT2_TIMING( plus_ , RS(double,10000.))
NT2_TIMING( plus_ , RS(float,10000.f))
NT2_TIMING( plus_ , RS(nt2::int64_t,2000000))
NT2_TIMING( plus_ , RS(nt2::int32_t,2000000))
NT2_TIMING( plus_ , RS(nt2::int16_t,32768))
NT2_TIMING( plus_ , RS(nt2::int8_t,127))
NT2_TIMING( plus_ , ((nt2::uint64_t, 0, ~0ULL))((nt2::uint64_t, 0,  ~0ULL)) )
NT2_TIMING( plus_ , ((nt2::uint32_t, 0, ~0U))((nt2::uint32_t, 0,  ~0U)) )
NT2_TIMING( plus_ , ((nt2::uint16_t, 0, 65535))((nt2::uint16_t, 0, 65535)) )
NT2_TIMING( plus_ , ((nt2::uint8_t , 0, 255))((nt2::uint8_t, 0, 255)) )


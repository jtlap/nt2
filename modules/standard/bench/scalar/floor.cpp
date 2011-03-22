//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/standard/include/floor.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<floor_> from standard
//////////////////////////////////////////////////////////////////////////////
using nt2::standard::tag::floor_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::standard::tag::floor_,(RS(float,-10000.0f,10000.0f)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(double,-10000.0,10000.0)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(int64_t,-10000,10000)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(int32_t,-10000,10000)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(int16_t,-32768,32767)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(int8_t,-128,127)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(uint64_t,0,65535)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(uint32_t,0,65535)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(uint16_t,0,65535)))
NT2_TIMING(nt2::standard::tag::floor_,(RS(uint8_t,0,255)))

#undef RS
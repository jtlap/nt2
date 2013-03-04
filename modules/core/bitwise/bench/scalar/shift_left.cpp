//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/bitwise/include/functions/shift_left.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<shift_left_> from bitwise
//////////////////////////////////////////////////////////////////////////////
using nt2::functors::shift_left_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::functors::shift_left_,(RS(float,-10000.0f,10000.0f))(RS(int32_t,0,31)))
NT2_TIMING(nt2::functors::shift_left_,(RS(double,-10000.0,10000.0))(RS(int64_t,0,63)))
NT2_TIMING(nt2::functors::shift_left_,(RS(int64_t,-10000,10000))(RS(int64_t,0,63)))
NT2_TIMING(nt2::functors::shift_left_,(RS(int32_t,-10000,10000))(RS(int32_t,0,31)))
NT2_TIMING(nt2::functors::shift_left_,(RS(int16_t,-32768,32767))(RS(int16_t,0,16)))
NT2_TIMING(nt2::functors::shift_left_,(RS(int8_t,-128,127))(RS(int8_t,0,7)))
NT2_TIMING(nt2::functors::shift_left_,(RS(uint64_t,0,65535))(RS(uint64_t,0,63)))
NT2_TIMING(nt2::functors::shift_left_,(RS(uint32_t,0,65535))(RS(uint32_t,0,31)))
NT2_TIMING(nt2::functors::shift_left_,(RS(uint16_t,0,65535))(RS(uint16_t,0,16)))
NT2_TIMING(nt2::functors::shift_left_,(RS(uint8_t,0,255))(RS(uint8_t,0,7)))

#undef RS

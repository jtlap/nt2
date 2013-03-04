//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/libc/include/functions/floor.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<float,ext_t> vfloat;
typedef nt2::simd::native<double,ext_t> vdouble;
typedef nt2::simd::native<int64_t,ext_t> vint64_t;
typedef nt2::simd::native<int32_t,ext_t> vint32_t;
typedef nt2::simd::native<int16_t,ext_t> vint16_t;
typedef nt2::simd::native<int8_t,ext_t> vint8_t;
typedef nt2::simd::native<uint64_t,ext_t> vuint64_t;
typedef nt2::simd::native<uint32_t,ext_t> vuint32_t;
typedef nt2::simd::native<uint16_t,ext_t> vuint16_t;
typedef nt2::simd::native<uint8_t,ext_t> vuint8_t;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<floor_> from libc
//////////////////////////////////////////////////////////////////////////////
using nt2::libc::tag::floor_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::libc::tag::floor_,(RS(vfloat,-10000.0f,10000.0f)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vdouble,-10000.0,10000.0)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vint64_t,-10000,10000)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vint32_t,-10000,10000)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vint16_t,-32768,32767)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vint8_t,-128,127)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vuint64_t,0,65535)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vuint32_t,0,65535)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vuint16_t,0,65535)))
NT2_TIMING(nt2::libc::tag::floor_,(RS(vuint8_t,0,255)))

#undef RS

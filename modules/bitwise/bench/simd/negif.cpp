//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/bitwise/include/negif.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<float,ext_t> vfloat;
typedef nt2::simd::native<double,ext_t> vdouble;
typedef nt2::simd::native<int64_t,ext_t> vint64_t;
typedef nt2::simd::native<int32_t,ext_t> vint32_t;
typedef nt2::simd::native<int16_t,ext_t> vint16_t;
typedef nt2::simd::native<int8_t,ext_t> vint8_t;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<negif_> from bitwise
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::negif_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::tag::negif_,(RS(vfloat,-10000.0f,10000.0f))(RS(vfloat,-10000.0f,10000.0f)))
NT2_TIMING(nt2::tag::negif_,(RS(vdouble,-10000.0,10000.0))(RS(vdouble,-10000.0,10000.0)))
NT2_TIMING(nt2::tag::negif_,(RS(vint64_t,-10000,10000))(RS(vint64_t,-10000,10000)))
NT2_TIMING(nt2::tag::negif_,(RS(vint32_t,-10000,10000))(RS(vint32_t,-10000,10000)))
NT2_TIMING(nt2::tag::negif_,(RS(vint16_t,-32768,32767))(RS(vint16_t,-32768,32767)))
NT2_TIMING(nt2::tag::negif_,(RS(vint8_t,-128,127))(RS(vint8_t,-128,127)))

#undef RS

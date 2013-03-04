//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/toolbox/bitwise/include/functions/shift_left.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <cmath>

typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
typedef boost::simd::native<float,ext_t> vfloat;
typedef boost::simd::native<double,ext_t> vdouble;
typedef boost::simd::native<int64_t,ext_t> vint64_t;
typedef boost::simd::native<int32_t,ext_t> vint32_t;
typedef boost::simd::native<int16_t,ext_t> vint16_t;
typedef boost::simd::native<int8_t,ext_t> vint8_t;
typedef boost::simd::native<uint64_t,ext_t> vuint64_t;
typedef boost::simd::native<uint32_t,ext_t> vuint32_t;
typedef boost::simd::native<uint16_t,ext_t> vuint16_t;
typedef boost::simd::native<uint8_t,ext_t> vuint8_t;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<shift_left_> from bitwise
//////////////////////////////////////////////////////////////////////////////
using boost::simd::functors::shift_left_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vfloat,-10000.0f,10000.0f))(RS(vint32_t,0,31)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vdouble,-10000.0,10000.0))(RS(vint64_t,0,63)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vint64_t,-10000,10000))(RS(vint64_t,0,63)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vint32_t,-10000,10000))(RS(vint32_t,0,31)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vint16_t,-32768,32767))(RS(vint16_t,0,16)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vint8_t,-128,127))(RS(vint8_t,0,7)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vuint64_t,0,65535))(RS(vuint64_t,0,63)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vuint32_t,0,65535))(RS(vuint32_t,0,31)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vuint16_t,0,65535))(RS(vuint16_t,0,16)))
BOOST_SIMD_TIMING(boost::simd::functors::shift_left_,(RS(vuint8_t,0,255))(RS(vuint8_t,0,7)))

#undef RS

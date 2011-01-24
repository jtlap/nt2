//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/euler/include/dawson.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<float,ext_t> vfloat;
typedef nt2::simd::native<double,ext_t> vdouble;
typedef nt2::simd::native<int32_t,ext_t> vint32_t;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<dawson_> from euler
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::dawson_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::tag::dawson_,(RS(vfloat,0.0f,100.0f)))
NT2_TIMING(nt2::tag::dawson_,(RS(vdouble,0.0,100.0)))
NT2_TIMING(nt2::tag::dawson_,(RS(vint32_t,0.0,100.0)))

#undef RS

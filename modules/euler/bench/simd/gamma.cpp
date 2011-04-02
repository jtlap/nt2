//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/euler/include/gamma.hpp>
#include <nt2/toolbox/euler/include/fast_gamma.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<float,ext_t> vfloat;
typedef nt2::simd::native<double,ext_t> vdouble;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<gamma_> from euler
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::gamma_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::tag::gamma_,(RS(vfloat,0.0f,12.0f)))
NT2_TIMING(nt2::tag::gamma_,(RS(vdouble,0.0,12.0)))
NT2_TIMING(nt2::tag::gamma_,(RS(float,0.0f,12.0f)))
NT2_TIMING(nt2::tag::gamma_,(RS(double,0.0,12.0)))
NT2_TIMING(nt2::tag::fast_gamma_,(RS(vfloat,0.0f,12.0f)))
NT2_TIMING(nt2::tag::fast_gamma_,(RS(vdouble,0.0,12.0)))
NT2_TIMING(nt2::tag::fast_gamma_,(RS(float,0.0f,12.0f)))
NT2_TIMING(nt2::tag::fast_gamma_,(RS(double,0.0,12.0)))

#undef RS
